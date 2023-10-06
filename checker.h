#ifndef CHECKER_H
#define CHECKER_H
#include "grid.h"
#include "parallel.h"
//Brian S. Callies
//CSC410

//typedef struct WorkUnit WorkUnit;

// Prototypes for checking functions

//int sum_neighbors(Grid* g, int i, int j, int* checks);
int sum_neighbors(Grid* g, int i, int j, WorkUnit* work);

void delay_based_on_sum(int sum);
int total_checks(WorkUnit* workUnits, int numThreads);

#endif
