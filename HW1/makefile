ACC = arm-none-eabi-gcc
FLAGS = -c -g -o1 -mcpu=cortex-m0 -mthumb




all: c asm link

c :
	$(ACC) $(FLAGS) test.c -o test.o

ASMC = arm-none-eabi-as
ASMFLAGS = -g -mcpu=cortex-m0 -mthumb

asm :
	$(ASMC) $(ASMFLAGS) t1.S -o t1.o

LFLAGS = -g -mcpu=cortex-m0 -mthumb --specs=rdimon.specs -lc -lrdimon

link :
	$(ACC) $(LFLAGS) t1.o test.o -o HW1.elf


test : all
	    qemu-system-arm  -machine versatilepb -cpu cortex-m3 -nographic \
			                   -monitor null -serial null \
							                      -semihosting -kernel HW1.elf

asmgen:
	$(ACC) $(FLAGS) -S test.c 


clean :
	rm *.o *.elf
