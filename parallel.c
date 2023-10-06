#include "checker.h"
#include "grid.h"
#include "parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void index_to_2d(int index, int* row, int* col, int cols) {
    *row = index / cols;
    *col = index % cols;
}

// Thread function: Each thread will execute this function.
void* thread_update_grid(void* arg) {
    WorkUnit* work = (WorkUnit*)arg;
    Grid* g = work->g;

    for (int idx = work->start_index; idx <= work->end_index; idx++) {
        int i, j;
        index_to_2d(idx, &i, &j, g->cols);

        // using `i` and `j` to access the grid and perform the necessary operations
        //int sum = sum_neighbors(g, i, j, checks);
        int sum = sum_neighbors(g, row, col, workUnit); // workUnit is the WorkUnit pointer passed to the thread


        g->grid[i][j] = update_cell_value(g->grid[i][j], sum);
    }

    pthread_exit(NULL);
}

void parallel_update_grid(Grid* g, int num_threads) {
    pthread_t threads[num_threads];
    WorkUnit work_units[num_threads];
    int cells_per_thread = (g->rows * g->cols) / num_threads;

    for (int t = 0; t < num_threads; t++) {
        work_units[t].g = g;
        work_units[t].start_index = t * cells_per_thread;

        if (t == num_threads - 1) {  // If this is the last thread, handle any leftover cells.
            work_units[t].end_index = (g->rows * g->cols) - 1;
        } else {
            work_units[t].end_index = (t + 1) * cells_per_thread - 1;
        }

        pthread_create(&threads[t], NULL, thread_update_grid, &work_units[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }
}