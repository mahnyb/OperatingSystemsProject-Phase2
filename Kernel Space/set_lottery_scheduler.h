// Kernel Space System Call Header: This will go to  /usr/src/kernel-source-2.4.27/include/linux

#ifndef __LINUX_SET_LOTTERY_SCHEDULER_H
#define __LINUX_SET_LOTTERY_SCHEDULER_H
#include <linux/linkage.h>

extern asmlinkage int sys_set_lottery_scheduler(int enabled);

#endif