#include "tables.h"
#include "buffer_blocks.h"

void multi_product(const char buff[], const unsigned long max_blocks) {
    unsigned long i;
    for (i = 1; i < max_blocks; i++) {
        product(&buff[i], &buff[0]);
    }
}
