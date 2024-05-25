#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <linux/set_lottery_scheduler.h>

void cpu_intensive_task() {
    long i;
    double result = 0.0;
    for (i = 0; i < 100000000; i++) {
        result = (i * 3.14 * 2.71) + (i % 10); 
    }
}

double elapsed_time(struct timeval start, struct timeval end) {
    double start_seconds = start.tv_sec + start.tv_usec / 1e6;
    double end_seconds = end.tv_sec + end.tv_usec / 1e6;
    return end_seconds - start_seconds;
}

void enable_lottery_scheduler() {
    int enabled = 1;
    if (set_lottery_scheduler(enabled) != 0) {
        perror("set_lottery_scheduler");
        exit(EXIT_FAILURE);
    }
    printf("Lottery scheduler enabled\n");
}

int main() {
    struct timeval start_time, end_time;
    int i, status;
    pid_t pid;

    printf("Testing default scheduler...\n");
    gettimeofday(&start_time, NULL);

    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) { // Child process
            cpu_intensive_task();
            exit(EXIT_SUCCESS);
        }
    }

    while (wait(&status) > 0); // Wait for all children to dieee

    gettimeofday(&end_time, NULL);
    printf("Default scheduler time: %f seconds\n", elapsed_time(start_time, end_time));

    enable_lottery_scheduler();

    printf("Testing lottery scheduler...\n");
    gettimeofday(&start_time, NULL);

    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) { // Child process
            cpu_intensive_task();
            exit(EXIT_SUCCESS);
        }
    }

    while (wait(&status) > 0); // Wait for all children to diee

    gettimeofday(&end_time, NULL);
    printf("Lottery scheduler time: %f seconds\n", elapsed_time(start_time, end_time));

    return 0;
}
