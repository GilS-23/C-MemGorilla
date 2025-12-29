#include "mem_tracker.h"
#include <stdio.h>

int main() {
    printf("Starting Memory Tracker Test...\n\n");

    int* p1 = (int*)malloc(10 * sizeof(int));
    //free(p1);
    char* p2 = (char*)malloc(50);
   // free(p2);
    double* p3 = (double*)calloc(5, sizeof(double));
    //free(p3);
    int* p4 = (int*)malloc(20);
    p4 = (int*)realloc(p4, 40);
    free(p4);
    //free(p4);
    print_leak_report();
    return 0;
}