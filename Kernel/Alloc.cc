
#include <Arc/memory.h>

static addr_t malloc_start;
static addr_t malloc_size;
static addr_t malloc_pos;

void malloc_init(addr_t start, addr_t size)
{
	malloc_start = start;
	malloc_size = size;
	malloc_pos = start;
}

extern "C" {
void *malloc(size_t size) {
	addr_t ret = malloc_pos;
	malloc_pos += size;
	return (void *)ret;
}

void free(void *ptr) {
	(void)ptr;
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
