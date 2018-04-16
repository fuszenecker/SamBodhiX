#ifndef __IPC_H__
#define __IPC_H__

#include <config.h>
#include <sys_types.h>

#define SEMA_EMPTY      0
#define SEMA_ALLOCATE   1
#define SEMA_ACCEPTED   2
#define SEMA_SENT       3
#define SEMA_RECEIVED   4

struct t_message_box {
    t_semaphore sema_in;
    t_pid       src;
    t_uchar     message_in[MESSAGE_SIZE];

    t_semaphore sema_out;
    t_pid       dst;
    t_uchar     message_out[MESSAGE_SIZE];
} __attribute__((packed));

void ipc();

#endif
