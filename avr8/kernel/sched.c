#include <config.h>
#include <ipc.h>
#include <sched.h>
#include <console.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

asm(".balign " BALIGN);

extern void test_task_1();
extern void test_task_2();

struct t_process_list_item {
    t_uchar     status;
    t_register  registers[NR_REGISTERS];

    t_priority  priority;
    t_priority  prio_counter;
    t_delay     delay;
            
    char        name[PROC_NAME_SIZE + 1];
} __attribute__((packed));


int scheduler_init() {
    struct t_message_box *message_box = (struct t_message_box *) (SCHED_RAM_BASE);
    struct t_process_list_item *process = (struct t_process_list_item *) (SCHED_PROC_LIST);
    signed char c;
        
    message_box->sema_in = SEMA_EMPTY;
    message_box->sema_out = SEMA_EMPTY;

    for (c = 0; c < MAX_PROCESSES; c++, process++) {
        process->status = 0;
        process->priority = 0;
        process->prio_counter = 0;
        process->delay = 0;
    }
    
    TCCR0 = 5;
    TCNT0 = 0;
    TIMSK |= _BV(TOIE0);
            
    return 0;
}


void scheduler_register_task(unsigned char pid, unsigned char status, void (*address)(void), unsigned char *stack) {
    struct t_process_list_item *process = (struct t_process_list_item *) (SCHED_PROC_LIST);

    process += pid;

    process->status = status;
    process->registers[REG_SPL] = (unsigned int) stack % 256;
    process->registers[REG_SPH] = (unsigned int) stack / 256;
    process->registers[REG_PCL] = ((unsigned int) address) % 256;
    process->registers[REG_PCH] = ((unsigned int) address) / 256;
}


//----------------------------------------------------------------------------
/*
    process = (struct t_process_list_item *) (SCHED_PROC_LIST);
    process->status = SCHED_CURRENT;
    process->priority = 255;
    strcpy(process->name, "SYSINIT");

//----------------------------------------------------------------------------

    process++;
    process->status = SCHED_RUNNING;
    process->priority = 1;
    strcpy(process->name, "IPC");

    process->registers[REG_SPL] = (IPC_STACK - NR_REGISTERS) % 256;
    process->registers[REG_SPH] = (IPC_STACK - NR_REGISTERS) / 256;
    process->registers[REG_PCL] = ((unsigned int) test_task_2) % 256;
    process->registers[REG_PCH] = ((unsigned int) test_task_2) / 256;
*/
//----------------------------------------------------------------------------

int scheduler_start() {
    sei();
    return 0;
}


unsigned char *get_register_address() {
    struct t_process_list_item *process = (struct t_process_list_item *) (SCHED_PROC_LIST);
    char current;

    for (current = 0; current < MAX_PROCESSES; current++, process++)
        if (process->status == SCHED_CURRENT)
            break;

    return process->registers;
}

void task_switch() {
    struct t_process_list_item *process = (struct t_process_list_item *) (SCHED_PROC_LIST);
    char current;

    for (current = 0; current < MAX_PROCESSES; current++)
        if (process->status == SCHED_CURRENT)
            break;
    
    process->status = SCHED_RUNNING;

    do {
        current++;
        process++;
        if (current >= MAX_PROCESSES) {
            current = 0;
            process = (struct t_process_list_item *) (SCHED_PROC_LIST);
        }
    } while (process->status != SCHED_RUNNING);
    
    process->status = SCHED_CURRENT;
}


void __vector_11() __attribute__((signal, naked));

