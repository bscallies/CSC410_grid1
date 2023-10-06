#include "checker.h"
#include "grid.h"
#include "parallel.h"
#include <stdio.h>
#include <stdlib.h>
//Brian S. Callies
//CSC410

void allocate_grid(Grid* g) {
    g->grid = (int**)malloc(g->rows * sizeof(int*));
    for (int i = 0; i < g->rows; i++) {
        g->grid[i] = (int*)malloc(g->cols * sizeof(int));
    }
}

void fillGrid(Grid* g) {
    srand(g->seed);
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            g->grid[i][j] = rand() % g->high_number;
        }
    }
}
/*
int sum_neighbors(Grid* g, int i, int j, int* checks) {
    int sum = 0;
    *checks = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (i + dx >= 0 && i + dx < g->rows && j + dy >= 0 && j + dy < g->cols) {
                sum += g->grid[i + dx][j + dy];
                (*checks)++;
            }
        }
    }

    usleep(sum % 11 * 1500); //checker
    return sum;
}*/

int update_cell_value(int currentValue, int sum) {
    if (sum % 10 == 0) {
        return 0;
    } else if (sum < 50) {
        return currentValue + 3;
    } else if (sum > 50 && sum < 150) {
        return (currentValue - 3 >= 0) ? currentValue - 3 : 0;
    } else {
        return 1;
    }
} //NEW

void update_grid(Grid* g) {
    int temp[g->rows][g->cols];
    int checks = 0;
    int total_checks = 0;  // Keep track of total checks

    WorkUnit dummy_work; //scheisse work around
    dummy_work.checks = 0;

    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            int sum = sum_neighbors(g, i, j, &checks);
            total_checks += checks;
            temp[i][j] = update_cell_value(g->grid[i][j], sum);
        }
    }

    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            g->grid[i][j] = temp[i][j];
        }
    }
}




void print_grid(Grid* g) {
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            printf("%2d ", g->grid[i][j]);
        }
        printf("\n");
    }
}

void free_grid(Grid* g) {
    for (int i = 0; i < g->rows; i++) {
        free(g->grid[i]);
    }
    free(g->grid);
}

void print_parameters(const Grid* g) {
    printf("Grid parameters:\n");
    printf("Rows: %d, Cols: %d \n", g->rows, g->cols);
    printf("Seed: %d,  High: %d \n\n", g->seed, g->high_number);
}

