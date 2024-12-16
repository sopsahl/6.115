main: 
	
	mov P1, #19h ; Value for 0.5 V
	mov R0, #100d ; Arbitrary number of cycles for each step
	
	loop1:
		setb P0.7
		clr P0.7
		djnz R0, loop1 ; cycles 100 times before moving to the next block
	
	mov P1, #0E6h ; Value for 4.5 V
	mov R0, #100d ; Arbitrary number of cycles for each step
	
	loop2:
		setb P0.7
		clr P0.7
		djnz R0, loop2 ; cycles 100 times before moving to the next block

	sjmp main

	

	
	
