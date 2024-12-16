; this program manages the countdown of frequency and striking of the lamp
; the Schmitt output will be connected to P1.0
.org 00h
	ljmp start
	
.org 0Bh
	clr TR0
	clr TF0
	mov TH0, #010h ; delay to take on each freq change
	mov TL0, #00h 
	setb TR0 ; starts the timer
	lcall updateFreq
	reti

.org 100h
start: 
	lcall init
	lcall main
	 
init:
	mov P1, #0ffh ; initializes the values in P1
	mov R2, #0Ah ; the increment will initially be 10h
	
	; move 36h into fe03h for counter initialization
	mov dpl, #03h 
	mov dph, #0feh
	mov a, #076h
	movx @dptr, a
	
	; R0 holds the low counter value, R1 holds the high counter value
	mov R0, #0B5h ; starts the wave at ~55kHz, or 181d
	mov R1, #00h
	; move the values into the counter
	mov dpl, #01h
	mov a, R0
	movx @dptr, a 
	mov a, R1
	movx @dptr, a
	
	; initialize a timer to delay each change to the square wave
	mov TL0, #010h 
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #01h ; sets Mode 1 , 16 bit timer
	setb TR0 ; sets the start of the timer
	
	ret
	
updateFreq:
	; this subroutine updates the frequency and moves the values in r0 and r1 into the counter		
	mov a, R2 ; adds the offset to the frequency {10, 1, or 0}
	add a, R0 
	mov R0, a
	movx @dptr, a ; changes low counter
	
	mov a, #00h 
	addc a, R1 ; checks if overflow, and if so, adds 1
	mov R1, a
	movx @dptr, a ; changes high counter
	
	clr C
		
	ret
	
main:
	firststage: ; increasing the counter by 10 for initial probing
		jnb P1.0, secondStage ; if the Schmitt output goes low
		clr P1.7 ; for visualization
		sjmp firstStage
	
	secondStage: ; increasing the counter by 1 when close to resonance
		mov R2, #01h ; now increase by a lower amt
		clr P1.6 ; for visualization
		secondLoop:
			jb P1.0, finalStage ; if the Schmitt output goes high
		sjmp secondLoop
		
	finalStage: ; maintaining the striking frequency
		mov R2, #00h
		clr P1.5 ; for visualization
		finalLoop:
			sjmp finalLoop
