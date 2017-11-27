	.text
	.syntax unified
	.thumb
	.global	mult_by_5
	.type mult_by_5, %function
mult_by_5:
	push {r4-r7}
    #code

    movs r1, r0     @preserve contents of r0
    lsls r1, 2      @multiply times 4
    adds r0, r1, r0 @add the number passed in as an argument to r1 and store it in r0

    #/code
	pop {r4-r7}	
	bx	lr
