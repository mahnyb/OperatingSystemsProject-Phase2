// Kernel Space System Call Function Code: This will go to  /usr/src/kernel-source-2.4.27/fs

include <linux/mysyscall.h>

asmlinkage int sys_set_lottery_scheduler(int enabled){
	// Implement the logic here
	return enabled;
 }