; this routine switches between 0 and 80 as reference every 2 seconds, and updates the DAC voltage from the
; gain and ADC block every 1/125 seconds
.org 0h
ljmp start

.org 0Bh ; handles the interrupt of the timer 0 auto reload
	lcall switch
	lcall readadc
	reti

.org 100h
start:
	lcall init
	lcall main
	
init:
	; initialize gain
	mov R4, #02h ; gain is initially 2
	; initialize the 8255 and the lcd
	mov dptr, #0fe23h
	mov a, #80h
	movx @dptr, a ; initializes mode 0 in the 8255
	mov a, #00h ; initializes the control
	lcall cntrl
	mov a, #38h ; format is 5x7 character set
	lcall databus
	lcall strike_e1
	mov a, #0ch ; display on, no cursor
	lcall databus
	lcall strike_e1
	mov a, #01h ; clr display
	lcall databus
	lcall strike_e1
	mov a, #80h ; set RAM = 0
	lcall databus
	; initialize the DAC
	mov dptr, #0fe00h ; location of the DAC
	mov R2, #00h
	mov a, #00h ; initially zero
	movx @dptr, a ; sends the command to the DAC
	;initialize the timer
	mov TH0, #0a4h ; gives us 5kHz
	mov R0, #0c8h
	mov R1, #64h ; gives us 10000x decrease in period for reference voltge
	mov R3, #28h ; gives us 40x decrease in period for adc sampling
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #02h ; sets Mode 2, auto reload on T0
	mov tcon, #10h ; sets the start of the timer
	ret
	
main:
	lcall display_info
	sjmp main

display_info:
; this displays referance and Gain on the LCD
	;resets
	mov a, #01h ; clr display
	lcall databus
	lcall strike_e1
	mov a, #80h ; set RAM = 0
	lcall databus 
	; sends info
	mov a,#47h
	lcall snd_chr
	mov a, #3ah 
	lcall snd_chr
	mov a, R4
	add a, #30h
	lcall snd_chr
	mov a, R2
	cjne a, #00h, notzero	
	zero:
		mov a, #30h
		lcall snd_chr
		lcall delay
		lcall delay
		ret
	notzero:
		mov a, #32h
		lcall snd_chr
		mov a, #2eh 
		lcall snd_chr
		mov a, #35h 
		lcall snd_chr
		lcall delay
		lcall delay
		ret
	
cntrl:
; this moves the value in the accumulator to the control
	mov dptr, #0fe22h ; the control lines
	movx @dptr, a 
	ret

databus:
; this moves the value in the accumulator to the databus
	mov dptr, #0fe20h ; the data lines
	movx @dptr, a 
	ret

strike_e1:
; this just strikes the E flag and clears it
	mov dptr, #0fe22h ; the control lines
	mov a, #40h
	movx @dptr, a 
	mov a, #00h
	movx @dptr, a 
	ret
	
strike_e2:
; this just strikes the E flag and clears it for characters
	mov dptr, #0fe22h ; the control lines
	mov a, #0C0h
	movx @dptr, a 
	mov a, #80h
	movx @dptr, a 
	ret
	
delay:
; this just introduces a real time delay for the inputs to the lcd
	mov R6, #0ffh
	mov R7, #0ffh
	loop:
		djnz R6, loop
		mov R6, #0ffh
		djnz R7, loop
		ret
		
snd_chr:
; this sends it to the lcd
	lcall databus ; a already holds the value to be sent
	lcall strike_e2
	lcall delay
	ret

switch:
; this subroutine switches the reference and sends it to the DAC
	djnz R0, return ; makes sure that 10000 cycles have passed 
	mov R0, #0c8h
	djnz R1, return
	mov R1, #064h 
	mov a, R2 
	cjne a, #00h, down ; branches the switching
	up:
		mov R2, #80h
		ret
	down:
		mov R2, #00h
		
	return:
		ret

readadc:	
	djnz R3, returnadc
	mov R3, #28h
	mov dptr, #0fe10h ; location of the adc
	movx @dptr, a ; triggers the read
	waiting:
		jb P3.5, waiting ; waits for interrupt flag to be cleared
	movx a, @dptr  ; gets the value out of the adc
	mov R5, a ; R5 holds the adc output
	mov P1, a   ; displays it
	lcall changeDAC
	returnadc:
		ret
	
changeDAC:
; this subroutine takes the output of the 
	mov a, R2 ; R2 holds the reference
	clr C 
	subb a, R5 ; subtracts the adc from reference
	jnc inrange
	negativecommand:
		mov a, #00h ; negative command
		sjmp cmd
	inrange:
		; instead, multiplies by gain
		mov b, R4; R4 holds the gain
		mul ab ; a holds the product
		jnb OV, cmd ; jumps to cmd if the overflow isn't set
	oversaturated:
		mov a, #0ffh ; oversaturated command
	cmd:
		mov dptr, #0fe00h  
		movx @dptr, a
		ret
