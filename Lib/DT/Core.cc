
#include <Arc/endian.h>
#include <Arc/stdint.h>
#include <DT/Core.h>

struct fdt_header {
	be32_t magic;
	be32_t totalsize;
	be32_t off_dt_struct;
	be32_t off_dt_strings;
	be32_t off_mem_rsvmap;
	be32_t version;
	be32_t last_comp_version;
	be32_t boot_cpuid_phys;
	be32_t size_dt_strings;
	be32_t size_dt_struct;
};

class FDT {
private:
	const void *fdt;
public:
	FDT(const void *fdt) : fdt(fdt) {
		const struct fdt_header *header = 
			reinterpret_cast<const struct fdt_header*>(fdt);

		if (be32_to_cpu(header->magic) != 0xd00dfeed) {
			
		}
	}
};