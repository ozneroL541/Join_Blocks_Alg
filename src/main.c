#include <stdio.h>
#include "alg_threads.h"
#include "original_alg.h"
#include "modified_alg.h"
#include "original_multi_block_alg.h"
#include "modified_multi_block_alg.h"
#include "product_executor.h"

#define ROUNDUP_DIVISION(dividend, divisor) \
    ((unsigned long)((dividend % divisor) == 0) ? (dividend / divisor) : ((dividend / divisor) + 1))


int main(void) {
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
    const unsigned long 
        /** Number of blocks in R */
        br = 65537,
        /** Number of blocks in S */
        bs = 65537,
        /** Number of blocks in the buffer */
        b = 2048;
    /** Tables structure */
    tables * tbl = init_rs(br, bs);

    if (tbl == NULL) {
        fprintf(stderr, "Error initializing tables\n");
        return -1;
    }
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

    original_t = start_alg(original);
    modified_t = start_alg(modified);
    original_mb_t = start_alg(original_mb);
    modified_mb_t = start_alg(modified_mb);

    if(original_t == NULL || modified_t == NULL || original_mb_t == NULL || modified_mb_t == NULL) {
        fprintf(stderr, "Error starting algorithm threads\n");
        free_product_params(original, 0);
        free_product_params(modified, 0);
        free_product_params(original_mb, 0);
        free_product_params(modified_mb, 0);
        free_tables(tbl, 1);
        return -1;
    }

    printf("Original algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(original_t));
    printf("B(R) + B(R)xB(S):\t\t%lu\n",(br + br * bs));
    printf("B(S) + B(R)xB(S):\t\t%lu\n",(bs + br * bs));
    printf("Modified algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(modified_t));
    printf("B(R)xB(S) + 1:\t\t\t%lu\n", (br*bs + 1));
    printf("B(R) + B(R)x(B(S)-1) + 1:\t%lu\n", (br + br * (bs - 1) + 1));
    printf("Original multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(original_mb_t));
    printf("B(R)+[B(R)/(B-1)]xB(S):\t\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * bs));
    printf("Modified multi-block algorithm\n");
    printf("Total blocks read:\t\t%lu\n", join_alg(modified_mb_t));
    printf("B(R)+[B(R)/(B-1)]x(B(S)-1)+1:\t%lu\n", (br + ROUNDUP_DIVISION(br, (b-1)) * (bs-1) + 1));

    free_product_params(original, 0);
    free_product_params(modified, 0);
    free_product_params(original_mb, 0);
    free_product_params(modified_mb, 1);
    return 0;
}
