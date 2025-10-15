#include <stdio.h>
#include "alg_threads.h"
#include "original_alg.h"
#include "modified_alg.h"
#include "original_multi_block_alg.h"
#include "modified_multi_block_alg.h"
#include "product_executor.h"

#define ROUNDUP_DIVISION(dividend, divisor) \
    ((unsigned long)((dividend % divisor) == 0) ? (dividend / divisor) : ((dividend / divisor) + 1))


int main(int argc, char *argv[]) {
    product_params 
        /** Original algorithm */
        * original = NULL, 
        /** Modified algorithm */
        * modified = NULL, 
        /** Original multi-block algorithm */
        * original_mb = NULL, 
        /** Modified multi-block algorithm */
        * modified_mb = NULL;
    /** Product threads */
    product_t
        /** Original algorithm thread */
        * original_t = NULL, 
        /** Modified algorithm thread */
        * modified_t = NULL, 
        /** Original multi-block algorithm thread */
        * original_mb_t = NULL,
        /** Modified multi-block algorithm thread */
        * modified_mb_t = NULL;
    unsigned long 
        /** Number of blocks in R */
        br = 0,
        /** Number of blocks in S */
        bs = 0,
        /** Number of blocks in the buffer */
        b = 0;
    /** Tables structure */
    tables * tbl = NULL;

    /* Read input datas */
    if(argc != 4) {
        fprintf(stderr, "Usage: %s <R table blocks> <S table blocks> <Buffer blocks>\n", argv[0]);
        return -1;
    }
    if(sscanf(argv[1], "%lu", &br) != 1 || sscanf(argv[2], "%lu", &bs) != 1 || sscanf(argv[3], "%lu", &b) != 1) {
        fprintf(stderr, "Error reading input parameters\n");
        fprintf(stderr, "Usage: %s <R table blocks> <S table blocks> <Buffer blocks>\n", argv[0]);
        return -1;
    }
    if(br == 0 || bs == 0 || b <= 3) {
        fprintf(stderr, "Invalid input parameters\n");
        fprintf(stderr, "R and S table blocks must be greater than 0\n");
        fprintf(stderr, "Buffer blocks must be greater than 3\n");
        return -1;
    }
    /* Initialize tables */
    if ((tbl = init_rs(br, bs)) == NULL) {
        fprintf(stderr, "Error initializing tables\n");
        return -1;
    }
    /* Initialize product parameters for each algorithm */
    if (
        (original = init_product_params(tbl, init_alg_c(original_algorithm), 0)) == NULL || 
        (modified = init_product_params(tbl, init_alg_c(modified_algorithm), 0)) == NULL ||
        (original_mb = init_product_params(tbl, init_alg_mb(original_multi_block_alg), b)) == NULL ||
        (modified_mb = init_product_params(tbl, init_alg_mb(modified_multi_block_alg), b)) == NULL 
    ) {
        if(original != NULL) free_product_params(original, 0);
        if(modified != NULL) free_product_params(modified, 0);
        if(original_mb != NULL) free_product_params(original_mb, 0);
        if(modified_mb != NULL) free_product_params(modified_mb, 0);
        if(tbl != NULL) free_tables(tbl, 1);
        return -1;
    }
    /* Start algorithms simulation */
    original_t = start_alg(original);
    modified_t = start_alg(modified);
    original_mb_t = start_alg(original_mb);
    modified_mb_t = start_alg(modified_mb);
    /* Check for errors */
    if(original_t == NULL || modified_t == NULL || original_mb_t == NULL || modified_mb_t == NULL) {
        fprintf(stderr, "Error starting algorithm threads\n");
        free_product_params(original, 0);
        free_product_params(modified, 0);
        free_product_params(original_mb, 0);
        free_product_params(modified_mb, 0);
        free_tables(tbl, 1);
        return -1;
    }
    /* Print results */
    printf("Original algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(original_t));
    printf("B(R) + B(R)xB(S):\t\t%lu\n",(br + br * bs));
    printf("B(S) + B(R)xB(S):\t\t%lu\n",(bs + br * bs));
    free_product_params(original, 0);
    printf("Modified algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(modified_t));
    printf("B(R)xB(S) + 1:\t\t\t%lu\n", (br*bs + 1));
    printf("B(R) + B(R)x(B(S)-1) + 1:\t%lu\n", (br + br * (bs - 1) + 1));
    free_product_params(modified, 0);
    printf("Original multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(original_mb_t));
    printf("B(R)+[B(R)/(B-1)]xB(S):\t\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * bs));
    free_product_params(original_mb, 0);
    printf("Modified multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(modified_mb_t));
    printf("B(R)+[B(R)/(B-1)]x(B(S)-1)+1:\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * (bs-1) + 1));
    free_product_params(modified_mb, 1);

    return 0;
}
