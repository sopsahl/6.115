; this routine cycles through a spindude and reads out the values
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
			mov R2, #25h 
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
	; initialize the interface with the spindude
	mov p1, #00h
	setb P3.3 ; E1 not active
	ret

step:
; this subroutine turns the stepper motor once
	djnz R0, return ; makes sure that 10000 cycles have passed 
	mov R0, #064h
	djnz R1, return
	mov R1, #064h 
	clr ea ; stops the interrupt
	djnz R2, cycle ; checks if we've stepped 24 times
		ret
	; cycles through the commands
	cycle:
	mov a, #01h
	mov P1, a
	movx @dptr, a ; turns on 1a
	mov a, #04h
	mov P1, a
	movx @dptr, a ; turns on 2a
	mov a, #02h
	mov P1, a
	movx @dptr, a ; turns on 1b
	mov a, #08h
	mov P1, a
	movx @dptr, a ; turns on 2b
	mov a, #00h
	mov P1, a
	movx @dptr, a ; turns all off
	; cycles through the photoresistors
	mov R3, #10h
	scanloop:
		mov P1, R3 ; selects a specific photoresistor and led
		clr P3.3 ; activates the light
		mov R4, #0ffh
		innerloop:
			djnz R4, innerloop ; waits for led to settle
		lcall read_adc
		setb P3.3
		lcall prthex
		mov a, #20h ; makes a space
		lcall sndchr
	
		djnz R3, scanloop
		lcall crlf
	return:
		ret

readadc:	
	mov dptr, #0fe10h ; location of the adc
	movx @dptr, a ; triggers the read
	waiting:
		jb P3.5, waiting ; waits for interrupt flag to be cleared
	movx a, @dptr  ; gets the value out of the adc
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
	ret
	
;===============================================================
; subroutine prthex
; this routine takes the contents of the acc and prints it out
; as a 2 digit ascii hex number.
;===============================================================
prthex:
   push acc
   lcall binasc           ; convert acc to ascii
   lcall sndchr           ; print first ascii hex digit
   mov   a,  r5           ; get second ascii hex digit
   lcall sndchr           ; print it
   pop acc
   ret
;===============================================================
; subroutine binasc
; binasc takes the contents of the accumulator and converts it
; into two ascii hex numbers.  the result is returned in the
; accumulator and r5.
;===============================================================
binasc:
   mov   r5, a            ; save in r5
   anl   a,  #0fh         ; convert least sig digit.
   add   a,  #0f6h        ; adjust it
   jnc   noadj1           ; if a-f then readjust
   add   a,  #07h
noadj1:
   add   a,  #3ah         ; make ascii
   xch   a,  r5           ; put result in reg 2
   swap  a                ; convert most sig digit
   anl   a,  #0fh         ; look at least sig half of acc
   add   a,  #0f6h        ; adjust it
   jnc   noadj2           ; if a-f then re-adjust
   add   a,  #07h
noadj2:
   add   a,  #3ah         ; make ascii
   ret
