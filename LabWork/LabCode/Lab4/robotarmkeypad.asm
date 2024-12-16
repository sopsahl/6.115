; this routine moves to a new motor signal based on a keypad press 10 times a second
.org 0h
ljmp start

.org 0Bh ; handles the interrupt of the timer 0 auto reload
	lcall switch
	reti

.org 100h
start:
	lcall init
	lcall main
	
init:
	; initialize the 8255
	mov dptr, #0fe23h ; location of the 8255 control
	mov a, #80h
	movx @dptr, a ; initializes mode 0 in the 8255
	mov dpl, #22h ; location of the port C enable pins
	mov a, #00h ; initializes the control
	movx @dptr, a
	;initialize the timer
	mov TH0, #0a4h ; gives us 5kHz
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #02h ; sets Mode 2, auto reload on T0
	mov tcon, #10h ; sets the start of the timer
	ret
	
main:
	sjmp main

switch:
; this subroutine turns on one motor only
	jnb P3.4, elsa; checks if a button has been pressed and DA is high
	mov a, P1 ; gets output of keypad
	anl a , #0fh ; just checking the bottom 4 bits
	motor1up:
		cjne a, #00h, motor1down
		mov a, #01h
		sjmp commandsend
	motor1down:
		cjne a, #01h, motor2up
		mov a, #02h
		sjmp commandsend
	motor2up:
		cjne a, #02h, motor2down
		mov a, #04h
		sjmp commandsend
	motor2down:
		cjne a, #03h, elsa
		mov a, #08h
		sjmp commandsend
	elsa:
		mov a, #00h ; base case
	commandsend:
		; this command is sent every half second
		movx @dptr, a ; turns on the specific motors (if any)
	ret
	