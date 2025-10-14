#include "product_executor.h"

algorithm * init_alg_c(void * (*alg)(const char *, const char *)) {
    algorithm * new_alg = (algorithm *)malloc(sizeof(algorithm));
    if (new_alg != NULL) {
        new_alg->alg = alg;
    }
    return new_alg;
}

algorithm * init_alg_mb(void * (*mb_alg)(const char *, const char *, const unsigned long *)) {
    algorithm * new_alg = (algorithm *)malloc(sizeof(algorithm));
    if (new_alg != NULL) {
        new_alg->mb_alg = mb_alg;
    }
    return new_alg;
}

product_params * init_product_params(blocks * blk, algorithm * alg, const char is_multi_block) {
    product_params * params = (product_params *)malloc(sizeof(product_params));
    if (params != NULL) {
        params->blk = blk;
        params->alg = alg;
        params->is_multi_block = is_multi_block;
    }
    return params;
}

void free_product_params(product_params * params) {
    if (params != NULL) {
        free_blocks(params->blk, 1);
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
        if (params->blk->buffer_blocks < 3) {
            /** Not enough blocks in the buffer to perform the join */
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
        if (params->is_multi_block && params->alg->mb_alg == NULL) {
            /** Invalid is_multi_block flag */
            errors++;
        }
    }
    return errors;
}

char execute_product_simulation(product_params * params) {
    {
        char errors = verify_params(params);
        if (errors) {
            return errors;
        }
    }
    if (params->is_multi_block) {
        params->alg->mb_alg(params->blk->r_table, params->blk->s_table, &(params->blk->buffer_blocks));
    } else {
        params->alg->alg(params->blk->r_table, params->blk->s_table);
    }    
    return 0;
}
