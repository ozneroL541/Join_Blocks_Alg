#include "tables.h"
#include "original_alg.h"

unsigned long original_algorithm(const char *r_table, const char *s_table) {
    unsigned long blocks_read = 0;
    unsigned long i, j;
    char buff1, buff2;
    for (i = 0; i < R_BLOCKS; i++) {
        read_block(r_table[i], &buff1, &blocks_read);
        for (j = 0; j < S_BLOCKS; j++) {
            read_block(s_table[j], &buff2, &blocks_read);
            product(&buff1, &buff2);
        }
    }
    return blocks_read;
}
