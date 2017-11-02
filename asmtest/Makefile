OBJS = main.o abs.o test_functions.o

ELF=$(notdir $(CURDIR)).elf

CC= arm-none-eabi-gcc
LD= arm-none-eabi-gcc
AR= arm-none-eabi-ar
AS= arm-none-eabi-as
GDB= arm-none-eabi-gdb
QEMU= qemu-system-arm
OBJDUMP= arm-none-eabi-objdump

CFLAGS = -g -mcpu=cortex-m0 -mthumb -I..
LDFLAGS = --specs=rdimon.specs -lc -lrdimon

QFLAGS= -cpu cortex-m3 -nographic 
QFLAGS+= -monitor null -serial null 
QFLAGS+= -machine integratorcp -semihosting -kernel 

$(ELF) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

.s.o : 
	$(AS) $(CFLAGS) -g $< -o $@
	$(OBJDUMP) -d $@ > $(@:.o=.lst)

.c.o : 
	$(CC) $(CFLAGS) -c $< -o $@

test : $(ELF)
	$(QEMU) $(QFLAGS)  $<

test : $(ELF)
	$(QEMU) $(QFLAGS)  $<

debug: $(ELF)
	$(QEMU) $(QFLAGS)  $< -gdb tcp::51234 -S &
	$(GDB) $< --command=../main.gdb

clean: 
	rm -f $(OBJS) $(ELF) $(OBJS:.o=.lst)


