; this routine monitors the output from the keypad and changes the keystroke to a digit

.org 00h
	ljmp start ; jumps to the main body of our program (at 100h)

.org 100h
start:
	lcall init ; starts the serial port
	refresh:
		setb P3.4 ; new buttom press available
	loop:

		jnb P3.2, refresh; checks if a button has been pressed and DA is high
		jnb P3.4, loop ; checks if a new button has been pressed
		
		lcall getNum ; gets the number from the keypad
		lcall sndchr ;displays the output onto the terminal
	sjmp loop

init:
; set up serial port with a 11.0592 Mhz crystal
; use timer 1 for 9600 baud communications
	mov tmod, #20h ;set timer 1 to mode 2
	mov tcon, #40h ; run timer 1
	mov th1, #-3 ; set 9600 baud
	mov scon, #50h ; set serial control for 8 bit data
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


getNum:
; this routine gets the value from the keypad, converts it to a digit and puts in in Acc
	clr P3.3 ; Gnds output enable
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
	.db 30h, 33h, 32h, 31h ; first row
	.db 30h, 36h, 35h, 34h ; second row
	.db 30h, 39h, 38h, 37h ; third row
	.db 30h, 30h, 30h, 30h ; fourth row




