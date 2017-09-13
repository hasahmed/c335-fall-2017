TEMPLATEROOT = ../fall2017-lab

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g

# object files

OBJS=  $(STARTUP) test.o stm32f30x_rcc.o stm32f30x_gpio.o

# include common make file

vpath %.c .
include $(TEMPLATEROOT)/c335.mk
