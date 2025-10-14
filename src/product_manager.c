#include "product_manager.h"

blocks * init_blocks(char * r_table, char * s_table, const unsigned long r_blocks, const unsigned long s_blocks, const unsigned long buffer_blocks) {
    blocks * blk = (blocks *)malloc(sizeof(blocks));
    if (blk != NULL) {
        blk->r_table = r_table;
        blk->s_table = s_table;
        blk->r_blocks = r_blocks;
        blk->s_blocks = s_blocks;
        if (buffer_blocks <= 3){
            blk->buffer_blocks = 3;
        } else {
            blk->buffer_blocks = buffer_blocks;
        }
    }
    return blk;
}

void free_blocks(blocks * blk, const char free_tables) {
    if (blk != NULL) {
        if (free_tables) {
            if (blk->r_table != NULL){
                free(blk->r_table);
            }
            if (blk->s_table != NULL){
                free(blk->s_table);
            }
        }
        free(blk);
    }
}
