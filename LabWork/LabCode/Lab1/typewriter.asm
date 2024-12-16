; the main loop or body of our typewriter program

.org 00h
	ljmp start ; jumps to the main body of our program (at 100h)

.org 100h
start:
	lcall init ; starts the serial port
	loop:
		lcall getchr  ; gets a character from the PC keyboard	
		lcall sndchr ; echoes the character to the PC screen
		djnz R0, loop ; decrements the counter
		lcall crlf
	sjmp loop

init:
; set up serial porr with a 11.0592 Mhz crystal
; use timer 1 for 9600 baud communications
	mov tmod, #20h ;set timer 1 to mode 2
	mov tcon, #40h ; run timer 1
	mov th1, #-3 ; set 9600 baud
	mov scon, #50h ; set serial control for 8 bit data
	mov R0, #41h ; initializes the chr counter to 65
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
	mov P1, a
	txloop:
		jnb scon.1, txloop ; wait till chr is sent
	ret

crlf:
; this routine handles carriage return and line  feed
	mov a, #0Ah ; makes the linefeed
	lcall sndchr
	mov a, #0Dh ; makes the carriage return
	lcall sndchr
	mov R0, #41h ; resets the counter to 65
	ret
