;this program uses the keypad to determine whether or not to drive the mechanical linear relay
init:
	mov dptr, #0fe23h ; location of the 8255 control
	mov a, #80h
	movx @dptr, a ; initializes mode 0 in the 8255
	mov dpl, #22h ; location of the port C enable pins
	mov a, #00h ; initializes the control
	movx @dptr, a
	lcall digitWait

digitWait:
	jnb P3.4, digitWait; checks if a button has been pressed and DA is high
	mov a, P1
	anl a , #0fh ; just checks the bottom four bits
on:
	cjne a, #00h, off
	mov a, #01h
	movx @dptr, a ; turns on the drive to the relay
	sjmp digitWait
off:
	cjne a, #01h, digitWait
	mov a, #00h
	movx @dptr, a ; turns off the drive to the relay
	sjmp digitWait
	