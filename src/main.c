#include <stdio.h>
#include "tables.h"
#include "buffer_blocks.h"
#include "original_alg.h"
#include "modified_alg.h"
#include "original_multi_block_alg.h"
#include "modified_multi_block_alg.h"
#include <pthread.h>

#define ROUNDUP_DIVISION(dividend, divisor) \
    ((unsigned long)((dividend % divisor) == 0) ? (dividend / divisor) : ((dividend / divisor) + 1))

char r_table[R_BLOCKS], s_table[S_BLOCKS];

void * t_init_r_table(void *arg) {
    init_table(r_table, R_BLOCKS);
    pthread_exit(arg);
}
void * t_init_s_table(void *arg) {
    init_table(s_table, S_BLOCKS);
    pthread_exit(arg);
}
void * t_original_algorithm(void *count) {
    *((unsigned long *)count) = original_algorithm(r_table, s_table);
    pthread_exit(NULL);
}
void * t_modified_algorithm(void *count) {
    *((unsigned long *)count) = modified_algorithm(r_table, s_table);
    pthread_exit(NULL);
}
void * t_original_multi_block_algorithm(void *count) {
    (*((unsigned long *)count)) = original_multi_block_alg(r_table, s_table);
    pthread_exit(NULL);
}
void * t_modified_multi_block_algorithm(void *count) {
    *((unsigned long *)count) = modified_multi_block_alg(r_table, s_table);
    pthread_exit(NULL);
}

int main(void) {
    unsigned long oa_io, ma_io, oma_io, mma_io;
    pthread_t oa_t, ma_t, oma_t, mma_t;
    const unsigned long br = R_BLOCKS, bs = S_BLOCKS, b = BUFFER_BLOCKS;
    int check = 0;

    check += pthread_create(&oa_t, NULL, t_init_r_table, NULL);
    check += pthread_create(&ma_t, NULL, t_init_s_table, NULL);
    if (check) {
        fprintf(stderr, "Error creating threads\n");
        return check;
    }
    pthread_join(oa_t, NULL);
    pthread_join(ma_t, NULL);
    printf("Tables initialized\n"); 
    check += pthread_create(&oa_t, NULL, t_original_algorithm, (void *)&oa_io);
    check += pthread_create(&ma_t, NULL, t_modified_algorithm, (void *)&ma_io);
    check += pthread_create(&oma_t, NULL, t_original_multi_block_algorithm, (void *)&oma_io);
    check += pthread_create(&mma_t, NULL, t_modified_multi_block_algorithm, (void *)&mma_io);
    if (check) {
        fprintf(stderr, "Error creating threads\n");
        return check;
    }

    pthread_join(oa_t, NULL);
    printf("Original algorithm\n");
    printf("Total blocks read:\t\t%lu\n", oa_io);
    printf("B(R) + B(R)xB(S):\t\t%lu\n",(br + br * bs));
    printf("B(S) + B(R)xB(S):\t\t%lu\n",(bs + br * bs));
    pthread_join(ma_t, NULL);
    printf("Modified algorithm\n");
    printf("Total blocks read:\t\t%lu\n", ma_io);
    printf("B(R)xB(S) + 1:\t\t\t%lu\n", (br*bs + 1));
    printf("B(R) + B(R)x(B(S)-1) + 1:\t%lu\n", (br + br * (bs - 1) + 1));
    pthread_join(oma_t, NULL);
    printf("Original multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", oma_io);
    printf("B(R)+[B(R)/(B-1)]xB(S):\t\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * bs));
    pthread_join(mma_t, NULL);
    printf("Modified multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", mma_io);
    printf("B(R)+[B(R)/(B-1)]x(B(S)-1)+1:\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * (bs-1) + 1));

    return 0;
}
