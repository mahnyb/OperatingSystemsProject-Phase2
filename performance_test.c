#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <linux/set_lottery_scheduler.h>

// Function to enable the lottery scheduler
void enable_lottery_scheduler() {
    int enabled = 1;
    if (set_lottery_scheduler(enabled) != 0) {
        perror("set_lottery_scheduler");
        exit(EXIT_FAILURE);
    }
    printf("Lottery scheduler enabled\n");
}

// CPU-intensive task
void cpu_intensive_task(int task_number) {
    char filename[256];
    sprintf(filename, "task_output_%d.txt", task_number);
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    clock_t start_time = clock();
    long i = 0;
    for (i ; i < 1000000; i++) {
        if (i % 10000000 == 0) {
            fprintf(file, "Task %d, progress: %ld%%\n", task_number, (i / 1000000) * 10);
        }
    }
    clock_t end_time = clock();
    double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    fprintf(file, "Task %d completed in %f seconds\n", task_number, cpu_time_used);
    fclose(file);
}

int main() {
    enable_lottery_scheduler();

    int num_tasks = 5; 
    pid_t pids[num_tasks];

    int i = 0
    for (i; i < num_tasks; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            // Child process
            cpu_intensive_task(i + 1);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all child processes to diee
    int j = 0;
    for (j; i < num_tasks; j++) {
        waitpid(pids[j], NULL, 0);
    }

    printf("All tasks completed. Check task_output_*.txt files for details.\n");
    return 0;
}