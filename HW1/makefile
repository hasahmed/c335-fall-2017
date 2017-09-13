ACC = arm-none-eabi-gcc
FLAGS = -c -g -o1 -mcpu=cortex-m0 -mthumb 

c :
	$(ACC) $(FLAGS) test.c -o test.o

ASMC = arm-none-eabi-as
ASMFLAGS = -g -mcpu=cortex-m0 -mthumb

asm :
	$(ASMC) $(ASMFLAGS) t1.S -o t1.o

LFLAGS = -g -mcpu=cortex-m0 -mthumb --specs=rdimon.specs -lc -lrdimon

link :
	$(ACC) $(LFLAGS) t1.o test.o -o HW1.elf

