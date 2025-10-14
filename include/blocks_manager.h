#ifndef _BLOCKS_MANAGER_H
#define _BLOCKS_MANAGER_H

/** 
 * Components on which execute the product simulation
 * @param r_table First table
 * @param s_table Second table
 * @param r_blocks Number of blocks in the first table
 * @param s_blocks Number of blocks in the second table
 * @param buffer_blocks Number of blocks in the buffer
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
    /** Number of blocks in the buffer */
    unsigned long buffer_blocks;
} blocks;

/** 
 * Initialize the blocks structure
 * @param r_table First table
 * @param s_table Second table
 * @param r_blocks Number of blocks in the first table
 * @param s_blocks Number of blocks in the second table
 * @param buffer_blocks Number of blocks in the buffer
 * @return Pointer to the initialized blocks structure
 */
blocks * init_blocks(char * r_table, char * s_table, const unsigned long r_blocks, const unsigned long s_blocks, const unsigned long buffer_blocks);

/** 
 * Free the memory allocated for the blocks structure and all its components
 * @param blk Pointer to the blocks structure to free
 * @param free_tables If true, also free the tables inside the structure
 */
void free_blocks(blocks * blk, const char free_tables);

#endif
