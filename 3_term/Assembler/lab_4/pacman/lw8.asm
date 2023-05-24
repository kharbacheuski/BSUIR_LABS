.model tiny
.code 
.386
org 100h    
    
     
            
main:     

    jmp installer

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

defaultINT9         dd  0 

finishWritingMessage    db  13, 10, 'Finish file writing.', '$'

cmdMaxLength        equ 126                       
filePath            db  cmdMaxLength + 1 dup(0)  
filePathLength      db  ? 
fileID              dw  ?
filePosition        dw  2 dup(0)
bufferChar          db  ? 

printMessage macro string
    push cs
    pop ds
    mov ah, 9
    lea dx, string 
    int 21h 
endm

handlerINT9 proc far
    pushf
    call cs:defaultINT9    
    
    pusha
    push ds
    push es  
    
    push cs
    pop ds
    
    in al, 60h      
    
    cmp al, 80h
    jae endHandler
    
    cmp al, 1
    jne workWithFile
    
    printMessage finishWritingMessage
    
    cli
    mov dx, word ptr [offset defaultINT9] 
    mov ax, word ptr [offset defaultINT9 + 2]
    mov ds, ax
    mov ah, 25h
    mov al, 09h 
    int 21h
    sti   

    mov ah, 49h
	push cs
	pop es
    int 21h
    jmp endHandler
    
    workWithFile:
    mov  byte ptr bufferChar, al
    call saveInFile
    
    endHandler: 
    mov al, 20h
    out 20h, al       
    pop es
    pop ds
    popa   
         
    iret
handlerINT9 endp

openFile proc
    mov ah, 3dh
    mov al, 00000001b   ;write mode
    mov cl, 00000000b
    mov dx, offset filePath
    int 21h
    mov fileID, ax  
    jnc openFileSuccessfully
    
    jmp endHandler    
    
    openFileSuccessfully:  
    ret
openFile endp

closeFile proc
    mov ah, 3eh
    mov bx, fileID
    int 21h
    jnc closeFileSuccessfully      
    
    jmp endHandler
    
    closeFileSuccessfully:
    ret
closeFile endp

setPointer proc 
    ;si = offset shift  
    mov ah, 42h  
    mov al, 0
    mov bx, fileID
    mov cx, [si]
    mov dx, [si + 2]
    int 21h        
    jnc setPointerSuccessfully    
    
    jmp endHandler
    
    setPointerSuccessfully: 
    ret
setPointer endp  

incIndex proc
    ;si = offset index      
        cmp word ptr [si + 2], 0ffffh
        jne incSmallPart
    incBigPart:
        mov ax, [si]
        add ax, 1
        mov word ptr [si], ax
        mov ax, 0
        mov word ptr [si + 2], ax
        ret
    incSmallPart:
        mov ax, [si + 2]
        add ax, 1
        mov word ptr [si + 2], ax
        ret    
incIndex endp

writeFile proc
    ;dx = offset buffer, cl = length       
    mov ah, 40h
    mov bx, fileID
    xor ch, ch
    int 21h 
    jnc writeFileSuccessfully  
    
    jmp endHandler
    
    writeFileSuccessfully: 
    ret
writeFile endp

saveInFile proc
    call openFile     
    
    mov si, offset filePosition 
    call setPointer  
    
    mov cl, 1
    mov dx, offset bufferChar
    call writeFile           
    
    mov si, offset filePosition 
    call incIndex 
    
    call closeFile   
    ret    
saveInFile endp 

endResidentPart:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

emptyCmdErrorMessage          db  'Error. Cmd is empty.', 13, 10, '$'
excessCharsErrorMessage       db  'Error. File path contains excess characters.', 13, 10, '$'
filePathErrorMessage          db  'Error. File is not found.', 13, 10, '$'
fileExtensionMessage          db  'Error. File must be TXT.', 13, 10, '$'

fileIsFoundMessage            db  'File is found.', 13, 10, '$'
setHandlerMessage             db  'Set new int9 handler.', 13, 10, '$'
storeResPartMessage           db  'Store resident part.', 13, 10, '$'
   
copyFilePath proc 
    push cs
    pop es         
	
	fillFilePathLength:
    	xor cx, cx        
    	mov si, 80h
    	mov cl, ds:[si]
    	dec cl
    	mov es:filePathLength, cl
	
	checkEmptyCmd:                
    	cmp cl, 0ffh
    	jne fillFilePath
    	mov ds, ax 
    	printMessage emptyCmdErrorMessage
        jmp exit
	
	fillFilePath:
    	add si, 2
    	mov di, offset filePath
    	rep movsb 
    	  
    push cs
    pop ds 
    ret
copyFilePath endp
        
findFile macro 
    mov ah, 4eh
	mov cx, 0			
	mov dx, offset filePath
	int 21h
endm 
      
checkFilePath proc 
	checkExcessCharsInFilePath: 
	    mov si, offset filePath
        xor ax, ax
        mov al, filePathLength       
        add si, ax
	    dec si 
	    mov bl, byte ptr [si]
        mov byte ptr [si], 0
        mov byte ptr [si + 1], 0
        findFile 	
    	jc tryFindFile                      
    	                                        
    	printMessage excessCharsErrorMessage
        jmp exit
                  
    tryFindFile:
        mov byte ptr [si], bl
        findFile
        jnc isTxtFile 
        
        printMessage filePathErrorMessage
        jmp exit 
        
    isTxtFile:
        cmp bl, 't'
        je fileIsFound
        
        printMessage fileExtensionMessage
        jmp exit
            
    fileIsFound:         
        printMessage fileIsFoundMessage 
        ret
checkFilePath endp 
    
installer:                      
    call copyFilePath 
    call checkFilePath
    
    printMessage setHandlerMessage
    cli 
    mov ah, 35h
    mov al, 09h
    int 21h    
    mov word ptr [offset defaultINT9], bx
    mov word ptr [offset defaultINT9 + 2], es
    mov ah, 25h
    mov al, 09h 
    mov dx, offset handlerINT9
    int 21h        
    sti
    
    printMessage storeResPartMessage
    mov ah, 31h
    mov al, 00h
    mov dx, (endResidentPart - main + 100h) / 16 + 1
    int 21h 
    
    exit:
    mov ax, 4c00h
    int 21h
end main