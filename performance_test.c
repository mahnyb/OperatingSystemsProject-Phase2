#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <linux/set_lottery_scheduler.h>

// Function to enable or disable the lottery scheduler
void lottery_scheduler(int enabled) {
    if (set_lottery_scheduler(enabled) != 0) {
        perror("set_lottery_scheduler");
        exit(EXIT_FAILURE);
    }
    printf("Lottery scheduler %s\n", enabled ? "enabled" : "disabled");
}

// CPU-intensive task performed by each process
void cpu_intensive_task() {
    long i = 0;
    volatile long result;  // Using volatile to prevent optimization
    for (i; i < 100000000; i++) {
        result = i % 123;  // Modulus operation
    }
}

void print_time_difference(struct timespec *start, struct timespec *end) {
    if (end->tv_nsec < start->tv_nsec) {
        // Handle the nanoseconds rollover
        end->tv_sec = end->tv_sec - start->tv_sec - 1;
        end->tv_nsec = end->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        end->tv_sec = end->tv_sec - start->tv_sec;
        end->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
    double time_in_seconds = end->tv_sec + end->tv_nsec * 1e9;
    printf("Time taken: %.10f seconds\n", time_in_seconds);
}

int main() {
    const int num_tasks = 10;
    pid_t pids[num_tasks];
    struct timespec start, end;
    int i;

    // Measure time with the default scheduler
    lottery_scheduler(0);  // Disable lottery scheduler
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < num_tasks; i++) {
        pids[i] = fork();
        if (pids[i] == 0) { // Child process
            cpu_intensive_task();
            exit(EXIT_SUCCESS);
        }
    }
    for (i = 0; i < num_tasks; i++) {
        waitpid(pids[i], NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_time_difference(&start, &end);

    // Enable lottery scheduler and measure time
    lottery_scheduler(1);  // Enable lottery scheduler
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < num_tasks; i++) {
        pids[i] = fork();
        if (pids[i] == 0) { // Child process
            cpu_intensive_task();
            exit(EXIT_SUCCESS);
        }
    }
    for (i = 0; i < num_tasks; i++) {
        waitpid(pids[i], NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_time_difference(&start, &end);

    return 0;
}
