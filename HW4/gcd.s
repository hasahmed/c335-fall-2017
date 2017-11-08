	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}
    #code



    #/code
	pop {r4-r7}
	bx	lr
