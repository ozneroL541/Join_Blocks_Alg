#include "tables.h"
#include <stdio.h>

void init_table(char *table, const unsigned long size) {
    register unsigned long i;
    for (i = 0; i < size; i++) {
        table[i] = (char) (i % 128);
    }
}

void product(const char *block_buffer1, const char *block_buffer2){
    /*printf("Product of %d and %d\n", *block_buffer1, *block_buffer2);*/
}

void read_block(const char table_block, char * buffer_block, unsigned long * counter) {
    *buffer_block = table_block;
    ++(*counter);
    /*printf("counter: %lu\n", *counter);*/
}
