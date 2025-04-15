#ifndef _BUFFER_BLOCKS_H_
    #define _BUFFER_BLOCKS_H_
    /** Number of blocks in the buffer */
    #define BUFFER_BLOCKS 8
    /** 
     * Make the product of the first block with the rest of the blocks.
     * @param buff The buffer containing the blocks
     * @param max_blocks Number of blocks to use for the product in the buffer
    */
    void multi_product(const char buff[], const unsigned long max_blocks);
#endif
