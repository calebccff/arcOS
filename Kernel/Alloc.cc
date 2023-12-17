
#include <Arc.h>
#include <Arc/memory.h>
#include <Arc/printk.h>

#define CHUNK_MAGIC 0x6D656f77

#define BLKSHIFT 6
#define BLKSIZE (1 << BLKSHIFT)

enum chunk_state : uint8_t {
	CHUNK_STATE_UNKNOWN = 0,
	CHUNK_STATE_FREE = 1,
	CHUNK_STATE_USED = 2
};

struct chunk {
	uint32_t chunk_magic; // 0x6D656f77
	chunk_state state; 
	uint16_t size; // in 64-byte blocks (<< 8)
	struct chunk *next;
};

static addr_t heap_top = 0;
static chunk *first_chunk = nullptr;
static chunk *current_chunk = nullptr;
static chunk *last_chunk = nullptr;

static inline void init_chunk(chunk *c, size_t size)
{
	c->chunk_magic = CHUNK_MAGIC;
	c->state = CHUNK_STATE_FREE;
	c->size = size;
	c->next = first_chunk;
}

/* Allocate a new chunk to add to the circular chunk buffer */
static inline chunk *alloc_chunk(size_t size)
{
	chunk *next = (chunk *)((addr_t)last_chunk + (last_chunk->size << BLKSHIFT) + sizeof(chunk));
	/* FIXME: handle OOM */
	assert((addr_t)next < heap_top);

	last_chunk->next = next;
	last_chunk = next;

	init_chunk(next, size);

	return next;
}

static void malloc_init_chunks(size_t size, size_t count)
{
	assert(size > 0);

	for (int i = 0; i < count; i++) {
		alloc_chunk(size);
	}
}

static addr_t use_chunk(chunk *c)
{
	void *addr = (void*)((addr_t)c + sizeof(chunk));
	c->state = CHUNK_STATE_USED;

	memset(addr, 0x0, (c->size << BLKSHIFT) - sizeof(chunk));
	
	return (addr_t)addr;
}

void malloc_init(addr_t top, size_t size)
{
	size_t total_blocks = size / BLKSIZE;

	log_debug("Initializing heap at [0x%x - 0x%x] (%lu blocks)", top - size, top, total_blocks);

	assert(size > 0);
	assert(size == ALIGN(size, 0x1000));
	assert(top > size);
	assert(top == ALIGN(top, 0x1000));

	heap_top = top;

	/* We want the addresses returned by malloc to be well-aligned, so we store the chunk headers
	 * misaligned at the end of the previous chunk
	 */
	last_chunk = current_chunk = first_chunk = (chunk *)(top - size + BLKSIZE - sizeof(chunk));
	init_chunk(first_chunk, 1);

	/* Pre-allocate the first 1/8th of RAM with small chunks */
	for (int i = 0; i < total_blocks / 8; i += (1 * 1 + 16 * 2 + 64 * 1)) {
		/* Allocate 64 byte chunks */
		if (i > 0)
			malloc_init_chunks(1, 1);
		/* Allocate 1k byte chunks */
		malloc_init_chunks(16, 2);
		/* Allocate 4k byte chunks */
		malloc_init_chunks(64, 1);
	}

	log_debugfn("first/last chunk: 0x%x / 0x%x", first_chunk, last_chunk);
}

/* Number of additional blocks to search for a better match under some
 * conditions
 */
#define MAX_STEPS 16

extern "C" {
void *malloc(size_t size)
{
	void *addr;
	/* Round up to nearest 64-byte block and include space
	 * for the chunk header (of the next block)
	 */
	size = ALIGN(size, BLKSIZE) >> BLKSHIFT;

	/* Find a free chunk */
	chunk *c = current_chunk;
	chunk *best = nullptr;
	int steps = 0;
	do {
		if (c->state == CHUNK_STATE_FREE && c->size >= size) {
			if (!best) {
				best = c;
			} else if (c->size < best->size) {
				best = c;
			}

			if (best->size - size <= 16 || steps > MAX_STEPS) {
				break;
			}
			steps++;
		}
		c = c->next;
	} while (c != current_chunk);

	/* If we found a free chunk */
	if (best) {
		c = current_chunk = best;
		log_debugfn("found free chunk after %d steps (has %d extra blocks)", steps, c->size - size);
	}

	/* If we didn't find a free chunk, allocate a new one */
	if (c->state != CHUNK_STATE_FREE || c->size < size) {
		log_debugfn("allocating new chunk");
		c = alloc_chunk(size);
	}

	addr = (void *)use_chunk(c);
	log_debugfn("0x%x - %lu blocks requested", addr, size);

	return addr;
}

void free(void *ptr) {
	chunk *c = (chunk *)(((addr_t)ptr) - sizeof(chunk));
	log_debugfn("0x%x", ptr);
	bug(c->chunk_magic == CHUNK_MAGIC, "invalid chunk magic! 0x%x != 0x%x", c->chunk_magic, CHUNK_MAGIC);
	bug(c->state == CHUNK_STATE_USED, "chunk is not in use (state %d)!", c->state);

	c->state = CHUNK_STATE_FREE;

	memset(ptr, 0xAB, (c->size << BLKSHIFT) - sizeof(chunk));

	log_debugfn("0x%x - freed %d blocks", ptr, c->size);
};
}

/* Override C++ operators */
void * operator new(size_t n)
{
	return malloc(n);
}
void operator delete(void * p) throw()
{
  free(p);
}


void test_malloc()
{
	void *ptrs[10];
	void *ptr;

	log_test_start("malloc");
	log_test("malloc(256) x 10");
	for (int i = 0; i < 10; i++) {
		ptrs[i] = malloc(256);
		assert(ptrs[i] != nullptr);
	}

	chunk *c = first_chunk;
	for (int i = 0; i < 10; i++) {
		log_test("chunk 0x%x: state %d, size %d", c, c->state, c->size);
		c = c->next;
	}

	log_test("free() x 10");
	for (int i = 0; i < 10; i++) {
		free(ptrs[i]);
	}

	log_test("malloc(4095) x 10");
	for (int i = 0; i < 10; i++) {
		ptrs[i] = malloc(4095);
		assert(ptrs[i] != nullptr);
	}

	log_test("malloc(128) x 1");
	ptr = malloc(128);

	log_test("free() x 10");
	for (int i = 0; i < 10; i++) {
		free(ptrs[i]);
		if (i == 5) {
			log_test("free(ptr) x 1");
			free(ptr);
		}
	}

	ptr = malloc(0x10000);
	assert(ptr != nullptr);
	free(ptr);

	assert(last_chunk->size == (0x10000 >> BLKSHIFT));

	log_test_end("malloc");
}
