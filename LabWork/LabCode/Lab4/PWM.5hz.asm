; this routine generates a 5 kHz 50% Duty Cycle Square wave on 4A
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
	mov R0, #64h
	mov R1, #64h ; gives us 10000x decrease in period
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #02h ; sets Mode 2, auto reload on T0
	mov tcon, #10h ; sets the start of the timer
	ret
	
main:
	sjmp main

switch:
; this subroutine complements the value in PC3/4A
	djnz R0, return ; makes sure that 10000 cycles have passed 
	mov R0, #064h
	djnz R1, return
	mov R1, #064h 
	cjne a, #00h, down ; branches the switching
	up:
		mov a, #0fh
		movx @dptr, a ; sets PC3
		ret
	down:
		mov a, #00h
		movx @dptr, a ; clears PC3
		ret
	return:
		ret

