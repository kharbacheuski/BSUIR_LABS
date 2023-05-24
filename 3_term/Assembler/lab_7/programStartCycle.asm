.MODEL tiny

.CODE

START:               
    mov ax, @data
    mov ds, ax
    mov es, ax  
    
    call PARSE_CMD      
                        
    xor cx, cx 
    mov cl, TIMES_TO_RUN   ; count of runs programm    
  
    cmp cl, 0
    je EXIT               
    
    mov sp, PROGRAMM_LENGTH + 300h ; move stack na 200h
    mov ah, 4ah   ; set size of memory block  
    STACK_SHIFT = PROGRAMM_LENGTH + 300h   
    mov bx, STACK_SHIFT shr 5
    int 21h                
    
    mov ax, cs
    mov word ptr EPB + 4,   ax      ; command string seg
    mov word ptr EPB + 8,   ax      ; first fcb seg
    mov word ptr EPB + 0ch, ax      ; second fcb seg
    
    lea dx, TIMES_TO_RUN_STR
    mov ah, 9
    int 21h
    
    RUN_PROGRAM_CYCLE:    
        mov ax, 4b00h       ; load and run programm
        lea dx, PROGRAM_NAME  ; address of program
        lea bx, EPB   ; params EPB
        int 21h
        
        jc FATAL_ERROR
                            
    loop RUN_PROGRAM_CYCLE    
    
    int 20h

EXIT:        
    mov ah, 4ch
    int 21h        
    
FATAL_ERROR:      
    mov ah, 9
    cmp al, 2
    je SET_FILE_NOT_FOUND
    cmp al, 5
    je SET_ACCESS_DENIED
    cmp al, 0bh
    je SET_NOT_VALID_FORMAT
    
SHOW_MESSAGE:  
    int 21h   
    jmp EXIT
    
SET_FILE_NOT_FOUND:  
    lea dx, FILE_NOT_FOUND_MESSAGE
    jmp SHOW_MESSAGE

SET_ACCESS_DENIED:   
    lea dx, ACCESS_DENIED_MESSAGE 
    jmp SHOW_MESSAGE

SET_NOT_VALID_FORMAT:  
    lea dx, NOT_VALID_FORMAT_MESSAGE
    jmp SHOW_MESSAGE
    
PARSE_CMD proc      
    mov cl, [80h]
    cmp cl, 0
    je EMPTY_PARAMETER
    
    mov di, 82h
                    
    call SKIP_SPACES
    lea si, PROGRAM_NAME 
    call WRITE_PARAMETR      
                                         
    call SKIP_SPACES
    lea si, TIMES_TO_RUN_STR    
    call WRITE_PARAMETR                                                 
    call TO_DIGIT     
    
    lea si, PARAMETER_FOR_RUN_PROGRAM     
    call SKIP_SPACES
    
    dec di
    WRITE_PARAMETER_FOR_RUN_PROGRAM:
        cmp [di], 0dh  
        je EXIT_FROM_PARSE
        
        mov al, [di]
        mov [si], al      
        
        inc si
        inc di
    jmp WRITE_PARAMETER_FOR_RUN_PROGRAM
            
    EXIT_FROM_PARSE:              
    ret       
    
EMPTY_PARAMETER:  
    mov ah, 9
    lea dx, EMPTY_PARAMETER_MESSAGE
    int 21h
    mov ah, 4ch
    int 21h
PARSE_CMD endp               
    
WRITE_PARAMETR proc         
     WRITE_CYCLE:
        mov al, [di]    
        cmp al, 0
        je END_OF_WRITE
        cmp al, ' '
        je END_OF_WRITE  
        cmp al, 9
        je END_OF_WRITE     
        cmp al, 0dh
        je END_OF_WRITE 
        mov [si], al               
        inc di
        inc si
        jmp WRITE_CYCLE    
                       
    END_OF_WRITE:          
    ret 
WRITE_PARAMETR endp

SKIP_SPACES proc     
    dec di
    CYCLE:  
        inc di
        cmp [di], 0dh
        je END_OF_SKIPPING
        cmp [di], 0
        je END_OF_SKIPPING
        cmp [di], ' '
        je CYCLE
        cmp [di], 9     
        je CYCLE
    END_OF_SKIPPING:
    ret
SKIP_SPACES endp

TO_DIGIT proc     
    push di
    call IS_VALID_DIGIT      
        
    lea di, TIMES_TO_RUN_STR
    xor bx, bx     
    xor ax, ax
    mov bl, 10
    
    TO_DIGIT_CYCLE:   
        mov cl, [di] 
        sub cl, '0'
              
        mul bx
        add al, cl
        inc di
        cmp [di], '$'
    jne TO_DIGIT_CYCLE                                 
    pop di 
    mov TIMES_TO_RUN, al                 
    ret     
TO_DIGIT endp    

IS_VALID_DIGIT proc      
    lea di, TIMES_TO_RUN_STR
    xor cx, cx
    mov cl, 4
    
    FIND_SIZE_CYCLE:    
        cmp [di], '$'       
        je EXIT_FROM_CYCLE              
        cmp [di], '0'
        jl NOT_VALID_DIGIT
        cmp [di], '9'
        jg NOT_VALID_DIGIT
           
        inc di     
    loop FIND_SIZE_CYCLE  
    
    EXIT_FROM_CYCLE:    
    
    lea di, TIMES_TO_RUN_STR      
    cmp cl, 4
    je NOT_VALID_DIGIT
    
    cmp cl, 1
    jl NOT_VALID_DIGIT
    je IS_LOWER    
    ret           

IS_LOWER:
    cmp [di], '2'
    jg NOT_VALID_DIGIT
    cmp [di + 1], '5'
    jg NOT_VALID_DIGIT
    cmp [di + 2], '5'
    jg NOT_VALID_DIGIT      
    ret
    
NOT_VALID_DIGIT:     
    mov ah, 9
    lea dx, NOT_VALID_DIGIT_MESSAGE
    int 21h 
    mov ah, 4ch
    int 21h    
        
IS_VALID_DIGIT endp

LINE db 128 dup ('$')
TIMES_TO_RUN db 0
TIMES_TO_RUN_STR db 4 dup('$')
PROGRAM_NAME db 128 dup(0)           
PARAMETER_FOR_RUN_PROGRAM 128 dup(0dh)

EPB dw 0000  ;WORD
    dw offset PARAMETER_FOR_RUN_PROGRAM ; command string address
    dw 005ch, 0, 006ch, 0     ; FCB adresses   

NOT_VALID_DIGIT_MESSAGE db "Digit must be in [0, 255]$"       
EMPTY_PARAMETER_MESSAGE db "You should enter name of program and quantity of starts$"
FILE_NOT_FOUND_MESSAGE db "Executable file not found$"
ACCESS_DENIED_MESSAGE db "Access denied$"    
NOT_VALID_FORMAT_MESSAGE db "Not valid format message$"

PROGRAMM_LENGTH EQU $ - START
end START
