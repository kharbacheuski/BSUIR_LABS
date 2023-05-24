data segment
    writingError db 10, 13, "Write error!$"
    readingError db 10, 13, "Read error!$"
    output db "Output: $"
    dataForSending db 'F'
    dataForReading db ?  
data ends

code segment
    
    initializeCOM1 proc
        mov al, 80h
        mov dx, 3FBh
        out dx, al
        
        mov dx, 3F8h
        mov al, 00h
        out dx, al
        mov al, 0Ch
        mov dx, 3F9h
        out dx, al
        
        mov dx, 3FCh
        mov al, 00001011b
        out dx ,al
        
        mov dx, 3F9h
        mov al, 0
        out dx, al
        ret
    initializeCOM1 endp
    
    isWritedInCOM1 proc
        xor al, al  
       
        mov dx, 3FDh
        in al, dx
        test al, 10h
        jnz NoWRite
        ret
    isWritedInCOM1 endp
    
    NoWRite proc
       mov ah, 09h
       mov dx, offset writingError
       int 21h
       ret 
    NoWRite endp
    
    isReadedFromCOM2 proc
        xor al, al
        mov dx, 3FDh
        in al, dx
        test al, 10b
        jnz NoRead
        ret
    isReadedFromCOM2 endp
    
    NoRead proc
       mov ah, 09h
       mov dx, offset readingError
       int 21h
       ret 
    NoRead endp
    
    sendData proc
        mov dx, 3F8h
        mov al, dataForSending
        out dx, al
        ret
    sendData endp
    
    readData proc
        mov dx, 3F8h
        in al, dx
        mov dataForReading, al
        ret
    readData endp
    
    start:
        mov ax, @data
        mov ds, ax       
        
        call initializeCOM1
        call isWritedInCOM1
        call sendData   
        
        mov al, 02h
        call isReadedFromCOM2   
        
        call readData    
        
        mov dx, offset output
        mov ah, 09h
        int 21h    
        
        mov ah, 02h
        mov dl, dataForReading
        int 21h   
        
        mov ax, 4C00h
        int 21h
        
        code ends    

end start