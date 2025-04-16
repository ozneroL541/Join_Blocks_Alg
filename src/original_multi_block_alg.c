#include "tables.h"
#include "buffer_blocks.h"
#include "original_multi_block_alg.h"

unsigned long original_multi_block_alg(const char *r_table, const char *s_table) {
    unsigned long blocks_read = 0;
    char buffer[BUFFER_BLOCKS];
    unsigned long i = 0, j;
    if (BUFFER_BLOCKS >= 2) {
        while (i < R_BLOCKS) {
            for (j = 1; j < BUFFER_BLOCKS && i < R_BLOCKS; j++) {
                read_block(r_table[i], &buffer[j], &blocks_read);
                i++;
            }
            for (j = 0; j < S_BLOCKS; j++) {
                read_block(s_table[j], &buffer[0], &blocks_read);
                product(&buffer[0], &buffer[j]);
            }
        }
    }
    return blocks_read;
}
