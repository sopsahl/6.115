; this subroutine displays the value from the adc in the p1
main:
	mov dptr, #0fe10h ; location of the adc
	loop:
		movx @dptr, a ; triggers the read
		waiting:
			jb P3.5, waiting ; waits for interrupt flag to be cleared
		movx a, @dptr  ; gets the value out of the adc
		mov P1, a   ; displays it
		sjmp loop
		
delay:
	mov R1, #0ffh
	delay_loop:
		mov R2, #0ffh
		stop:
			djnz R2, stop
			djnz R1, delay_loop
		ret
		