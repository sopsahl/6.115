; this subroutine displays the value from the adc in the p1

main:
	mov dptr, #0fe30h ; location of the adc
	loop:
		movx a, @dptr  ; gets the value out of the adc
		mov P1, a   ; displays it
		sjmp loop
		