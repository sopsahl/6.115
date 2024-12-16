.org 00h
init:
	mov dptr, #0fe23h
	mov a, #80h
	movx @dptr, a ; initializes mode 0 in the 8255
	mov R0, #20h  ; the data bus
	mov R1, #22h  ; the control lines
	mov R2, #40d  ; the max length of the message
	mov R3, #00h  ; initializing the pointer
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
	lcall delay
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
term1: ; all characters printed
	sjmp term1
	
	
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
	jz term2 ; checks to see if terminated by a null character
	inc R3
	pop dph
	pop dpl
	ret
	term2:
		sjmp term2
		
snd_chr:
; this sends it to the lcd
	lcall databus ; a already holds the value to be sent
	lcall strike_e2
	ret

.org 1000h
.db 36h, 2eh, 31h, 31h, 35h, 20h, 52h, 75h, 6Ch, 65h, 73h, 21h, 00h
	

	