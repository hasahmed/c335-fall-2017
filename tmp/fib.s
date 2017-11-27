	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}

    movs r1, 1      @prev1
    movs r2, 1      @prev2
    movs r3, 1      @val
    movs r4, 0      @counter, i
    #if r0 == 0: return 0
    cmp r0, 0
    beq .END

    #if r0 == 1: return 1
    cmp r0, 1
    beq .END

    #else
.LOOP:
    #r5 = num
    #r4 = i
    movs r5, r0     @r5 = num -- tmp value 
    subs r5, 2      @(num - 2) 
    #if i < (num - 2)
    cmp r4, r5      @i < (num -2) 
    #then
    bgt .RETVAL
    beq .RETVAL
    #else
    adds r3, r1, r2 @val = prev1 + prev2
    movs r2, r1     @prev2 = prev1
    movs r1, r3     @prev1 = val
    adds r4, 1      @i++
    b .LOOP

.RETVAL:
    movs r0, r3
    b .END

.END:
	pop {r4-r7}
	bx	lr			
