#include<linux/init.h>
#include<linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
MODULE_LICENSE("GPL");

//void calculate_stats();
int count = 0;
static const char *task_state_array[] = {
    "TASK_RUNNING",        /*  0 */
    "TASK_INTERRUPTIBLE",        /*  1 */
    "TASK_UNINTERRUPTIBLE",    /*  2 */
    "TASK_STOPPED",        /*  4 */
    "TASK_TRACED",    /*  8 */
    "EXIT_DEAD",        /* 16 */
    "EXIT_ZOMBIE"        /* 32 */
};

static inline const char * get_task_state(struct task_struct *tsk)
{
    unsigned int state = (tsk->state & (TASK_RUNNING |
                        TASK_INTERRUPTIBLE |
                        TASK_UNINTERRUPTIBLE |
                        TASK_STOPPED |
                        TASK_TRACED)) |
            (tsk->exit_state & (EXIT_ZOMBIE |
                        EXIT_DEAD));
    const char **p = &task_state_array[0];
    if(state == 0) count++;

    while (state) {
        p++;
        state >>= 1;
    }
    return *p;
}

void calculate_stats(void) {
	struct task_struct * task;
	int np = 0;
	for_each_process(task) {
		np = np+1;
		printk(KERN_INFO "PID %d running, Parent PID %d, State: %s", task->pid, task->parent->pid, get_task_state(task));
		//printk(KERN_INFO "Parent PID %d, ", task->parent->pid);
		//printk(KERN_INFO "State: %s\n", get_task_state); 
	}
	printk(KERN_INFO "Percentage TASK_RUNNING: %d", (count*100)/np);
	printk(KERN_INFO "STATS As calculated above");
}

static int hello_init(void) {
	printk(KERN_ALERT "Init\n");
	calculate_stats();
	return 0;
}

static void hello_exit(void) {
	printk(KERN_ALERT "Exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

