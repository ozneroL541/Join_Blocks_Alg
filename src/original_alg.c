#include "tables.h"
#include "original_alg.h"

unsigned long original_algorithm(const char *r_table, const char *s_table, const unsigned long r_blocks, const unsigned long s_blocks) {
    /** Number of blocks read */
    unsigned long blocks_read = 0;
    /** Loop variables */
    unsigned long i, j;
    /** Buffers for the blocks */
    char buff1, buff2;
    
    for (i = 0; i < r_blocks; i++) {
        read_block(r_table[i], &buff1, &blocks_read);
        for (j = 0; j < s_blocks; j++) {
            read_block(s_table[j], &buff2, &blocks_read);
            product(&buff1, &buff2);
        }
    }
    return blocks_read;
}
