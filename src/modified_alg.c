#include "tables.h"
#include "modified_alg.h"

void modified_algorithm(const char *s_table, const char *r_table) {
    unsigned long i, j = 0, k = 0;
    char buff1, buff2;
    read_block(r_table[j], &buff2);
    for (i = 0; i < R_BLOCKS; i++) {
        read_block(s_table[i], &buff1);
        product(&buff1, &buff2);
        for (k = 1; k < S_BLOCKS; k++) {
            j = (j+1)%S_BLOCKS;
            read_block(r_table[j], &buff2);
            product(&buff1, &buff2);
        }
    }
}
