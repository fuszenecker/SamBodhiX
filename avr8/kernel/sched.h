#ifndef __SCHED_H__
#define __SCHED_H__

#define SCHED_EMPTY     0
#define SCHED_RUNNING   1
#define SCHED_DELAYED   2
#define SCHED_KILLED    3
#define SCHED_STOPPED   4
#define SCHED_CURRENT   5

int scheduler_init();
int scheduler_start();
void scheduler_register_task(unsigned char pid, unsigned char status, void (*address)(void), unsigned char *stack);

#define REG_SPL         (36)
#define REG_SPH         (35)
#define REG_PCL         (34)
#define REG_PCH         (33)
#define REG_STATUS      (0)

#endif
