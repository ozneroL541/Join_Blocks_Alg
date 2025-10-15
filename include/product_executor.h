#ifndef _PRODUCT_EXECUTOR_H
#define _PRODUCT_EXECUTOR_H
#include "tables_manager.h"

/** 
 * Union of function pointers for different types of algorithms
 * @param alg Pointer to a classic algorithm
 * @param mb_alg Pointer to a multi-block algorithm
 */
typedef union {
    /** Pointer to a classic algorithm */
    void * (*alg)(const char *, const char *, const unsigned long, const unsigned long);
    /** Pointer to a multi-block algorithm */
    void * (*mb_alg)(const char *, const char *, const unsigned long, const unsigned long, const unsigned long *);
} algorithm;

/** 
 * Parameters for executing the product simulation
 * @param blk Pointer to the tables structure
 * @param buffer_blocks Number of blocks in the buffer
 * @param algorithm Function pointer to the algorithm to use
 */
typedef struct {
    /** Pointer to the tables structure */
    tables * blk;
    /** Number of blocks in the buffer */
    unsigned long buffer_blocks;
    /** Algorithm to use */
    algorithm * alg;
} product_params;

/**
 * Initialize a classic algorithm
 * @param alg Pointer to the classic algorithm function
 * @return Pointer to the initialized algorithm structure
 */
algorithm * init_alg_c(void * (*alg)(const char *, const char *, const unsigned long, const unsigned long));

/**
 * Initialize a multi-block algorithm
 * @param mb_alg Pointer to the multi-block algorithm function
 * @return Pointer to the initialized algorithm structure
 */
algorithm * init_alg_mb(void * (*mb_alg)(const char *, const char *, const unsigned long, const unsigned long, const unsigned long *));


/** 
 * Initialize the product_params structure
 * @param blk Pointer to the tables structure
 * @param alg Pointer to the algorithm structure
 * @param buffer_blocks Number of blocks in the buffer
 * @return Pointer to the initialized product_params structure
 */
product_params * init_product_params(tables * blk, algorithm * alg, const unsigned long buffer_blocks);

/** 
 * Free the memory allocated for the product_params structure
 * @param params Pointer to the product_params structure to free
 */
void free_product_params(product_params * params);

/** 
 * Execute the product simulation
 * @param params Pointer to the product_params structure
 * @return 0 on success
 */
char execute_product_simulation(product_params * params);

#endif
