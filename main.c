#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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
    int start;    // start index for assigned work to each thread
    int end;      // end index
    Grid* g;      // Pointer to the main grid structure
    int checks;   // Number of checks made by this thread
    int thread_id;
} WorkUnit;
pthread_key_t thread_id_key;
pthread_mutex_t count_mutex; //safe guards threads
#define MAX_THREADS 12



//Protofunctions
void run_with_threads(Grid* g, WorkUnit* work_units, int num_threads);
void allocate_grid(Grid* g);
void fillGrid(Grid* g);
void print_parameters(const Grid* g);
void print_grid(Grid* g);
void free_grid(Grid* g);
void delay_based_on_sum(int sum);
int sum_neighbors(Grid* g, int i, int j);
int update_cell_value(int currentValue, int sum);
void* thread_update_grid(void* arg);
int parallel_update_grid(Grid* g, WorkUnit* work_units, int num_threads);
int total_checks(WorkUnit* workUnits, int numThreads);

void initialize(Grid* g, WorkUnit* work_units, int numThreads) {

    allocate_grid(g);
    fillGrid(g);
    print_parameters(g);

    printf("Generation 1:\n");
    print_grid(g);
    printf("\n");

    int cells_per_thread = (g->rows * g->cols) / numThreads;
    for (int t = 0; t < numThreads; t++) {
        work_units[t].g = g;
        work_units[t].start = t * cells_per_thread;
        work_units[t].checks = 0; // Initializing checks
        work_units[t].thread_id = t; //thread id
        if (t == numThreads - 1) {
            work_units[t].end = (g->rows * g->cols) - 1;
        } else {
            work_units[t].end = (t + 1) * cells_per_thread - 1;
        }
    }
}

int main() {
    Grid g = {
            .rows = 12,
            .cols = 20,
            .grid = NULL,
            .high_number = 20,
            .generations = 10,
            .seed = 2
    };

    WorkUnit workUnits[MAX_THREADS];
    pthread_mutex_t count_mutex;

    int thread_counts[] = {4, 12}; // Runs once with x threads for each input here
    int num_runs = sizeof(thread_counts) / sizeof(int);

    for (int i = 0; i < num_runs; i++) {
        run_with_threads(&g, workUnits, thread_counts[i]);
    }

    free_grid(&g);
    pthread_key_delete(thread_id_key);
    pthread_mutex_destroy(&count_mutex);
    return 0;
}

//FUNCTIONS
void run_with_threads(Grid* g, WorkUnit* work_units, int num_threads) {
    clock_t start, end;
    double cpu_time_used;

    initialize(g, work_units, num_threads);
    for (int t = 0; t < num_threads; t++) {
        work_units[t].checks = 0;
    }

    start = clock();
    for (int gen = 2; gen <= g->generations; gen++) {
        printf("Generation %d with %d threads:\n", gen, num_threads);
        parallel_update_grid(g, work_units, num_threads);
        print_grid(g);
        printf("Total checks: %d\n\n", total_checks(work_units, num_threads));
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken with %d threads: %f seconds\n", num_threads, cpu_time_used);
}


//int sum_neighbors(Grid* g, int i, int j, WorkUnit* work) {
int sum_neighbors(Grid* g, int i, int j) {
    int sum = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int ni = i + dx;
            int nj = j + dy;
            if (ni >= 0 && ni < g->rows && nj >= 0 && nj < g->cols && !(dx == 0 && dy == 0)) {
                sum += g->grid[ni][nj];
                //printf("DEBUG: Thread %d - Adding value from neighbor cell (%d, %d) to cell (%d, %d)\n", tid, ni, nj, i, j);
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
        //printf("DEBUG: Thread %d checks: %d\n", i, workUnits[i].checks);
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
    pthread_setspecific(thread_id_key, (void*)(intptr_t)work->thread_id);
    Grid* g = work->g;

    for (int idx = work->start; idx <= work->end; idx++) {  // Changed to 'start' and 'end'
        int i, j;
        //printf("Thread ID: %d, Start index: %d, End index: %d\n", work->thread_id, work->start, work->end);
        index_to_2d(idx, &i, &j, g->cols);
        int sum = sum_neighbors(g, i, j);
        pthread_mutex_lock(&count_mutex);
        work->checks++;
        pthread_mutex_unlock(&count_mutex);
        g->grid[i][j] = update_cell_value(g->grid[i][j], sum);
    }
    //printf("DEBUG: Thread [%d - %d] performed %d checks\n", work->start, work->end, work->checks);
    pthread_exit(NULL);
}

int parallel_update_grid(Grid* g, WorkUnit* work_units, int num_threads) {
    //printf("DEBUG: Starting parallel_update_grid for generation\n");
    pthread_t threads[num_threads];
    int cells_per_thread = (g->rows * g->cols) / num_threads;

    for (int t = 0; t < num_threads; t++) {
        work_units[t].g = g;
        work_units[t].start = t * cells_per_thread;  // Changed to 'start'
        if (t == num_threads - 1) {
            work_units[t].end = (g->rows * g->cols) - 1;  // Changed to 'end'
        } else {
            work_units[t].end = (t + 1) * cells_per_thread - 1;  // Changed to 'end'
        }
        work_units[t].thread_id = t;
        pthread_create(&threads[t], NULL, thread_update_grid, &work_units[t]);
        //printf("Thread ID: %d, Start index: %d, End index: %d\n", work_units[t].thread_id, work_units[t].start, work_units[t].end);
        printf("Thread ID: %d, Start index: %d, End index: %d, Check count: %d\n",
               work_units[t].thread_id, work_units[t].start, work_units[t].end, work_units[t].checks);
    }
    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }
    int total = total_checks(work_units, num_threads);
    return total;
}
//END