void __vector_11() {
    asm("push r31");
    asm("push r30");
    asm("push r29");
    asm("push r28");
    asm("push r27");
    asm("push r26");
    asm("push r25");
    asm("push r24");
    asm("push r23");
    asm("push r22");
    asm("push r21");
    asm("push r20");
    asm("push r19");
    asm("push r18");
    asm("push r17");
    asm("push r16");
    asm("push r15");
    asm("push r14");
    asm("push r13");
    asm("push r12");
    asm("push r11");
    asm("push r10");
    asm("push r9");
    asm("push r8");
    asm("push r7");
    asm("push r6");
    asm("push r5");
    asm("push r4");
    asm("push r3");
    asm("push r2");
    asm("push r1");
    asm("push r0");         // 34

    asm("in r0, 0x3f");     // STATUS
    asm("push r0");         // 35

    TCCR0 = 0;

    asm("ldi r30, %0" :: "i" (SCHED_PROC_LIST % 256));
    asm("ldi r31, %0" :: "i" (SCHED_PROC_LIST / 256));
    asm("ldi r25, 0");
    asm(".next:");
    asm("ld  r24, Z");
    asm("cpi r24, %0" :: "i" (SCHED_CURRENT));
    asm("breq .found");
    asm("inc r25");
    asm("adiw r30, %0" :: "i" (sizeof(struct t_process_list_item)));
    asm("jmp .next");
    asm(".found:");

    // _REGISTERS[]_ offset
    asm("adiw r30, 1"); 

    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");
    asm("pop r0"); asm("st Z+, r0");

    // save stack pointer
    asm("in r4, 0x3e"); asm("st Z+, r4");
    asm("in r4, 0x3d"); asm("st Z+, r4");

    TCCR0 = 5;
    TCNT0 = 0;

    asm("ldi r30, %0" :: "i" (SCHED_PROC_LIST % 256));
    asm("ldi r31, %0" :: "i" (SCHED_PROC_LIST / 256));
    asm("ldi r25, 0");
    asm(".next2:");
    asm("ld  r24, Z");
    asm("cpi r24, %0" :: "i" (SCHED_CURRENT));
    asm("breq .found2");
    asm("inc r25");
    asm("adiw r30, %0" :: "i" (sizeof(struct t_process_list_item)));
    asm("jmp .next2");
    asm(".found2:");

    asm("ldi r24, %0" :: "i" (SCHED_RUNNING));
    asm("st Z, r24"); 

    asm(".next_it:");
    asm("inc r25");
    asm("adiw r30, %0" :: "i" (sizeof(struct t_process_list_item)));
    asm("cpi r25, %0" :: "i" (MAX_PROCESSES));
    asm("brlt .next_one");
    asm("ldi r30, %0" :: "i" (SCHED_PROC_LIST % 256));
    asm("ldi r31, %0" :: "i" (SCHED_PROC_LIST / 256));
    asm("ldi r25, 0x00");
    asm(".next_one:");
    asm("ld r24, Z");
    asm("cpi r24, %0" :: "i" (SCHED_RUNNING));
    asm("brne .next_it");

    asm("ldi r24, %0" :: "i" (SCHED_CURRENT));
    asm("st  Z, r24");

    asm("adiw r30, %0" :: "i" (sizeof(t_uchar) + 37 * sizeof(unsigned char))); 

    // asm("out %0, r25" :: "i" (PORTD));

    // save stack pointer
    asm("ld r4, -Z"); asm("out 0x3d, r4");
    asm("ld r4, -Z"); asm("out 0x3e, r4");

    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 
    asm("ld r0, -Z"); asm("push r0"); 

    asm("pop r0");
    asm("out 0x3f, r0");

    asm("pop r0");
    asm("pop r1");
    asm("pop r2");
    asm("pop r3");
    asm("pop r4");
    asm("pop r5");
    asm("pop r6");
    asm("pop r7");
    asm("pop r8");
    asm("pop r9");
    asm("pop r10");
    asm("pop r11");
    asm("pop r12");
    asm("pop r13");
    asm("pop r14");
    asm("pop r15");
    asm("pop r16");
    asm("pop r17");
    asm("pop r18");
    asm("pop r19");
    asm("pop r20");
    asm("pop r21");
    asm("pop r22");
    asm("pop r23");
    asm("pop r24");
    asm("pop r25");
    asm("pop r26");
    asm("pop r27");
    asm("pop r28");
    asm("pop r29");
    asm("pop r30");
    asm("pop r31");
    
    asm("reti");
}

