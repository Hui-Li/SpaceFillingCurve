#include <stdint.h>
#include <limits.h>

namespace ZOrder {
    uint64_t mortonEncode_for(unsigned int x, unsigned int y, unsigned int z) {
        uint64_t answer = 0;
        for (uint64_t i = 0; i < (sizeof(uint64_t) * CHAR_BIT) / 3; ++i) {
            answer |= ((x & ((uint64_t) 1 << i)) << 2 * i) | ((y & ((uint64_t) 1 << i)) << (2 * i + 1)) |
                      ((z & ((uint64_t) 1 << i)) << (2 * i + 2));
        }
        return answer;
    }

    uint64_t mortonEncode_for(unsigned int x, unsigned int y) {
        uint64_t answer = 0;
        for (uint64_t i = 0; i < (sizeof(uint64_t) * CHAR_BIT) / 2; ++i) {
            answer |= ((x & ((uint64_t) 1 << i)) << 2 * i) | ((y & ((uint64_t) 1 << i)) << (2 * i + 1));
        }
        return answer;
    }
}
