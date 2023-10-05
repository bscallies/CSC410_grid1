#ifndef GRID_H
#define GRID_H
//Brian S. Callies
//CSC410
typedef struct {
    int rows;
    int cols;
    int** grid;
    int high_number;
    int generations;
    int seed;
} Grid;

void allocate_grid(Grid* g);
void fillGrid(Grid* g);
//int sum_neighbors(Grid* g, int i, int j, int* checks);
int update_cell_value(int currentValue, int sum);
void update_grid(Grid* g);
void print_grid(Grid* g);
void free_grid(Grid* g);
void print_parameters(const Grid* g);


#endif // GRID_H
