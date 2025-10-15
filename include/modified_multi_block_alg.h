#ifndef _MODIFIED_MULTI_BLOCK_ALG_H_
    #define _MODIFIED_MULTI_BLOCK_ALG_H_
    /** 
     * Modified algorithm to calculate the product of two tables with multiple 
     * blocks avaiable in the buffer.
     * @param r_table First table.
     * @param s_table Second table.
     * @param r_blocks Number of blocks in the first table.
     * @param s_blocks Number of blocks in the second table.
     * @param buffer_blocks Number of blocks in the buffer.
     * @return The number of blocks read.
     */
    unsigned long modified_multi_block_alg(const char *r_table, const char *s_table, const unsigned long r_blocks, const unsigned long s_blocks, const unsigned long buffer_blocks);
#endif
