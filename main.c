#include "checker.h"
#include "grid.h"
#include "parallel.h"
#include <stdio.h>
//#include <stdlib.h>
#include <pthread.h>
//Brian S. Callies
//CSC410

int main() {
    Grid g = {
            .rows = 12,
            .cols = 20,
            .grid = NULL,
            .high_number = 20,
            .generations = 10,
            .seed = 2};

    allocate_grid(&g);
    fillGrid(&g);
    print_parameters(&g);

    printf("Generation 1:\n");
    print_grid(&g);
    printf("\n");

    for (int gen = 2; gen <= g.generations; gen++) {
        printf("Generation %d:\n", gen);
        //update_grid(&g);
        int NUM_THREADS = 4;  // This can be adjusted as needed
        WorkUnit work_units[NUM_THREADS];
        parallel_update_grid(&g, NUM_THREADS);

        print_grid(&g);
        printf("\n");
        //printf("Total checks: %d\n", total_checks(workUnits, NUM_THREADS));
        printf("Total checks: %d\n", total_checks(work_units, NUM_THREADS));

    }

    free_grid(&g);
    return 0;
}
