MCU	= atmega32
CC	= /usr/local/avr/bin/avr-gcc
OPT	= -O1
CFLAGS	= -Wall $(OPT) -g -I. -Ikernel -Idrivers -I../servers -mmcu=$(MCU) -DARCH=avr8 -DCPU=$(MCU) -fpack-struct
LD	= avr-gcc
LDFLAGS	=

ELF	= RTOE
OBJS	= kernel/sysinit.o kernel/sched.o ../servers/ipc.o drivers/console.o

OBJCOPY	= avr-objcopy
OCFLAGS	= -O

OBJDUMP	= avr-objdump
ODFLAGS	= -h -S

NM	= avr-nm

AVARICE	= avarice
AIFLAGS	= -2 -j /dev/ttyS0 -e -p -f

all:	$(OBJS)
	$(LD) $(CFLAGS) $(LDFLAGS) -o $(ELF) $(OBJS)
	$(OBJCOPY) $(OCFLAGS) binary $(ELF) $(ELF).bin
	$(OBJCOPY) $(OCFLAGS) ihex $(ELF) $(ELF).hex
	$(OBJDUMP) $(ODFLAGS) $(ELF) > $(ELF).list
	$(NM) $(ELF) | sort > $(ELF).nm

clean:
	rm -f $(OBJS) $(ELF) *.hex *core *.bin *.list *.nm

jburn:
	$(AVARICE) $(AIFLAGS) $(ELF)

depend:
	$(CC) $(CFLAGS) -MM kernel/*.c drivers/*.c ../servers/*.c > depend

include depend
# DO NOT DELETE
