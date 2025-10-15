#ifndef _TABLES_MANAGER_H
#define _TABLES_MANAGER_H
#include <stdlib.h>

/** 
 * Components on which execute the product simulation
 * @param r_table First table
 * @param s_table Second table
 * @param r_blocks Number of blocks in the first table
 * @param s_blocks Number of blocks in the second table
 */
typedef struct {
    /** First table */
    char * r_table;
    /** Second table */
    char * s_table;
    /** Number of blocks in the first table */
    unsigned long r_blocks;
    /** Number of blocks in the second table */
    unsigned long s_blocks;
} tables;

/** 
 * Initialize the tables structure
 * @param r_table First table
 * @param s_table Second table
 * @param r_blocks Number of blocks in the first table
 * @param s_blocks Number of blocks in the second table
 * @return Pointer to the initialized blocks structure
 */
tables * init_tables(char * r_table, char * s_table, const unsigned long r_blocks, const unsigned long s_blocks);

/** 
 * Free the memory allocated for the tables structure and all its components
 * @param blk Pointer to the tables structure to free
 * @param free_tables If true, also free the tables inside the structure
 */
void free_tables(tables * blk, const char free_tables);

#endif
