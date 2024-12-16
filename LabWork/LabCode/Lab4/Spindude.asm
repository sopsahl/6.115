; this routine cycles through a spindude whenever a key is pressed
.org 0h
ljmp start

.org 0Bh ; handles the interrupt of the timer 0 auto reload
	lcall step
	reti

.org 100h
start:
	lcall init ; starts the serial port
	loop:
		lcall waitchr  ; waits till a character comes from the PC keyboard	
		setb ea  ; starts the interrupt routine
		waiting:
			jb ea, waiting ; waits until the 24 steps are handled
			mov R2, #25d
	sjmp loop
	
init:
	; initialize the 8255
	mov dptr, #0fe23h ; location of the 8255 control
	mov a, #80h
	movx @dptr, a ; initializes mode 0 in the 8255
	mov dpl, #22h ; location of the port C enable pins
	mov a, #00h ; initializes the control
	movx @dptr, a
	; set up serial port with a 11.0592 Mhz crystal
	; use timer 1 for 9600 baud communications
	; use timer 2 for 5khz interrupt
	mov tmod, #22h ;set timer 1 to mode 2 and Timer 0 to mode2
	mov th1, #-3 ; set 9600 baud
	mov th0, #0a4h ; gives us 5kHz
	mov tcon, #50h ; run timer 1 and timer 2
	mov scon, #50h ; set serial control for 8 bit data
	mov ie, #02h ; sets the TF0 interrupt but not global interrputs
	mov R0, #64h
	mov R1, #64h ; gives us 10000x decrease in period
	mov R2, #25d ; we have 24 steps (+1)
	mov R5, #11h
	ret

step:
; this subroutine turns the stepper motor once
	djnz R0, return ; makes sure that 10000 cycles have passed 
	mov R0, #064h
	djnz R1, return
	mov R1, #064h 
	djnz R2, cycle ; checks if we've stepped 24 times
		clr ea ; stops the interrupt 
		sjmp return 
	; cycles through the commands
	cycle:
	mov a, R5
	rl a ; shifts it 
	mov P1, a
	mov R5, a ; stores the value
	movx @dptr, a ; shifts it 
	movx @dptr, a ; turns all off
	return:
		ret

waitchr: 
; this routine receives a character from the PC, transmitted over the serial port
; RI is the same as SCON.0
; the 7 bit ASCII is in the accumulator
	jnb ri, waitchr ; wait till character received
	clr ri
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
