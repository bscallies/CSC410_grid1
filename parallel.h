#ifndef PARALLEL_H
#define PARALLEL_H

#include "grid.h"
#include <pthread.h>

typedef struct {
    Grid* g;
    int start_index;
    int end_index;
} WorkUnit;

void* thread_update_grid(void* arg);
void parallel_update_grid(Grid* g, int num_threads);

#endif
