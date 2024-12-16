main:
	mov P1, #98h ; Character LED 9
	mov P1, #80h ; Character LED 8
	mov P1, #0F8h ; Character LED 7
	mov P1, #82h ; Character LED 6
	mov P1, #92h ; Character LED 5
	mov P1, #99h ; Character LED 4
	mov P1, #0B0h ; Character LED 3
	mov P1, #0A4h ; Character LED 2
	mov P1, #0F9h ; Character LED 1
	mov P1, #0C0h ; Character LED 0
	sjmp main 
