#include <pthread.h>

void index_to_2d(int index, int* row, int* col, int cols) {
    *row = index / cols;
    *col = index % cols;
}