#include "tables.h"
#include "original_alg.h"

void original_algorithm(const char *s_table, const char *r_table) {
    unsigned long i, j;
    char buff1, buff2;
    for (i = 0; i < R_BLOCKS; i++) {
        read_block(s_table[i], &buff1);
        for (j = 0; j < S_BLOCKS; j++) {
            read_block(r_table[j], &buff2);
            product(&buff1, &buff2);
        }
    }
}
