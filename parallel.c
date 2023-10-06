#include "parallel.h"
#include "checker.h"
#include <stdio.h>
#include <pthread.h>

void index_to_2d(int index, int* row, int* col, int cols) {
    *row = index / cols;
    *col = index % cols;
}

void* thread_update_grid(void* arg) {
    WorkUnit* work = (WorkUnit*)arg;
    Grid* g = work->g;

    for (int idx = work->start; idx <= work->end; idx++) {  // Changed to 'start' and 'end'
        int i, j;
        index_to_2d(idx, &i, &j, g->cols);

        //int sum = sum_neighbors(g, i, j, &work->checks);
        int sum = sum_neighbors(g, i, j, work);
        g->grid[i][j] = update_cell_value(g->grid[i][j], sum);
    }

    pthread_exit(NULL);
}

int parallel_update_grid(Grid* g, int num_threads) {
    pthread_t threads[num_threads];
    WorkUnit work_units[num_threads];
    int cells_per_thread = (g->rows * g->cols) / num_threads;

    for (int t = 0; t < num_threads; t++) {
        work_units[t].g = g;
        work_units[t].start = t * cells_per_thread;  // Changed to 'start'

        if (t == num_threads - 1) {
            work_units[t].end = (g->rows * g->cols) - 1;  // Changed to 'end'
        } else {
            work_units[t].end = (t + 1) * cells_per_thread - 1;  // Changed to 'end'
        }

        pthread_create(&threads[t], NULL, thread_update_grid, &work_units[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    int total = total_checks(work_units, num_threads);

    return total;
}
