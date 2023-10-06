#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

typedef struct {
    int start;    // Start index for this thread's work
    int end;      // End index for this thread's work
    Grid* g;      // Pointer to the main grid structure
    int checks;   // Number of checks made by this thread
} WorkUnit;

//Protofunctions
void allocate_grid(Grid* g);
void fillGrid(Grid* g);
void print_parameters(const Grid* g);
void print_grid(Grid* g);
void free_grid(Grid* g);
void delay_based_on_sum(int sum);
int sum_neighbors(Grid* g, int i, int j, WorkUnit* work);
int update_cell_value(int currentValue, int sum);
void* thread_update_grid(void* arg);
int parallel_update_grid(Grid* g, int numThreads);
int total_checks(WorkUnit* workUnits, int numThreads);

int main() {
    Grid g = {
            .rows = 12,
            .cols = 20,
            .grid = NULL,
            .high_number = 20,
            .generations = 10,
            .seed = 2
    };
    allocate_grid(&g);
    fillGrid(&g);
    print_parameters(&g);

    printf("Generation 1:\n");
    print_grid(&g);
    printf("\n");

    for (int gen = 2; gen <= g.generations; gen++) {
        printf("Generation %d:\n", gen);
        int NUM_THREADS = 4;  // This can be adjusted as needed
        int cells_per_thread = (g.rows * g.cols) / NUM_THREADS;
        WorkUnit work_units[NUM_THREADS];

        for (int t = 0; t < NUM_THREADS; t++) {
            work_units[t].g = &g;
            work_units[t].start = t * cells_per_thread;
            if (t == NUM_THREADS - 1) {
                work_units[t].end = (g.rows * g.cols) - 1;
            } else {
                work_units[t].end = (t + 1) * cells_per_thread - 1;
            }
            work_units[t].checks = 0;
        }

        parallel_update_grid(&g, NUM_THREADS);

        print_grid(&g);
        printf("\n");
        printf("Total checks: %d\n", total_checks(work_units, NUM_THREADS));
    }
    free_grid(&g);
    return 0;
}


//FUNCTIONS
//checker.c functions
int sum_neighbors(Grid* g, int i, int j, WorkUnit* work) {
    int sum = 0;
    //*checks = 0;  // Initialize checks

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (i + dx >= 0 && i + dx < g->rows && j + dy >= 0 && j + dy < g->cols) {
                sum += g->grid[i + dx][j + dy];
                //(*checks)++;
                work->checks++;
            }
        }
    }

    delay_based_on_sum(sum);
    return sum;
}

void delay_based_on_sum(int sum) {
    usleep(sum % 11 * 1500);  // adding the delay here
}


int total_checks(WorkUnit* workUnits, int numThreads) {
    int total = 0;
    for (int i = 0; i < numThreads; i++) {
        total += workUnits[i].checks;
    }
    return total;
}

//grid.c functions
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
//END