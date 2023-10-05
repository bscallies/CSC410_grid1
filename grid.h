#ifndef GRID_H
#define GRID_H

typedef struct {
    int rows;
    int cols;
    int** grid;
} Grid;

void initialize_grid(Grid* g, int rows, int cols);
void fill_grid(Grid* g, int seed, int high);
void print_grid(Grid* g);
void update_grid(Grid* g);

#endif // GRID_H
