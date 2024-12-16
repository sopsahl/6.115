; our keypad calculator program with answer in the teraTerm window

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

digitWait:
	sjmp button
	innerloop:
		setb P3.4 ; new button press available
		button:
			jnb P3.2, innerloop; checks if a button has been pressed and DA is high
			jnb P3.4, button; checks if a new button has been pressed
			ret 
		
getNum:
; this routine handles sotring the three digit number and converting it into hex
	mov R1, #03h ; initializes the chr counter to 3
	numFetch:		
		lcall getchr; gets the number from the keypad

		lcall sndchr ; echoes the character to the PC screen
		
		add A, #0d0h ; transforms to the represented digit

		push acc ; adds the digit to the stack 

		djnz R1, numFetch; decrements the counter
		
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
	
	mov R2, A
	push 02h ; add the value to the stack 

	push 01h ; restores the PC
	push 00h

	ret 


init:
; set up serial port with a 11.0592 Mhz crystal
; use timer 1 for 9600 baud communications
	mov tmod, #20h ;set timer 1 to mode 2
	mov tcon, #40h ; run timer 1
	mov th1, #-3 ; set 9600 baud
	mov scon, #50h ; set serial control for 8 bit data
	setb P3.4 ; new button press available
	ret

getchr:
; this routine gets the value from the keypad, converts it to a digit and puts in in Acc	
	clr P3.3 ; Gnds output enable
	lcall digitWait
	mov A, #0fh 
	anl A, P1 ; masks off the upper bit
	setb P3.3 ; sets output enable high 
	lcall getDigit
	clr P3.4; used to determine if a new number has been pressed
	ret  
	
getDigit:
; this routine uses table lookup to get the digit value from the ascii
; accumulator stores 00-0fh value of the keypad press
	inc A
	movc a, @a + pc ; puts value of the transformation into the accumulator
	ret
; table of digits
	.db 2Bh, 33h, 32h, 31h ; first row
	.db 2Dh, 36h, 35h, 34h ; second row
	.db 30h, 39h, 38h, 37h ; third row
	.db 30h, 30h, 30h, 30h ; fourth row

getOp: 
; this routine determines the result and outputs the result in the LED bank
	lcall getchr; gets an operation from the keypad
	lcall sndchr ; echoes the character to the PC screen
	mov R4, A ; moves the operation into R4
	lcall crlf ; carriage return and line feed

	pop 00h; get the return PC and stores
	pop 01
	
	pop 02h ; gets the second number
	pop 03h ; gets the first number
	mov A, R3 ; moves the first number into the accumulator
	
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

		lcall sndresult
	
		push 01h ; restores the return PC
		push 00h
	
		lcall crlf ; carriage return and line feed
		ret

sndresult:
; this routine prints the result to the TeraTerm window
; Acc holds the int value	
	mov B, #100d 
	div AB ; gets the number of 100s
	lcall displayAscii
	
	mov A, B
	mov B, #10d
	div AB ; gets the number of 10s
	lcall displayAscii
	
	mov A, B ; gets the number of 1s
	lcall displayAscii 
	
	lcall crlf  ; carriage return and linefeed
	
	ret

displayAscii:
; this subroutine gets the ascii of the digit in A and displays it
	clr C
	subb A, #0d0h
	lcall sndchr
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
