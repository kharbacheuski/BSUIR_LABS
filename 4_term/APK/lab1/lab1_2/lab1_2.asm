data segment
    startProgram db 'Start$'
    enterSymbol db 'Enter symbol: $'
    output db 'Output: $'
data ends

code segment

newLine:
    mov ah, 02h
    mov dl, 0ah
    int 21h
    
    mov ah, 02h
    mov dl, 0dh
    int 21h
ret

printFromCOM:    
    MOV DX, 01h       ; dx = 1 (com2)
    MOV AH, 02H       ; read letter from channel
    INT 14H           ; al - symbol
    
    xor dx, dx
    MOV DL,AL         ; al - data byte
    MOV AH,02H        ; print letter
    INT 21H
ret

writeToCOM:   
    MOV DX, 0        ; port number com1
    MOV AH,01H       ; send letter to channel
    INT 14H
ret

start:
    mov ax, data
    mov ds, ax
    
    mov ah, 9h
    mov dx, offset startProgram
    int 21h
    
    call newLine
    call newLine
    
    XOR AX,AX
    
    MOV AL,11100011B ; port init
    xor dx,dx        ; dx = 0 (com1)
    MOV AH,00H
    INT 14H
    
    mov ah, 9h
    mov dx, offset enterSymbol
    int 21h
    
    xor ax, ax
    
    MOV AH, 01H      ; read a character from console
    INT 21H          ; in al - your symbol
   
    
    call writeToCOM  ; write al into com      
                                      
    MOV AL, 'e'
    call writeToCOM  ; write al into com     
    MOV AL, 'l'
    call writeToCOM  ; write al into com
    MOV AL, 'l'
    call writeToCOM  ; write al into com
    MOV AL, '0'
    call writeToCOM  ; write al into com
    
    call newLine
    call newLine
    
    mov ah, 9h
    mov dx, offset output
    int 21h
    
    xor ax, ax
    
    MOV AL, 11100011B ; port init
    MOV DX, 01h       ; dx = 1 (com2)
    MOV AH, 00H
    INT 14H
    

    call printFromCOM      
    call printFromCOM
    call printFromCOM
    call printFromCOM
    call printFromCOM
    
    MOV AX, 4C00H     ; exit
    INT 21H
    
    code ends
end start










; [SOURCE]: C:\Users\admin\Desktop\work.asm
