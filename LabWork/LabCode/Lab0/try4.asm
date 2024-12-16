mov P1, #0FFh ;adds 255d to the pointer to begin
loop:
	mov R0, #97d ; initializes the delay to 97 (not 100 bc we add three instructions)
	delay:
		djnz R0, delay ;decrements the counter and jumps if 100 cycles haven't passed
	dec P1 ; decreases the value in P1 by 1
	sjmp loop ; jumps to loop
