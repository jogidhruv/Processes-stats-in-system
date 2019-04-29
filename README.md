# Processes-stats-in-system
Implements a kernel module which prints current process stats in the dmesg logs

The stats will include following details:

1) Percentage of processes in TASK_RUNNING state
2) PID of all the tasks
3) PID of parent task of all the tasks
4) State of given task

To test the kernel module (Run these commands with superuser privileges)

1) make
2) insmod kernel_module.ko     (to insert module)
3) dmesg                       (check your process stats in debug logs)
4) rmmod kernel_module.ko      (to remove the module)
