; this routine takes the values at #9000h and #9001h and calculates the 
; sum, difference, product, quotient, and remainder in the successive bits #9002-7
.org 8000h
main:
	lcall getab
	lcall getsum
	lcall getdifference
	lcall getproduct
	lcall getquotient
	ljmp 0000h ; return to the minmon operation
		
getab:
;this subroutine gets the two numbers from external memory
	mov dpl, #00h ; data pointer low
	mov dph, #90h ; data pointer high 
	movx a, @dptr ; move the first number into R0
	mov R0, a
	inc dptr
	movx a, @dptr ; move the second number into R1
	mov R1, a
	ret

addResult:
;this subroutine adds the result in A to the next location in memory
	inc dptr
	movx @dptr, a
	ret
	
	
getsum:
; this subroutine gets the value of the sum and adds it to memory
	mov a, R0
	add a, R1
	lcall addResult
	ret

getdifference:
; this subroutine gets the value of the difference and adds it to memory
	mov a, R0
	clr C 
	subb A, R1
	lcall addResult
	ret
	
getproduct:
; this subroutine gets the value of the product and adds it to memory
; Note: it'll add it lower half, upper half
	mov a, R0
	mov b, R1
	mul ab
	lcall addResult ; adding the lower half of the product
	mov a, b
	lcall addResult ; adding the upper half of the product
	ret
	
getquotient:
; this subroutine gets the value of the quotient and remainder and adds it to memory
; Note: it'll add quotient, remainder
	mov a, R0
	mov b, R1
	div ab
	lcall addResult ; adding the quotient
	mov a,b 
	lcall addResult ; adding the remainder
	ret
	
	
