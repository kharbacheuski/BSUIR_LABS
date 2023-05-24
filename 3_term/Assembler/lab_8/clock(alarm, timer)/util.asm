.code
;lea dx,(data) for display
print proc
	mov ah,09h
	int 21h
	ret
print endp

;store input as input
scan proc
	mov ah,0ah
	int 21h
	ret
scan endp

;clear screen for cyan color
clr_src proc

	mov ax,0600h
	mov bh,7fh
	mov cx,0000h
	mov dx,184fh
	int 10h
	 
	mov dh,0		;set row
	mov dl,25		;set column
	call res_cur
	 
	ret
clr_src endp

;INT 10 - AH = 02h VIDEO - SET CURSOR POSITION
res_cur proc
	;dh = row,dl = column
	mov bh,0
	mov ah,02h
	int 10h
	ret
res_cur endp


