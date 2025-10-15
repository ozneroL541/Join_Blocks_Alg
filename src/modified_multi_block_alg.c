#include "tables.h"
#include "buffer_blocks.h"
#include "modified_multi_block_alg.h"

unsigned long modified_multi_block_alg(const char *r_table, const char *s_table, const unsigned long r_blocks, const unsigned long s_blocks, const unsigned long buffer_blocks) {
    unsigned long blocks_read = 0;
    char buffer[buffer_blocks];
    unsigned long i = 0, j = 0, k = 0, z = 0;
    if (buffer_blocks >= 2) {
        read_block(s_table[j], &buffer[0], &blocks_read);
        while ( i < r_blocks ) {
            for (k = 1; k < buffer_blocks && i < r_blocks; k++) {
                read_block(r_table[i], &buffer[k], &blocks_read);
                i++;
            }
            multi_product(buffer, k);
            for (j = 1; j < s_blocks; j++) {
                read_block(s_table[z], &buffer[0], &blocks_read);
                multi_product(buffer, k);
                z = (z + 1) % s_blocks;
            }
        }
    }
    return blocks_read;
}
