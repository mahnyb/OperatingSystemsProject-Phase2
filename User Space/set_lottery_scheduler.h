// User Space System Call Header: This will go to  /usr/include/linux

#include <linux/unistd.h>
#include <errno.h>
extern int errno;

_syscall1(int, set_lottery_scheduler, int, enabled);
