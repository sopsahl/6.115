main:
	setb P3.3 
	setb P3.4 ;   sets 3.4-3 => 11 (display 3)
	mov P1, #0C0h ; 0
	mov P1, #0FFh ; clear the display before moving on
	
	clr P3.3 ; sets 3.4-3 => 10 (display 2)
	mov P1, #0F9h ; 1
	mov P1, #0FFh ; clear the display before moving on
	
	setb P3.3 
	clr P3.4 ; sets 3.4-3 => 01 (display 1)
	mov P1, #0A4h ; 2
	mov P1, #0FFh ; clear the display before moving on

	clr P3.3 
	clr P3.4 ; sets 3.4-3 => 00 (display 0)
	mov P1, #0B0h ; 3
	mov P1, #0FFh ; clear the display before moving on

	sjmp main

