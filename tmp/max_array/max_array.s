	.text
	.syntax unified
	.thumb
	.global	max_array
	.type max_array, %function
max_array:
	push {r4-r7}
    #code

    movs r3, 1              @this is counter
    ldr r2, [r0]         @r2 = arr[0]


.LOOP:
    cmp r3, r1          @if (r3 == r1(size) break)
    beq .END

    adds r0, r0, 4     @r0 += 1, this incriments the array by 1
    adds r3, r3, 1      @r3 += 1 this counts how far we've come in the array
    ldr r4, [r0]     @load the actual value r0
    cmp r4, r2          @if r0 > r2, then reassign
    bgt .REASSIGN
    b .LOOP

.REASSIGN:
    ldr r2, [r0]         @r2 = *r0
    b .LOOP

.END:
    movs r0, r2

    #/code
	pop {r4-r7}	
	bx	lr

