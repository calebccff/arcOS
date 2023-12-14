#pragma once

/* We only care about little endian native arches */

#define be16_to_cpu(x) ((x) >> 8 | (x) << 8)
#define be32_to_cpu(x) ((x) >> 24 | ((x) & 0xff0000) >> 8 | ((x) & 0xff00) << 8 | (x) << 24)
#define be64_to_cpu(x) ((x) >> 56 | ((x) & 0xff000000000000) >> 40 | ((x) & 0xff0000000000) >> 24 | ((x) & 0xff00000000) >> 8 | ((x) & 0xff000000) << 8 | ((x) & 0xff0000) << 24 | ((x) & 0xff00) << 40 | (x) << 56)

#define cpu_to_be16(x) be16_to_cpu(x)
#define cpu_to_be32(x) be32_to_cpu(x)
#define cpu_to_be64(x) be64_to_cpu(x)
