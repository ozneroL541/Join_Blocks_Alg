#include "product_executor.h"

algorithm * init_alg_c(unsigned long (*alg)(const char *, const char *, const unsigned long, const unsigned long)) {
    algorithm * new_alg = (algorithm *)malloc(sizeof(algorithm));
    if (new_alg != NULL) {
        new_alg->alg = alg;
    }
    return new_alg;
}

algorithm * init_alg_mb(unsigned long (*mb_alg)(const char *, const char *, const unsigned long, const unsigned long, const unsigned long)) {
    algorithm * new_alg = (algorithm *)malloc(sizeof(algorithm));
    if (new_alg != NULL) {
        new_alg->mb_alg = mb_alg;
    }
    return new_alg;
}

product_params * init_product_params(tables * blk, algorithm * alg, const unsigned long buffer_blocks) {
    product_params * params = (product_params *)malloc(sizeof(product_params));
    if (params != NULL) {
        params->blk = blk;
        params->alg = alg;
        if (buffer_blocks < 3) {
            params->buffer_blocks = 3;
        } else {
            params->buffer_blocks = buffer_blocks;
        }
    }
    return params;
}

void free_product_params(product_params * params) {
    if (params != NULL) {
        free_tables(params->blk, 1);
        free(params->alg);
        free(params);
    }
}

/** 
 * Check the validity of the parameters for executing the product simulation
 * @param params Pointer to the product_params structure
 * @return 0 on success, number of errors found otherwise
 */
char verify_params(product_params * params) {
    /** Number of errors found */
    char errors = 0;

    if (params == NULL) {
        /** Invalid parameters */
        errors++;
    }
    if (params->blk == NULL) {
        /** Invalid block structure */
        errors++;
    } else {
        if (params->blk->r_table == NULL || params->blk->s_table == NULL) {
            /** Invalid table structure */
            errors++;
        }
    }
    if (params->alg == NULL) {
        /** Invalid algorithm structure */
        errors++;
    } else {
        if (params->alg->alg == NULL && params->alg->mb_alg == NULL) {
            /** No algorithm specified */
            errors++;
        } else if (params->alg->alg != NULL && params->alg->mb_alg != NULL) {
            /** Both algorithms specified */
            errors++;
        }
        if (params->buffer_blocks >= 3 && params->alg->mb_alg == NULL) {
            errors++;
        }
    }
    return errors;
}

unsigned long execute_product_simulation(product_params * params) {
    if (verify_params(params)) {
        return 0;
    }
    if (params->buffer_blocks <= 3) {
        return params->alg->mb_alg(params->blk->r_table, params->blk->s_table, params->blk->r_blocks, params->blk->s_blocks, params->buffer_blocks);
    } else {
        return params->alg->alg(params->blk->r_table, params->blk->s_table, params->blk->r_blocks, params->blk->s_blocks);
    }
}
