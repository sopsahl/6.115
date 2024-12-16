; this routine moves to a new motor signal every second
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
	mov a, #11h ; initially only the first is on
	; we use 11 for the rotation, so repeats every 4 seconds
	;initialize the timer
	mov TH0, #0a4h ; gives us 5kHz
	mov R0, #64h
	mov R1, #64h ; gives us 10000x decrease in period
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #02h ; sets Mode 2, auto reload on T0
	mov tcon, #10h ; sets the start of the timer
	ret
	
main:
	sjmp main

switch:
; this subroutine turns on one motor only
	djnz R0, return ; makes sure that 10000 cycles have passed 
	mov R0, #064h
	djnz R1, return
	mov R1, #064h 
	rl a ; rotates a left
	movx @dptr, a ; turns on the specific motors
	return:
		ret

