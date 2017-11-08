	.text
	.syntax unified
	.thumb
	.global	string_length
	.type string_length, %function
string_length:
	push {r4-r7}
    #code

    movs r1, 0         @string length counter
.LOOP:
    ldrb r2, [r0, r1]   @r2 = r0[r1]
    cmp r2, 0           @if r2 == '\0'
    beq .END
    #else
    adds r1, 1          @r1++
    b .LOOP
.END:
    movs r0, r1         @return r1

    #/code
	pop {r4-r7}	
	bx	lr
