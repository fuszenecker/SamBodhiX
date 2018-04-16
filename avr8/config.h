#ifndef __CONFIG_H__
#define __CONFIG_H__

#define K               * 1024

#define RAM_BASE        0x00100
#define RAM_SIZE        (4 K)
#define FLASH_SIZE      (32 K)

#define RAM_BLOCK_SIZE  1024
#define BALIGN          "256"
#define MESSAGE_SIZE    32
#define NR_REGISTERS    (0x20 + 5)
#define PROC_NAME_SIZE  8
#define MAX_PROCESSES   4

#include <ipc.h>

/* 

    +----------------------+
    | SYSINIT MSG BOX      |
    | SYSINIT VARIABLES    |
    | ...                  |
    | SYSINIT STACK        |
    +----------------------+
    | SCHEDULER MSG BOX    |
    | SCHEDULER VARIABLES  |
    | ...                  |
    | SCHEDULER STACK      |
    +----------------------+
    | IPC MSG BOX          |
    | IPC VARIABLES        |
    | ...                  |
    | IPC STACK            |
    +----------------------+
    | ...                  |
    | ...                  |
    | ...                  |

*/

#define SINIT_RAM_BASE  (RAM_BASE)
#define SINIT_RAM_SIZE  (RAM_BLOCK_SIZE)
#define SYSINIT_STACK   (SINIT_RAM_BASE + SINIT_RAM_SIZE - 1)

#define SCHED_RAM_BASE  (SINIT_RAM_BASE + SINIT_RAM_SIZE)
#define SCHED_RAM_SIZE  (1 * RAM_BLOCK_SIZE)
#define SCHED_PROC_LIST (RAM_BASE + RAM_SIZE - (1 K))

#define IPC_RAM_BASE    (SCHED_RAM_BASE + SCHED_RAM_SIZE)
#define IPC_RAM_SIZE    (1 * RAM_BLOCK_SIZE)
#define IPC_STACK       (IPC_RAM_BASE + IPC_RAM_SIZE - 1)

#endif
