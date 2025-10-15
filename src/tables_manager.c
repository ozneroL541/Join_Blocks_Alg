#include "tables_manager.h"

tables * init_tables(char * r_table, char * s_table, const unsigned long r_blocks, const unsigned long s_blocks) {
    /** Tables structure */
    tables * blk = NULL;
    if (r_blocks == 0 || s_blocks == 0) {
        return NULL;
    }
    blk = (tables *)malloc(sizeof(tables));
    if (blk != NULL) {
        blk->r_table = r_table;
        blk->s_table = s_table;
        blk->r_blocks = r_blocks;
        blk->s_blocks = s_blocks;
    }
    return blk;
}

void free_tables(tables * blk, const char free_tables) {
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
