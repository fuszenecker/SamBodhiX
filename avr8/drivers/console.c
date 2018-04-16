#include <avr/io.h>

int console_lowlevel_init() {
    unsigned char c;
    
    DDRD |= 0x2;

    UBRRH = 82;
    UBRRL = 82;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);

    for (c = 0; c < 64; c++) {
        while (!(UCSRA & (1 << UDRE)));
        UDR = '_';
    }
    
    while (!(UCSRA & (1 << UDRE)));
    UDR = '\r';
    while (!(UCSRA & (1 << UDRE)));
    UDR = '\n';

    while (!(UCSRA & (1 << UDRE)));
    UDR = '\r';
    while (!(UCSRA & (1 << UDRE)));
    UDR = '\n';

    return 0;
}

inline int console_lowlevel_print(char value) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = value;
    return 0;
}

inline char to_hex(unsigned char value) {
    switch (value & 15) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: return '.';
    }

    return '_';
}

inline int console_lowlevel_print_hex(unsigned char value) {
    console_lowlevel_print(to_hex(value / 16));    
    console_lowlevel_print(to_hex(value % 16));    
    return 0;
}

inline void console_lowlevel_print_reg(char ch1, char ch2, unsigned char value) {
    console_lowlevel_print(ch1);
    console_lowlevel_print(ch2);
    console_lowlevel_print('=');
    console_lowlevel_print_hex(value);
    console_lowlevel_print(' ');
    console_lowlevel_print(' ');
}

void console_lowlevel_dump_regs() __attribute__((naked));

void console_lowlevel_dump_regs() {
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

    char c;
    unsigned char value;
    unsigned int sp;
 
    console_lowlevel_print('\r');
    console_lowlevel_print('\n');
    console_lowlevel_print('\r');
    console_lowlevel_print('\n');

    asm("push %0" : "=r" (value));
    console_lowlevel_print_reg('S', 'T', value);

    for (c = 0; c < 32; c++) {
        if (!(c % 8))
            console_lowlevel_print('\r'),
            console_lowlevel_print('\n');

        asm __volatile__ ("push %0" : "=r" (value));
        console_lowlevel_print_reg('r', 'a' + c, value);
    }

    console_lowlevel_print('\r');
    console_lowlevel_print('\n');
    console_lowlevel_print('\r');
    console_lowlevel_print('\n');

    asm("in %0, 0x3e" : "=r" (value));
    sp = value << 8;
    asm("in %0, 0x3d" : "=r" (value));
    sp |= value;
 
    for (c = 0; c < 32; c++) {
        console_lowlevel_print_hex(*((unsigned char *) sp));
        console_lowlevel_print(' ');
    }

    console_lowlevel_print('\r');
    console_lowlevel_print('\n');
    console_lowlevel_print('\r');
    console_lowlevel_print('\n');
}
