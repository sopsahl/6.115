.org 00h
init:
	mov dptr, #0fe23h
	mov a, #80h
	movx @dptr, a ; initializes mode 0 in the 8255
	mov R0, #20h  ; the data bus
	mov R1, #22h  ; the control lines
	mov R2, #5d ; 5 characters to be displayed
	mov R3, #0d 
	mov a, #00h ; initializes the control
	lcall cntrl
	mov a, #38h ; format is 5x7 character set
	lcall databus
	lcall strike_e1
	mov a, #0ch ; display on, no cursor
	lcall databus
	lcall strike_e1
	rests:
	mov R2, #5d ; 5 characters to be displayed
	mov a, #01h ; clr display
	lcall databus
	lcall strike_e1
	mov a, #80h ; set RAM = 0
	lcall databus 
	lcall delay
	lcall get_voltage
	lcall main
	
cntrl:
; this moves the value in the accumulator to the control
	mov dpl, R1
	movx @dptr, a 
	ret

databus:
; this moves the value in the accumulator to the databus
	mov dpl, R0
	movx @dptr, a 
	ret

strike_e1:
; this just strikes the E flag and clears it
	mov dpl, R1
	mov a, #40h
	movx @dptr, a 
	mov a, #00h
	movx @dptr, a 
	ret
	
strike_e2:
; this just strikes the E flag and clears it for characters
	mov dpl, R1
	mov a, #0C0h
	movx @dptr, a 
	mov a, #80h
	movx @dptr, a 
	ret
	
main: 
; the main body of the program
	lcall fetch_char
	lcall snd_chr
	lcall delay
	djnz R2, main
	ljmp init ; restarts the process
	
	
delay:
; this just introduces a real time delay for the inputs to the lcd
	mov R4, #0ffh
	mov R5, #0ffh
	loop:
		djnz R5, loop
		mov R5, #0ffh
		djnz R4, loop
		ret
		
fetch_char:
; this gets the character
	mov a, R3 ; R3 holds the offset
	push dpl
	push dph
	mov dptr, #1000h ; location of the lookup table
	movc a, @a + dptr ; moves the entry with the offset
	inc R3
	pop dph
	pop dpl
	ret
		
snd_chr:
; this sends it to the lcd
	lcall databus ; a already holds the value to be sent
	lcall strike_e2
	ret

get_voltage:
; this gets the voltage and stores the value at 1000h
	mov dpl, #10h  ; location of the ADC
	movx @dptr, a 
	waiting:
		jb P3.5, waiting
	movx a, @dptr  ; gets the value out of the adc
	mov P1, a  ; displays in the P1 lights
	mov b, #51d 
	div ab ; a holds the ones, b holds the remainder
	add a, #30h ; the lcd equivalent of the output
	push dph
	mov dptr, #1000h ; location of the lookup table
	movx @dptr, a  ; moves the value to the ones
	mov a, b
	mov b, #5d 
	div ab
	add a, #30h ; the lcd equivalent of the output
	mov dpl, #02h
	movx @dptr, a  ; moves the value to the tenths
	pop dph
	ret
	

.org 1000h
.db 30h, 2eh, 30h, 20h, 56h 

	