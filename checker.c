#include "checker.h"
#include <unistd.h>

int sum_neighbors(Grid* g, int i, int j, int* checks) {
    int sum = 0;
    *checks = 0;  // Initialize checks

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (i + dx >= 0 && i + dx < g->rows && j + dy >= 0 && j + dy < g->cols) {
                sum += g->grid[i + dx][j + dy];
                (*checks)++;
            }
        }
    }

    delay_based_on_sum(sum);
    return sum;
}

void delay_based_on_sum(int sum) {
    usleep(sum % 11 * 1500);  // adding the delay here
}
