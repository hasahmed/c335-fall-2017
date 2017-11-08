	.text
	.syntax unified
	.thumb
	.global	abs_s
	.type abs_s, %function
abs_s:
	push {r4-r7}
    cmn r0, r0
    bmi .NEG            @if r0 - r0 != 0 goto .NEG
    b .END              @else go to end
.NEG:
    movs r1, 0          @store 0 in r1
    subs r0, r1, r0     @subtract 0 from r0 making it positive, and store in r0
.END:
	pop {r4-r7}	
	bx	lr
