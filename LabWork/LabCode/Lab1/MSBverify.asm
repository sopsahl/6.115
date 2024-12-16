; this file creates a ascending light display
main:
	mov P1, #0ffh; start off all lit
	lcall delay

	mov P1, #00h ; then blank
	lcall delay
	
	setb P1.7
	lcall delay
	clr P1.7 

	setb P1.6
	lcall delay
	clr P1.6

	setb P1.5
	lcall delay
	clr P1.5

	setb P1.4
	lcall delay
	clr P1.4

	setb P1.3
	lcall delay
	clr P1.3
 
	setb P1.2
	lcall delay
	clr P1.2

	setb P1.1
	lcall delay
	clr P1.1

	setb P1.0
	lcall delay
	clr P1.0
	
	ljmp main ; restart the process



; this function waits for the counter to end before returning
delay:
	mov R0, #0ffh
	loop:
		mov R1, #0ffh
		innerloop:
			djnz R1, innerloop ; embedded so that delay last for long enough
			nop
		djnz R0, loop ; decrements and waits for the counter to end before returning
		ret

