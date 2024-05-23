#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/set_lottery_scheduler.h>


int main() {
    int enabled = 1;
    if (set_lottery_scheduler(enabled) != 0) {
        perror("set_lottery_scheduler");
        return 1;
    }
    printf("Lottery scheduler enabled\n");
    return 0;
}
