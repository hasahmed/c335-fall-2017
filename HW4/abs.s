	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
    movs r0, 1
/*
	Your implementation goes here. 
*/
	pop {r4-r7}	
	bx	lr
