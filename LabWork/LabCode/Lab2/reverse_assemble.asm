.org 00h
start:
	mov A, #00h
	mov P1, acc
	setb P1.2
	sjmp start
	
.db "Party on in 6.115!"
	