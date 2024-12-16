; this routine implements an 8 bit variable counter

mov dpl, #00h
mov dph, #10h
movx a, @dptr ; gets the value we stored initially in W9000=x

main:
	mov R0, a ; mov the starting value into R0
	loop:
		djnz R0, loop
	cpl P1.0 ; flips the sign of P1.0
	sjmp main
	