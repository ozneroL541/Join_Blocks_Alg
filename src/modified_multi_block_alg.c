#include "tables.h"
#include "buffer_blocks.h"
#include "modified_multi_block_alg.h"

void modified_multi_block_alg(const char *s_table, const char *r_table) {
    unsigned long i = 0, j = 0, k = 0, z = 0;
    if (BUFFER_BLOCKS >= 2) {
        read_block(s_table[j], &buffer[0]);
        while ( i < R_BLOCKS ) {
            for (k = 1; k < BUFFER_BLOCKS && i < R_BLOCKS; k++) {
                read_block(r_table[i], &buffer[k]);
                i++;
            }
            multi_product(buffer, k);
            for (j = 1; j < S_BLOCKS; j++) {
                read_block(s_table[z], &buffer[0]);
                multi_product(buffer, k);
                z = (z + 1) % S_BLOCKS;
            }
        }
    }
}
