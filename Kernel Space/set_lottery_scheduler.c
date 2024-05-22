// Kernel Space System Call Function Code: This will go to  /usr/src/kernel-source-2.4.27/fs

#include <linux/set_lottery_ticket.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

extern int sched_lottery; // Declare the global variable

asmlinkage int sys_set_lottery_scheduler(int enabled){
	// Implement the logic here
	sched_lottery = enabled;
	return 0;
 }