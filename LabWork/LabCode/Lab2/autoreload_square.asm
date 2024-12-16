; this routine implements an autoreload counter square wave
.org 00h
	ljmp start
	
.org 0Bh
	cpl P1.0
	reti


.org 100h
start: 
	lcall init
	lcall main
		
main:
	sjmp main ; infinite loop
	
init: 
	mov dpl, #00h
	mov dph, #10h
	movx a, @dptr ; gets the value we stored initially in W9000=x
	mov TH0, a ; moves it to the reload vector
	
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #02h ; sets Mode 2, auto reload on T0
	mov tcon, #11h ; sets the falling edge trigger and the start of the timer
	
	ret
	
	
	