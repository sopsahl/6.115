mov R0, #19h
mov R1, #0E6h

mov R2, #7fh
mov R3, #01h

push 00h
push 01h ; stores R0 and R1 on the stack

main: 
	pop 01h
	pop 00h ; removes R0 and R1 from the stack
	
	loop:
		
		push 02h ; Stores Value of the duty cycling 
		
		mov A, #0h
		subb A, R2 ; gets 255 - duty cycle for the counter
		mov R2, A
		
		mov A, R0 ; moves 0.5 V into the Accumulator
		
		lcall dacme

		pop 02h ; Restores value of the duty cycling
		push 02h ; Stores it again
	
		mov A, R1 ; moves 4.5 V into the Accumulator

		lcall dacme 

		pop 02h ; gets the value of the duty cycling

		sjmp loop
	

dacme:
	mov P1, A ; moves the accumulator to the DAC
	clr P0.7
	mainloop:
	
		push 03h ; stores the period scaling factor
		innerloop:
			djnz R3, innerloop ; if the period scale counter isn't zero, reuploads
		pop 03h ; restores the period scaling factor

		djnz R2, mainloop ; cycles before moving to the next block

	setb P0.7
	ret

