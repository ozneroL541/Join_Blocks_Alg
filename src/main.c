#include <stdio.h>
#include "alg_threads.h"
#include "original_alg.h"
#include "modified_alg.h"
#include "original_multi_block_alg.h"
#include "modified_multi_block_alg.h"
#include "product_executor.h"

int main(void) {
    tables * tbl = init_rs(65536, 32000);
    product_params * original, * modified, * original_mb, * modified_mb;
    product_t * original_t, * modified_t, * original_mb_t, * modified_mb_t;
    if (tbl == NULL) {
        fprintf(stderr, "Error initializing tables\n");
        return -1;
    }
    if ((original = init_product_params(tbl, init_alg_c(original_algorithm), 3)) == NULL ) {
        free_tables(tbl, 1);
        return -1;
    }
    if ((modified = init_product_params(tbl, init_alg_c(modified_algorithm), 3)) == NULL ) {
        free_product_params(original);
        free_tables(tbl, 1);
        return -1;
    }
    if ((original_mb = init_product_params(tbl, init_alg_mb(original_multi_block_alg), 8)) == NULL ) {
        free_product_params(original);
        free_product_params(modified);
        free_tables(tbl, 1);
        return -1;
    }
    if ((modified_mb = init_product_params(tbl, init_alg_mb(modified_multi_block_alg), 8)) == NULL ) {
        free_product_params(original);
        free_product_params(modified);
        free_product_params(original_mb);
        free_tables(tbl, 1);
        return -1;
    }

    original_t = start_alg(original);
    modified_t = start_alg(modified);
    original_mb_t = start_alg(original_mb);
    modified_mb_t = start_alg(modified_mb);

    printf("Original algorithm read %lu blocks\n", join_alg(original_t));
    printf("Modified algorithm read %lu blocks\n", join_alg(modified_t));
    printf("Original multi-block algorithm read %lu blocks\n", join_alg(original_mb_t));
    printf("Modified multi-block algorithm read %lu blocks\n", join_alg(modified_mb_t));

    free_product_params(original);
    free_product_params(modified);
    free_product_params(original_mb);
    free_product_params(modified_mb);
    free_tables(tbl, 1);
    return 0;
}

