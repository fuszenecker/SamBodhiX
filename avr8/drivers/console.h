#ifndef __CONSOLE_H__
#define __CONSOLE_H__

int console_lowlevel_init();
int console_lowlevel_print(char);
char console_lowlevel_print_hex(unsigned char);
void console_lowlevel_print_reg(char, char, unsigned char);
void console_lowlevel_dump_regs();

#endif
