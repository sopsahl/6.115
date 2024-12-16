mov P1, #0FFh ;adds 255d to the pointer to begin
loop:
	clr P0.7
	dec P1 ; decreases the value in P1 by 1
	setb P0.7
      sjmp loop ; jumps to loop
