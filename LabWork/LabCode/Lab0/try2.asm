main:
mov P1, #11h ; makes port 1 pins 0 and 4 high and all else low
mov P1, #22h ; makes port 1 pins 1 and 5 high and all else low
mov P1, #33h ; makes port 1 pins 0, 1, 4, and 5 high and all else low
sjmp main
