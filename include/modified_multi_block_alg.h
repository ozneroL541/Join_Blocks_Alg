#ifndef _MODIFIED_MULTI_BLOCK_ALG_H_
    #define _MODIFIED_MULTI_BLOCK_ALG_H_
    /** 
     * Modified algorithm to calculate the product of two tables with multiple 
     * blocks avaiable in the buffer.
     * @param r_table First table.
     * @param s_table Second table.
     * @return The number of blocks read.
     */
    unsigned long modified_multi_block_alg(const char *r_table, const char *s_table);
#endif
