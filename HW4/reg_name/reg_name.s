	.text
	.syntax unified
	.thumb
	.global	reg_name
	.type reg_name, %function
reg_name:
	push {r4-r7}
    #code

    ldr r1, .NAMES              @assign r1 to *names[] array
    cmp r0, 16                  @if asgv[0] > 15
    bgt .RETZERO                @if r0 > 15 return 0
        #else
    lsls r2, r0, 2              @multiply offset by 4 bc sizeof char*
    #return the string at index of r2
    ldr r0, [r1, r2]            @load the index stored 
    b .END

.RETZERO:
    eors r0, r0, r0            @zero register
    b .END

.END:
    .align 2
    #/code
	pop {r4-r7}	
	bx	lr

.NAMES:
    .word names
