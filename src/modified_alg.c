#include "tables.h"
#include "modified_alg.h"

unsigned long modified_algorithm(const char *r_table, const char *s_table) {
    unsigned long blocks_read = 0;
    unsigned long i, j = 0, k = 0;
    char buff1, buff2;
    read_block(s_table[j], &buff2, &blocks_read);
    for (i = 0; i < R_BLOCKS; i++) {
        read_block(r_table[i], &buff1, &blocks_read);
        product(&buff1, &buff2);
        for (k = 1; k < S_BLOCKS; k++) {
            j = (j+1)%S_BLOCKS;
            read_block(s_table[j], &buff2, &blocks_read);
            product(&buff1, &buff2);
        }
    }
    return blocks_read;
}
