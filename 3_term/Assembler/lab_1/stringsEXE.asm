; strings EXE

data segment 
    strOne db 10, 13, "Smells like$"
    strTwo db 10, 13, "Teen Spirit$"
    strThree db 10, 13, "Nirvana (Grunge)$"   
ends

stack segment 
    dw 128 dup(0)
ends

code segment
start: 
    mov ax, data;
    mov ds, ax;
    mov es, ax;
    
    lea dx, strOne;
    mov ah, 9;
    int 21h;    
    
    lea dx, strTwo;
    mov ah, 9;
    int 21h;
    
    lea dx, strThree;
    mov ah, 9;
    int 21h;      
    
    mov ax, 4c00h;
    int 21h;
ends

end start;