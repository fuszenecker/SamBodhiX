#include <config.h>
#include <os_config.h>

#include <sched.h>

#include <avr/io.h>
#include <console.h>

asm(".balign " BALIGN);

void test_task_1();
void test_task_2();

int main() __attribute__((naked));

int main () {
    DDRB = 0xff;
    DDRA = 0;
    PORTB = 0xfe;

    while (1) {
        // 0x3f is STATUS
        asm("eor r1, r1");
        asm("out 0x3f, r1");

        asm("ldi r28, %0" :: "i" (SYSINIT_STACK % 256));
        asm("ldi r29, %0" :: "i" (SYSINIT_STACK / 256));
        asm("out 0x3e, r29");
        asm("out 0x3d, r28");

        console_lowlevel_init();
//        console_lowlevel_print('I');

    
//        test_task_2();

        scheduler_init();
//        console_lowlevel_print('S');

        scheduler_register_task(0, SCHED_CURRENT, (void *) 0, 0);
        scheduler_register_task(1, SCHED_RUNNING, test_task_2, IPC_STACK);

        scheduler_start(); 

        // console_lowlevel_dump_regs();

        test_task_1();
    }
}

void test_task_1() {
        register unsigned int c = 0, d = 0;
        
        for (;; c++) {
            PORTB = ~(c & 255);

            for (d = 0; d < 50000; d++) asm("nop");
        }
}

extern void reg_ipc(void);

void test_task_2() {
        register unsigned int c = 0, d = 0;

        c = 0x55;

        for (;; c++) {
            DDRA = 0xff;

            PORTA = 0x55;
            for (d = 0; d < 50000; d++) asm("nop");
            for (d = 0; d < 50000; d++) asm("nop");
            for (d = 0; d < 50000; d++) asm("nop");

            PORTA = 0xAA;
            for (d = 0; d < 50000; d++) asm("nop");
            for (d = 0; d < 50000; d++) asm("nop");
            for (d = 0; d < 50000; d++) asm("nop");
        }
}
