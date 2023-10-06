#ifndef PARALLEL_H
#define PARALLEL_H

#include "grid.h"
#include <pthread.h>

typedef struct {
    int start;    // Start index for this thread's work
    int end;      // End index for this thread's work
    Grid* g;      // Pointer to the main grid structure
    int checks;   // Number of checks made by this thread
} WorkUnit;

void* thread_update_grid(void* arg);
//void parallel_update_grid(Grid* g, int num_threads);
int parallel_update_grid(Grid* g, int numThreads);


#endif
