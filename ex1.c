#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    clock_t start_time = clock();

    int pid1 = fork();

    if (pid1 < 0) {
        return 1;
    }

    if (pid1 == 0) {
        clock_t start = clock();
        
        printf("Process id of first child is %d, id of parent is %d\n", getpid(), getppid());

        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        printf("Execution time of first child is %.2f ms\n\n", elapsed_ms);
    } 
    else {
        int pid2 = fork();

        if (pid2 < 0) {
            return 1;
        }

        if (pid2 == 0) {
            clock_t start = clock();
            
            printf("Process id of second child is %d, id of parent is %d\n", getpid(), getppid());

            clock_t end = clock();
            double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
            printf("Execution time of second child is %.2f ms\n\n", elapsed_ms);
        } 
        else {
            clock_t start = clock();
            
            printf("ID of main process is %d, id of parent is %d\n", getpid(), getppid());

            clock_t end = clock();
            double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
            printf("Main process execution time: %.2f ms\n\n", elapsed_ms);
        }
    }

    return 0;
}