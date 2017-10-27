CC = gcc -std=c99

disassembler: hw3.o
	@echo "building"
	$(CC) -o disassembler hw3.o

#testprint : test
#	cat test.out

test : asm disassembler
	@echo "testing"
	cat test.hex | ./disassembler > test.out && diff test.out test.asm > test.diff || :
	@echo "done"

asm: 
	@echo "generating test.hex"
	arm-none-eabi-as test.asm -o test.o
	arm-none-eabi-objcopy test.o -O binary --only-section=.text test.bin
	hexdump -x test.bin |sed -e 's/^[^ ]*//' > test.hex

clean:
	@rm -f *.o test.bin test.hex test.out test.diff

.SILENT : test asm
