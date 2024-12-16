; this routine implements a 16 bit variable counter

mov dpl, #00h
mov dph, #10h
movx a, @dptr ; gets the value we stored initially in W9000=x
mov R0, a ; low byte
inc dptr
movx a, @dptr ; gets the value in W9001=x
mov R1, a ; high byte

clr ea 
mov tcon, #00h
mov tmod, #01h ; mode 1 16 bit counter
mov P1, #00h 

main:
	mov TL0, R0
	mov TH0, R1
	setb TR0 ; starts the timer
	loop:
		jnb TF0, loop ; checks if the timer has overflowed
	clr TR0 ; ends the timer
	clr TF0 ; clears the flag
	cpl P1.0 ; flips the sign of P1.0
	sjmp main
	