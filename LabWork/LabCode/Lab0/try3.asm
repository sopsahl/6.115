mov P1, #11h ;makes port 1 pins 0 and 4 high
mov P1, #22h ;makes port 1 pins 1 and 5 high and all else low
loop:
	mov P1, #55h ; makes port 1 pins 0, 2, 4, and 6 high and all else low
	sjmp loop ; previous line will be repeated indefinitely

