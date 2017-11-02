	.text
	.syntax unified
	.thumb
	.global	abs_x
	.type abs_x, %function
abs_x:
	push {r4-r7}  //push registers to stack
    cmp r0, r0
    movs r0, 3
/*
	Your implementation goes here. 
*/
	pop {r4-r7}	 //pop registers from stack, and load them into current registers
	bx	lr
