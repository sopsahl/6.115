; the main loop or body of our calculator program

.org 00h
	ljmp start ; jumps to the main body of our program (at 100h)

.org 100h
start:
	lcall init ; starts the serial port
	loop:
		lcall getNum ; gets the first number
		lcall getNum ; gets the second number
		lcall getOp ; are we +, -, or other 
	sjmp loop

getNum:
; this routine handles sotring the three digit number and converting it into hex
	mov R0, #03h ; initializes the chr counter to 3
	innerloop:
		lcall getchr  ; gets a character from the PC keyboard
		lcall sndchr ; echoes the character to the PC screen
		add A, #0d0h ; converts to actual digit
		push acc ; adds the digit to the stack 
		djnz R0, innerLoop ; decrements the counter
	lcall crlf ; carriage return and line feed
	; get the digits from storage and convert to actual value
	
	pop 00h ; ones place
	pop 01h ; tens place
	pop 02h ; hundreds place

	mov A, #100d
	mov B, R2
	mul AB ; multiplying the 100s place by 100
	mov R2, A ; R2 holds the result
	
	mov A, #10d
	mov B, R1
	mul AB ; multiplying the 10s place by 10

	add A, R0 ; add the 1s
	add A, R2 ; add the 100s
	
		
	pop 00h ; gets the stored PC from the stack
	pop 01h
	
	mov R3, A
	push 03h ; add the value to the stack 

	push 01h ; restores the PC
	push 00h

	ret 
	
getOp: 
; this routine determines the result and outputs the result in the LED bank
	lcall getchr  ; gets a character from the PC keyboard
	lcall sndchr ; echoes the character to the PC screen
	mov R4, A ; moves the operation into R4

	pop 00h; get the return PC and stores
	pop 01h
	
	pop 02h ; gets the second number
	pop 03h ; gets the first number
	mov A, R3
	

	plus:
		cjne R4, #2Bh, minus ; skips to next section if not a plus sign
		add A, R2 ; adds the two numbers
		sjmp endOperations

	minus:
		cjne R4, #2Dh, default ; skips to default if not a minus sign
		clr C ; gets rid of the carry bit so we don't have some issues
		subb A, R2 ; subtracts the second number from the first
		sjmp endOperations

	default:
		mov A, #0h
	
	endOperations: 

		mov P1, A; shows the result in the LED bank
	
		push 01h ; restores the return PC
		push 00h
	
		lcall crlf ; carriage return and line feed
		ret

init:
; set up serial porr with a 11.0592 Mhz crystal
; use timer 1 for 9600 baud communications
	mov tmod, #20h ;set timer 1 to mode 2
	mov tcon, #40h ; run timer 1
	mov th1, #-3 ; set 9600 baud
	mov scon, #50h ; set serial control for 8 bit data
	ret

getchr: 
; this routine receives a character from the PC, transmitted over the serial port
; RI is the same as SCON.0
; the 7 bit ASCII is in the accumulator
	jnb ri, getchr ; wait till character received
	mov a, sbuf ; put character in the accumulator
	anl a, #7fh ; mask off 8th bit, not necessary in ASCII
	clr ri ; clear 'receive status' flag
	ret

sndchr: 
; this routine transmits a character to the PC using the serial port
; the accumulator holds the character to be sent
; SCON.1 and TI are the same
	clr scon.1 ; clear the ti complete flag
	mov sbuf, a ; move a character from the accumulator to the serial buffer
	txloop:
		jnb scon.1, txloop ; wait till chr is sent
	ret

crlf:
; this routine handles carriage return and line  feed
	mov a, #0Ah ; makes the linefeed
	lcall sndchr
	mov a, #0Dh ; makes the carriage return
	lcall sndchr
	ret
