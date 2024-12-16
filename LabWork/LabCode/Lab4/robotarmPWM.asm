; this routine moves to a new motor signal based on a keypad press 10 times a second with PWM 
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
	;initialize the counters
	mov R0, #00h ; initial control signal
	mov R1, #10d ; initial 10 cycle counter
	mov R2, #10d ; initial duty cycle counter
	mov R3, #10d ; initial duty cycle buffer
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
	jnb P3.4, base; checks if a button has been pressed and DA is high
	mov a, P1 ; gets output of keypad
	anl a , #0fh ; just checking the bottom 4 bits
	motor1up:
		cjne a, #00h, motor1down
		mov R0, #01h
		sjmp commandsend
	motor1down:
		cjne a, #01h, motor2up
		mov R0, #02h
		sjmp commandsend
	motor2up:
		cjne a, #02h, motor2down
		mov R0, #04h
		sjmp commandsend
	motor2down:
		cjne a, #03h, noselection
		mov R0, #08h
		sjmp commandsend
	noselection:
		lcall PWM ; changes the counter
		mov R3, a ; R3 stores the permanent counter value
	base:
		mov R0, #00h ; base case
	commandsend:
		mov a, R1
		jnz afterreload ; checks if the 10 cycle counter is not zero
			mov R1, #10d ; reloads the 10 cycle counter
			mov a, R3
			mov R2, a ; reloads the duty cycle counter
		afterreload:
			dec R1 ; decrements the 10 cycle counter	
		PWM_on:
			mov a, R2
			jz send ; checks if the 1/10 counter is zero
			dec R2 
			mov a, R0 ; puts the value of the buffer into the output
			sjmp send
		PWM_off:
			mov a, #00h ; off
		send:
			movx @dptr, a ; turns on the specific motors (if any)
	ret

PWM:
	inc A
	movc a, @a + pc ; puts value of the transformation into the accumulator
	ret
; table of digits
	.db 10d, 10d, 10d, 10d, 3d, 6d, 9d, 10d, 2d, 5d, 8d, 10d, 1d, 4d, 7d, 10d ; each number is its own fraction of ten, and the rest are 10/10

	