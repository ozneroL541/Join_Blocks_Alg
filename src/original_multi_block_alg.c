#include "tables.h"
#include "buffer_blocks.h"
#include "original_multi_block_alg.h"

unsigned long original_multi_block_alg(const char *r_table, const char *s_table, const unsigned long r_blocks, const unsigned long s_blocks, const unsigned long buffer_blocks) {
    /** Number of blocks read */
    unsigned long blocks_read = 0;
    /** Loop variables */
    unsigned long i = 0, j;
    /** Buffers for the blocks */
    char *buffer = NULL;

    if (buffer_blocks >= 2) {
        buffer = (char *)calloc(buffer_blocks, sizeof(char));
        if (buffer == NULL) {
            return 0;
        }
        while (i < r_blocks) {
            for (j = 1; j < buffer_blocks && i < r_blocks; j++) {
                read_block(r_table[i], &buffer[j], &blocks_read);
                i++;
            }
            for (j = 0; j < s_blocks; j++) {
                read_block(s_table[j], &buffer[0], &blocks_read);
                product(&buffer[0], &buffer[j]);
            }
        }
        free(buffer);
    }
    return blocks_read;
}
