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

Use version control (like Git) if you aren't already. This allows you to keep track of changes, experiment without fear, and revert back if something goes wrong.
Test often. After every major change, ensure your code runs without errors and gives expected outputs.
Backup your work. In addition to version control, regularly backup your work in a secondary location.
Given the above breakdown, I would recommend starting with organizing your files and setting up the base grid correctly. Once that's in place, you can begin adding the additional features and requirements one at a time. Always test as you go along to ensure that each added feature works as expected.
