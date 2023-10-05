#include "grid.h"
#include <stdio.h>
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
        update_grid(&g);
        print_grid(&g);
        printf("\n");
    }

    free_grid(&g);
    return 0;
}
