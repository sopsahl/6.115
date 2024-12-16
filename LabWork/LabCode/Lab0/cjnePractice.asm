main:
	func1:
		cjne R0, #1h, func2 : skips the following code block
		mov P1, #0AAh ; mov AAh into P1
		lcall delay ; display lasts for visibility
		sjmp func1
	func2:
		cjne R0, #2h, func3 ; skips the following code block
		mov P1, #0B0h ; move '3' into the display
		lcall delay ; display lasts for visibility
		sjmp func2
	func3:
		cjne R0, #3h, func4 ; skips the following code block
		mov P1, #7Fh ; Moving 2.5V into P1
		clr P0.7 ; shows 2.5V
		lcall delay ; display lasts for visibility
		setb P0.7
		sjmp func3
	func4:
		cjne R0, #4h, func1 ; returns to the start of the file
		mov P1, #0CCh ; Moving 4V into P1
		clr P0.7 ; shows 4V
		lcall delay ; display lasts for visibility
		setb P0.7
		sjmp func4


delay:
	mov R1, #100d ; counter just for visibility
	loop:
		djnz R1, loop
	ret

