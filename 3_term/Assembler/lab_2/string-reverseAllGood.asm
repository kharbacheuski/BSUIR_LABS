data segment 
    
     str db 200,0, 200 dup ('$')  
     startProgram db '____Start____$'
     enterString db 'Enter string: $'
     revertString db 'Revert string: $'  
     
     lastStackElement equ 49
     
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
    
start:  mov ax, data
        mov ds, ax  
        
        mov ah, 9h
        mov dx, offset startProgram  
        int 21h 
          
        call newLine
        call newLine 
        
        mov ah, 9h
        mov dx, offset enterString  
        int 21h
        
        mov ah,0aH                  ; read string from keybord
        mov dx, offset str          ; into buffer
        int 21h
         
        mov di, offset str          ; di = buffer address          
        mov bx, 0h                  ; clear bx register
        mov bl, [di+1]              ; bl = real string length 
        mov byte ptr [di+bx+2], '$' ; last symbol = '$'  
            
        call newLine 
        call newLine 
        
        mov ah, 9h
        mov dx, offset revertString 
        int 21h 
        
        mov si, bx
        add si, 2
        mov cx,bx     ; length of string 
        inc cx
        push lastStackElement 
        
stack:  cmp str[si],' '   ; if symbol == ' '
        je pushing   
        cmp str[si],'$'   ;  or symbol == '$'
        je pushing  
        jne next 
        
        pushing:          ; push index of last symbol of each word
            push si
            jmp next 
              
        next: 
            dec si
            loop stack 
             
word:  pop bx      ; pop index of last space before each word
       mov dl, ' '
       int 21h
       cmp bx, lastStackElement 
       je endProgram  
       jne print
       print:  
            mov cx, bx
            add cx, -2 ; cycle for length - 2 
            add bx, -1 ; index of space - 1
            printSymbol:  
                cmp str[bx], ' ' 
                je word                     
                jne nextSymbol  
                    
                nextSymbol: 
                    cmp str[bx], ' ' 
                    je word  
                    mov ah, 02h
                    mov dl, str[bx]  
                    int 21h 
                    dec bx 
                    loop printSymbol
                    jmp word
      
endProgram: int 10h 

code ends
end start






