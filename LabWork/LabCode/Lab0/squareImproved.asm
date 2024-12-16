mov R0, #19h
mov R1, #0E6h

push 00h
push 01h ; stores R0 and R1 on the stack

main: 
	pop 01h
	pop 00h ; removes R0 and R1 from the stack
	
	loop:

		mov A, R0 ; moves 0.5 V into the Accumulator
	
		lcall dacme
	
		mov A, R1 ; moves 4.5 V into the Accumulator

		lcall dacme 

		sjmp loop
	

dacme:
	mov P1, A ; moves the accumulator to the DAC
	push 00h ; storing R0 because we'll use it for the counter
	mov R0, #100d ; Arbitrary number of cycles for each step
	innerloop:
		setb P0.7
		clr P0.7
		djnz R0, innerloop ; cycles 100 times before moving to the next block
	pop 00h ; returning the value of R0
	ret




	