#include "tables.h"

/** Seed */
static unsigned int g_seed;
/** 
 * Used to seed the generator.
 * @param seed Seed value
 */
void fast_srand(int seed) {
    g_seed = seed;
}
/**
 * Compute a pseudorandom integer.
 * Output value in range [0, 32767] 
 * @return Pseudorandom integer
 */
int fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

void init_table(char *table, const unsigned long size) {
    register unsigned long i;
    for (i = 0; i < size; i++) {
        table[i] = (char) fast_rand(); /*(char) (i % 128);*/
    }
}

void product(const char *block_buffer1, const char *block_buffer2){
    /*printf("Product of %d and %d\n", *block_buffer1, *block_buffer2);*/
}

void read_block(const char table_block, char * buffer_block, unsigned long * counter) {
    *buffer_block = table_block;
    *counter = (*counter + 1);
    /*printf("counter: %lu\n", *counter);*/
}
