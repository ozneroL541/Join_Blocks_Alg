#include <stdio.h>
#include "tables.h"
#include "buffer_blocks.h"
#include "original_alg.h"
#include "modified_alg.h"
#include "original_multi_block_alg.h"
#include "modified_multi_block_alg.h"

#define ROUNDUP_DIVISION(dividend, divisor) \
    ((unsigned long)((dividend % divisor) == 0) ? (dividend / divisor) : ((dividend / divisor) + 1))

char s_table[R_BLOCKS], r_table[S_BLOCKS];

int main() {
    unsigned long blocks_read;
    const unsigned long br = R_BLOCKS, bs = S_BLOCKS, b = BUFFER_BLOCKS;
    init_table(s_table, br);
    init_table(r_table, bs);

    blocks_read = original_algorithm(s_table, r_table);
    printf("Original algorithm\n");
    printf("Total blocks read:\t\t%lu\n", blocks_read);
    printf("B(R) + B(R)xB(S):\t\t%lu\n",(br + br * bs));
    printf("B(S) + B(R)xB(S):\t\t%lu\n",(bs + br * bs));

    blocks_read = modified_algorithm(s_table, r_table);
    printf("Modified algorithm\n");
    printf("Total blocks read:\t\t%lu\n", blocks_read);
    printf("B(R)xB(S) + 1:\t\t\t%lu\n", (br*bs + 1));
    printf("B(R) + B(R)x(B(S)-1) + 1:\t%lu\n", (br + br * (bs - 1) + 1));

    blocks_read = original_multi_block_alg(s_table, r_table);
    printf("Original multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", blocks_read);
    printf("B(R)+[B(R)/(B-1)]xB(S):\t\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * bs));

    blocks_read = modified_multi_block_alg(s_table, r_table);
    printf("Modified multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", blocks_read);
    printf("B(R)+[B(R)/(B-1)]x(B(S)-1)+1:\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * (bs-1) + 1));

    return 0;
}