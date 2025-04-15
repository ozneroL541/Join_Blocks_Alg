#ifndef _MODIFIED_MULTI_BLOCK_ALG_H_
    #define _MODIFIED_MULTI_BLOCK_ALG_H_
    /** 
     * Modified algorithm to calculate the product of two tables with multiple 
     * blocks avaiable in the buffer.
     * @param s_table First table.
     * @param r_table Second table.
     * @return The number of blocks read.
     */
    unsigned long modified_multi_block_alg(const char *s_table, const char *r_table);
#endif
