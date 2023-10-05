#ifndef CHECKER_H
#define CHECKER_H
#include "grid.h"
//Brian S. Callies
//CSC410

// Prototypes for checking functions

int sum_neighbors(Grid* g, int i, int j, int* checks);
void delay_based_on_sum(int sum);

#endif
