#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/set_lottery_scheduler.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int enabled = 1;
    if (set_lottery_scheduler(enabled) != 0) {
        perror("set_lottery_scheduler");
        return 1;
    }
    printf("Lottery scheduler enabled\n");

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        int i = 0;
        for (i; i < 10; i++) {
            printf("Child process: %d\n", i);
            sleep(1);
        }
    }
    else {
        // Parent process
        int i = 0;
        for (i; i < 10; i++) {
            printf("Parent process: %d\n", i);
            sleep(1);
        }
        wait(NULL);  // Wait for the child to finish
    }
    return 0;
}
