.code

;In dl out dl 
bcd2dec proc
	mov ah,0
	mov al,dl
	shr al,4

	mov cl,10
	mul cl
	mov cl,al
	mov al,dl
	shl al,4
	shr al,4	

	add al,cl
	mov dl,al
	ret
bcd2dec endp  

;Input theta radius adjust_x and adjust_y out x,y
;x = r - r cosθ + adjust_x, y = r -r sinθ + adjust_y		
circle_func proc
	fdiv deg_180		;convert degree to radian

	fldpi				;load pi=3.142
		
	fmul 				;floating point multiplication
		
	fsincos				;st(0)=cos, st(1)=sin
	
	fimul radius		;integer and floating point multiplication
	fchs				;st(0) = -st(0)

	fiadd adjust_x		;integer and floating point addition

	fiadd radius	
	
	fistp x				;x=st(0), and pop st(0)
	
	fimul radius
	fchs		

	fiadd adjust_y

	fiadd radius	
	
	fist y
	
	ret
circle_func endp

