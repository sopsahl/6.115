; this program makes the tie fighter with rotation

.org 00h
	ljmp start ; jumps to the main body of our program (at 100h)

.org 0Bh ; handles the interrupt of the timer 0 auto reload
	lcall send_x
	lcall send_y
	reti

.org 100h
start: 
	lcall init
	lcall main

main:
	sjmp main ; infinite loop
	
init:
	; initializing the offset counters
	mov R0, #00h ; x low count
	mov R1, #00h ; x high count
	mov R2, #00h ; y low count
	mov R3, #40h ; y high count
	; initializing the offsets
	mov R4, #00h ; x low
	mov R5, #01h ; x high
	mov R6, #0Efh ; y low (subtracted 0.0625 offset for a 1.25 Hz rotation)
	mov R7, #02h ; y high
	; initializing the timer
	mov TH0, #04ch ; gives us enough time to get computations: 5120 int/sec
	mov ie, #82h ; sets the TF0 interrupt
	mov tmod, #02h ; sets Mode 2, auto reload on T0
	mov tcon, #10h ; sets the start of the timer
	ret
	

send_x:
	clr C
	mov a, R0
	add a, R4 ; increments the low count
	mov R0, a
	mov a, R1
	addc a, R5 ; increments the high count with the carry
	mov R1, a
	lcall get_val ; gets the value from the table
	mov dptr, #0fe40h
	movx @dptr, a  ; sends it to the xDac
	ret

send_y:
	clr C
	mov a, R2
	add a, R6 ; increments the low count
	mov R2, a
	mov a, R3
	addc a, R7 ; increments the low count with the carry
	mov R3, a
	lcall get_val ; gets the value from the table
	mov dptr, #0fe44h 
	movx @dptr, a  ; sends it to the yDac
	ret

get_val:
; a holds the offset
	clr C
	mov dptr, #1000h 
	movc a, @a + dptr ; moves the entry with the offset
	mov b, #2d
	div ab ; divides the result by 2
	ret
	
.org 1000h
.db 080h, 083h, 086h, 089h, 08Ch, 08Fh, 092h, 095h, 098h, 09Bh, 09Eh, 0A2h, 0A5h, 0A7h, 0AAh, 0ADh, 0B0h, 0B3h, 0B6h, 0B9h, 0BCh, 0BEh, 0C1h, 0C4h, 0C6h, 0C9h, 0CBh, 0CEh, 0D0h, 0D3h, 0D5h, 0D7h, 0DAh, 0DCh, 0DEh, 0E0h, 0E2h, 0E4h, 0E6h, 0E8h, 0EAh, 0EBh, 0EDh, 0EEh, 0F0h, 0F1h, 0F3h, 0F4h, 0F5h, 0F6h, 0F8h, 0F9h, 0FAh, 0FAh, 0FBh, 0FCh, 0FDh, 0FDh, 0FEh, 0FEh, 0FEh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FEh, 0FEh, 0FEh, 0FDh, 0FDh, 0FCh, 0FBh, 0FAh, 0FAh, 0F9h, 0F8h, 0F6h, 0F5h, 0F4h, 0F3h, 0F1h, 0F0h, 0EEh, 0EDh, 0EBh, 0EAh, 0E8h, 0E6h, 0E4h, 0E2h, 0E0h, 0DEh, 0DCh, 0DAh, 0D7h, 0D5h, 0D3h, 0D0h, 0CEh, 0CBh, 0C9h, 0C6h, 0C4h, 0C1h, 0BEh, 0BCh, 0B9h, 0B6h, 0B3h, 0B0h, 0ADh, 0AAh, 0A7h, 0A5h, 0A2h, 09Eh, 09Bh, 098h, 095h, 092h, 08Fh, 08Ch, 089h, 086h, 083h, 080h, 07Ch, 079h, 076h, 073h, 070h, 06Dh, 06Ah, 067h, 064h, 061h, 05Dh, 05Ah, 058h, 055h, 052h, 04Fh, 04Ch, 049h, 046h, 043h, 041h, 03Eh, 03Bh, 039h, 036h, 034h, 031h, 02Fh, 02Ch, 02Ah, 028h, 025h, 023h, 021h, 01Fh, 01Dh, 01Bh, 019h, 017h, 015h, 014h, 012h, 011h, 00Fh, 00Eh, 00Ch, 00Bh, 00Ah, 009h, 007h, 006h, 005h, 005h, 004h, 003h, 002h, 002h, 001h, 001h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 001h, 001h, 001h, 002h, 002h, 003h, 004h, 005h, 005h, 006h, 007h, 009h, 00Ah, 00Bh, 00Ch, 00Eh, 00Fh, 011h, 012h, 014h, 015h, 017h, 019h, 01Bh, 01Dh, 01Fh, 021h, 023h, 025h, 028h, 02Ah, 02Ch, 02Fh, 031h, 034h, 036h, 039h, 03Bh, 03Eh, 041h, 043h, 046h, 049h, 04Ch, 04Fh, 052h, 055h, 058h, 05Ah, 05Dh, 061h, 064h, 067h, 06Ah, 06Dh, 070h, 073h, 076h, 079h, 07Ch 
