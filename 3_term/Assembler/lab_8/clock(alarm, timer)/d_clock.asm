;macro is like a function that can accept input parameter and process the code in main function
;row_drawer is a macro that use to draw the horizontal line in the vga mode of dosbox
row_drawer macro row, start_col, end_col, color 
	local con_col
	
	mov	ah,0ch				;draw pixel
	mov	bh,0				;page
	mov	al,color			;color
	mov cx,start_col		;column
	mov	dx,row				;row
	
	con_col : 	
	
		int	10h				;draw 
		inc cx
		cmp cx, end_col
		jle con_col
		
endm

;col_drawer is a macro that use to draw the horizontal line in the vga mode of dosbox
col_drawer macro column, start_row, end_row, color 
	local con_row
	
	mov	ah,0ch				;draw pixel
	mov	bh,0				;page
	mov	al,color			;color
	mov cx,column			;column
	mov	dx,start_row		;row
	
	con_row : 	
	
		int	10h				;draw 
		inc dx
		cmp dx, end_row
		jle con_row
		
endm
.code
reset_print	proc
	;row
	mov	ax,start_row
	mov	row_1,0
	add	row_1,ax
	mov	row_2,25
	add	row_2,ax
	mov	row_3,50
	add	row_3,ax
	
	;column	
	mov	ax,start_col
	mov	col_1,0
	add	col_1,ax
	mov	col_2,20
	add	col_2,ax

	row_drawer	row_1,col_1,col_2,clock_color
	row_drawer	row_2,col_1,col_2,clock_color
	row_drawer	row_3,col_1,col_2,clock_color
	col_drawer	col_1,row_1,row_3,clock_color
	col_drawer	col_2,row_1,row_3,clock_color
	
	sub col_2,5
	col_drawer	col_2,row_1,row_3,clock_color
	
	ret
reset_print	endp

print_0 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,50
	add	row_2,ax

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color		
	row_drawer 	row_2, col_1, col_2, color	

	col_drawer 	col_1, row_1, row_2, color		
	col_drawer 	col_2, row_1, row_2, color	
	ret
print_0 endp

print_1 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,50
	add	row_2,ax

	;column
	mov	ax,start_col
	mov col_1,10
	add	col_1,ax
	mov col_2,15
	add	col_2,ax			
			
	col_drawer 	col_2, row_1, row_2, color	
	row_drawer 	row_1, col_1, col_2, color	
	
	ret
print_1 endp

print_2 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	col_drawer 	col_2, row_1, row_2, color		
	row_drawer 	row_2, col_1, col_2, color
	col_drawer 	col_1, row_2, row_3, color	
	row_drawer 	row_3, col_1, col_2, color

	ret
print_2 endp

print_3 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	row_drawer 	row_2, col_1, col_2, color
	row_drawer 	row_3, col_1, col_2, color
	col_drawer 	col_2, row_1, row_3, color		

	ret
print_3 endp

print_4 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax	

					
	col_drawer 	col_1, row_1, row_2, color		
	sub row_2,25
	col_drawer 	col_2, row_2, row_3, color	
	add row_2,25
	row_drawer 	row_2, col_1, col_2, color	
	
	ret
print_4 endp

print_5 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	col_drawer 	col_1, row_1, row_2, color		
	row_drawer 	row_2, col_1, col_2, color
	col_drawer 	col_2, row_2, row_3, color	
	row_drawer 	row_3, col_1, col_2, color

	ret
print_5 endp

print_6 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	col_drawer 	col_1, row_1, row_3, color		
	row_drawer 	row_2, col_1, col_2, color
	col_drawer 	col_2, row_2, row_3, color	
	row_drawer 	row_3, col_1, col_2, color

	ret
print_6 endp

print_7 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,50
	add	row_2,ax

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	col_drawer 	col_2, row_1, row_2, color		

	ret
print_7 endp

print_8 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	col_drawer 	col_1, row_1, row_3, color		
	row_drawer 	row_2, col_1, col_2, color
	col_drawer 	col_2, row_1, row_3, color	
	row_drawer 	row_3, col_1, col_2, color

	ret
print_8 endp

print_9 proc
	;row
	mov	ax,start_row
	mov row_1,0
	add	row_1,ax
	mov row_2,25
	add	row_2,ax
	mov row_3,50
	add	row_3,ax	

	;column
	mov	ax,start_col
	mov col_1,0
	add	col_1,ax
	mov col_2,20
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	col_drawer 	col_1, row_1, row_2, color		
	row_drawer 	row_2, col_1, col_2, color
	col_drawer 	col_2, row_1, row_3, color	
	row_drawer 	row_3, col_1, col_2, color

	ret
print_9 endp

print_seperator proc
	;row
	mov	ax,start_row
	mov row_1,13
	add	row_1,ax
	mov row_2,38
	add	row_2,ax
	;column
	mov	ax,start_col
	mov col_1,9
	add	col_1,ax
	mov col_2,11
	add	col_2,ax			
			
	row_drawer 	row_1, col_1, col_2, color			
	
	row_drawer 	row_2, col_1, col_2, color

	ret
print_seperator endp