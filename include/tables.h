#ifndef _TABLES_H_
    #define _TABLES_H_
    /** R tables blocks' number */
    #define R_BLOCKS 65531
    /** 
     * S tables blocks' number 
     * @note Do not exceed 7000 for S_BLOCKS, it might cause segmentation fault
    */
    #define S_BLOCKS 65537

    /** First Table */
    extern char r_table[R_BLOCKS];
    /** Second Table */
    extern char s_table[S_BLOCKS];

    /**
     * Initializes the table with values.
     * @param table Pointer to the table to be initialized.
     * @param size Size of the table.
     */
    void init_table(char *table, const unsigned long size);

    /**
     * Computes the product of two blocks of the buffer.
     * @param block_buffer1 Pointer to the first block buffer.
     * @param block_buffer2 Pointer to the second block buffer.
     * @note This function is a placeholder and does not perform any actual computation.
     */
    void product(const char *block_buffer1, const char *block_buffer2);

    /**
     * Reads a block from the table and stores it in the buffer.
     * @param table_block Table's block to be read.
     * @param buffer_block Pointer to the buffer where the table's block will be stored.
     * @param counter Pointer to the counter that keeps track of the number of blocks read.
     */
    void read_block(const char table_block, char * buffer_block, unsigned long * counter);
#endif
