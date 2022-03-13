# binary_tree_thread_generator

Implement a C program, thread_generation, that receives a command line parameter
n.
The parent thread creates two threads and waits for their termination.
Each further thread creates the other two threads, and it awaits their termination. 
Tread creation stops after 2^n threads have been created, i.e., the ones that stand
on the leaves of a tree with 2^n leaves.
