	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}
    #code
    movs r3, 0              @d = r3 = 0


#while(1){
.L1: 
    #if // r0 & 1 
    movs r2, 1
    ands r2, r0, r2         @r0 & 1
    cmp r2, 1
    # then
    beq .END_L1
    #endif

    #if // r1 & 1 
    movs r2, 1
    ands r2, r1, r2         @r1 & 1
    cmp r2, 1
    #then
    beq .END_L1
    #endif


    asrs r0, r0, 1          @a >>= 1
    asrs r1, r1, 1          @b >>= 1
    adds r3, r3, 1          @d += 1
    b .L1                   @coninue loop
#}

.END_L1:




.L2:
    # if// a == b
    cmp r0, r1
    # then:
    beq .END_L2
    # else:

    # if //!(a & 1):
    movs r2, 1
    ands r2, r0, r2         @r0 & 1
    cmp r2, 1
    # then:
    bne .DIVA

    # else if //!(b & 1):
    movs r2, 1
    ands r2, r1, r2         @r1 & 1
    cmp r2, 1
    # then:
    bne .DIVB


    #else if // a > b
    cmp r0, r1
    #then
    bgt .AMBDIV2

    #else // b > a
    #then
    b .BMADIV2


.AMBDIV2:
    subs r0, r0, r1         @a = (a-b)
    asrs r0, r0, 1          @a >>= 1
    b .L2

.BMADIV2:
    subs r1, r1, r0         @b = (b - a)
    asrs r1, r1, 1          @b >>= 1
    b .L2

.DIVA:
    asrs r0, r0, 1
    b .L2

.DIVB:
    asrs r1, r1, 1
    b .L2

.END_L2:
    b .RET

.RET:
    lsls r0, r0, r3         @return a << d
    .align 2


    #/code
	pop {r4-r7}
	bx	lr
