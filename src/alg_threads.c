#include "alg_threads.h"

void * run_algorithm(void * params) {
    product_t * p = (product_t *) params;
    (p->result) = execute_product_simulation(p->params);
    pthread_exit(NULL);
}

product_t * start_alg(product_params* params) {
    product_t * p = (product_t *) malloc(sizeof(product_t));
    if (p != NULL) {
        p->params = params;
        p->result = 0;
        if (!pthread_create(&(p->thread), NULL, run_algorithm, (void *)p)) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

unsigned long join_alg(product_t* p) {
    unsigned long res = 0;
    if (p != NULL) {        
        pthread_join(p->thread, NULL);
        res = p->result;
        free(p);
    }
    return res;
}

/** 
 * Table thread initializer
 */
void * init_t(void * arg) {
    unsigned long * size = (unsigned long *) arg;
    char * table = gen_table(*size);
    return (void *) table;
}

tables * init_rs(const unsigned long r_blocks, const unsigned long s_blocks) {
    /** Table initializer thread */
    pthread_t r_t, s_t;
    /** Tables */
    char * r = NULL, * s = NULL;
    /** Tables structure */
    tables * tbl = NULL;
    
    pthread_create(&r_t, NULL, init_t, (void *)&r_blocks);
    pthread_create(&s_t, NULL, init_t, (void *)&s_blocks);
    pthread_join(r_t, (void **)&r);
    pthread_join(s_t, (void **)&s);

    tbl = init_tables(r, s, r_blocks, s_blocks);
    return tbl;
}
