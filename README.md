# CSC410_grid1
For grid1 project due 10-13

Organize Your Directory and Files:

Create a directory named Grid1.
Inside Grid1, you should have the following files: single.c, threadstat.c, threaddyn.c, and ompgrid.c.
Set Up Your Grid:

The grid should be of size 12x20 for the final report.
Initialize the grid using the call: fillGrid(A, 2, 20);. Make sure you understand the function and its arguments to avoid mistakes.
For testing purposes, your first row of grid A should be: 10 19 8 15 1 18.
Add Delay in Checker Function:

Introduce a delay in your checker function using the usleep(s%11*1500); where s is the sum of neighbors before adjustment.
Remember to include the header #include <unistd.h>.
Timing:

Implement timing mechanisms in your code to measure the runtime of sequential code, pthread, and OpenMP samples.
You need to run the code 10 times (generations) and print the grid after each generation.
Pthreads:

Implement your code to handle both 4 and 12 threads. This should be a variable in your code that can be easily adjusted.
It's preferred to not create/kill threads during every repetition.
You need two versions: one for static scheduling and one for dynamic scheduling.
You should be able to report how many checks were performed by each thread. The total should be 
12×20×9


OpenMP:

Your code should have sections that differentiate between static and dynamic scheduling, and it should be easy to adjust the number of threads.
Reporting:

Prepare an overall timing table comparing the runtime for all versions: sequential, pthread (static and dynamic with 4 and 12 threads), and OpenMP (static and dynamic with 4 and 12 threads).
Include comments and explanations in your report.
Be prepared to provide code fragments, specific data values from the grid at specific times & locations, as mentioned in the requirements.
General Tips:

=Open MP=
Your code should have sections that differentiate between static and dynamic scheduling, and it should be easy to adjust the number of threads.
Reporting: Prepare an overall timing table comparing the runtime for all versions: sequential, pthread (static and dynamic with 4 and 12 threads), and OpenMP (static and dynamic with 4 and 12 threads).
Include comments and explanations in your report.
Be prepared to provide code fragments, specific data values from the grid at specific times & locations, as mentioned in the requirements.
General Tips:

Directive-Based Approach: OpenMP uses a directive-based approach to parallelism. By adding special compiler directives (pragmas) to your code, you can instruct the compiler where and how to parallelize operations. This means you can start with serial code and then incrementally parallelize it using OpenMP directives.

Shared Memory Model: OpenMP is designed for multi-threaded programming on systems with shared memory. This is different from distributed memory systems where each processor has its own local memory.

Portability: OpenMP is supported by many compilers and platforms, making it relatively portable. Programs written using OpenMP can be compiled for different systems without changing the source code.

Scalability: OpenMP programs can be scaled by simply increasing the number of threads. The same code can run on a single-core machine (using one thread) or a multi-core machine with several threads.

Key Features:

Loop Parallelism: Easily parallelize loops to run on multiple threads.
Task Parallelism: Define standalone parallel tasks.
Data Environment: Control data scope (private, shared) and data handling (reduction operations).
Synchronization: Use critical sections, barriers, and locks to synchronize threads.
Runtime Library: OpenMP provides a runtime library that allows querying and setting runtime properties, like the number of threads.
