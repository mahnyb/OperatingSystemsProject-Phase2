// Kernel Space System Call Function Code: This will go to  /usr/src/kernel-source-2.4.27/fs

#include <linux/set_lottery_ticket.h>
#include <sched.c> // global variable sched_lottery is defined in sched.c

asmlinkage int sys_set_lottery_scheduler(int enabled){
	// Implement the logic here
	sched_lottery = enabled;
 }