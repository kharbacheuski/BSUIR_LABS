.model small
.stack 100h 
.data           

epb     dw 0
        dw 0080h,0
		dw 005Ch,0,006Ch,0
            
cmdMaxLength        equ 126     
filePath            db  cmdMaxLength + 1 dup(0)  
filePathLength      db  ?  
fileID              dw  ?
fileEnd             db  0   
  
programPathLength   db  0
programPath         db  cmdMaxLength + 1 dup(0)
bufferChar          db  ?   
stringBeginIndex    dw  2 dup(0)

changeMemoryErrorMessage      db  'Change memory error.', 13, 10, '$'  
emptyCmdErrorMessage          db  'Error. Cmd is empty.', 13, 10, '$'
openFileErrorMessage          db  'Error.', 13, 10, '$'
closeFileErrorMessage         db  'Error.', 13, 10, '$'
movePointerErrorMessage       db  'Move pointer error.', 13, 10, '$'
readErrorMessage              db  'Read error.', 13, 10, '$'
runProgramErrorMessage        db  'Error.', 13, 10, '$'
                             
openFileMessage               db  'Open file.', 13, 10, '$'
closeFileMessage              db  13, 10, 'Close file.', 13, 10, '$'
runProgramMessage             db  13, 10, 'Run program: ', '$'
runProgramSuccessMessage      db  13, 10, 'Success.', 13, 10, '$'
newLine                       db  13, 10, '$'
                     
dataSize = $ - epb
      
.code 

printMessage macro string
    mov ah, 9
    lea dx, string 
    int 21h 
endm     
            
main:
    call changeMemoryBlock 
    mov ax, @data                 
	call copyFilePath
    call openFile 
    
    runProgramsLoop: 
    
        checkSeparator:
        
        mov cl, 1
        mov dx, offset bufferChar 
        call readFile  
        checkEOF:
            cmp ax, 0
            jne checkEnter  
            cmp fileEnd, 1
            je finishMain
                mov fileEnd, 1
                jmp readProgramPath
            finishMain:
                jmp endMain
        checkEnter:   
            cmp bufferChar, 13
            je readProgramPath
            mov al, programPathLength
            inc al
            mov programPathLength, al
    jmp runProgramsLoop
    
        readProgramPath:
        
        mov si, offset stringBeginIndex
        call setPointer 
        mov cl, programPathLength
        mov dx, offset programPath 
        call readFile            
        call runProgram
        mov ah, 2    
        mov al, 1
        call movePointer
        mov si, offset stringBeginIndex
        call getPointer 
        mov byte ptr programPathLength, 0
    jmp runProgramsLoop
            
    
    endMain:
        call closeFile
        exit:                  
        mov ax, 4c00h
        int 21h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    


changeMemoryBlock proc
    mov ah, 4Ah
	mov bx, (codeSize/16+1)+(dataSize/16+1)+(100h/16)+(100h/16)
	int 21h
	jnc changeMemorySuccessfully    
    printMessage changeMemoryErrorMessage 
    jmp exit
    
    changeMemorySuccessfully:
    ret
changeMemoryBlock endp 

copyFilePath proc           
	mov es, ax     
	
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
    
    mov ds, ax    
    ret
copyFilePath endp 

openFileFunction macro
    mov ah, 3dh
    mov al, 00000010b   ;read mode
    mov cl, 00000000b
    mov dx, offset filePath
    int 21h
endm    

openFile proc
    printMessage openFileMessage
    
    openFileFirstChecking:  
        openFileFunction 
        mov fileID, ax
        jnc checkExcessCharInFilePath 
        printMessage openFileErrorMessage
        jmp exit
                 
    checkExcessCharInFilePath: 
        mov si, offset filePath
        xor ax, ax
        mov al, filePathLength 
        add si, ax
        dec si
        mov byte ptr [si], 0             
        openFileFunction
        jc openFileSuccessfully        
        printMessage openFileErrorMessage
        jmp exit    
    
    openFileSuccessfully:
    ret
openFile endp

closeFile proc
    printMessage closeFileMessage
      
    mov ah, 3eh
    mov bx, fileID
    int 21h
    jnc closeFileSuccessfully    
    printMessage closeFileErrorMessage 
    jmp exit
    
    closeFileSuccessfully:
    ret
closeFile endp

movePointer proc 
    ;ah = shift, al = beg position
    mov bx, fileID
    xor cx, cx
    xor dx, dx
    mov dl, ah
    mov ah, 42h
    int 21h        
    jnc movePointerSuccessfully          
        
    printMessage movePointerErrorMessage
    jmp endMain
    
    movePointerSuccessfully: 
    ret
movePointer endp

setPointer proc 
    ;si = offset shift  
    mov ah, 42h  
    mov al, 0
    mov bx, fileID
    mov cx, [si]
    mov dx, [si + 2]
    int 21h        
    jnc setPointerSuccessfully          
        
    printMessage movePointerErrorMessage
    jmp endMain
    
    setPointerSuccessfully: 
    ret
setPointer endp

getPointer proc 
    mov ah, 0    
    mov al, 1
    call movePointer
    mov [si], dx
    mov [si + 2], ax 
    ret
getPointer endp

readFile proc
    ;dx = offset buffer, cl = length
    mov ah, 3fh
    mov bx, fileID 
    xor ch, ch
    int 21h
    jnc readFileSuccessfully
    
    printMessage readErrorMessage
    jmp endMain
        
    readFileSuccessfully: 
    ret
readFile endp

runProgram proc
    printRunProgramMessage:
        printMessage runProgramMessage
        mov si, offset programPath
        xor ax, ax
        mov al, programPathLength       
        add si, ax
        mov byte ptr [si], '$' 
        printMessage programPath
        printMessage newLine
        mov byte ptr [si], 0  
    
    checkExcessCharInProgramPath:  
        cmp programPathLength, 0
        je runProgramNotSuccessfully
        dec si                          
        mov bl, byte ptr [si]
        mov byte ptr [si], 0
        mov ah, 4eh
    	mov cx, 0			
    	mov dx, offset programPath
    	int 21h 	
    	jc tryRunProgram
        jmp runProgramNotSuccessfully
        
    
    tryRunProgram:
        mov byte ptr [si], bl
    	mov ah, 4bh
    	mov al, 0				
    	mov bx, offset epb
    	mov dx, offset programPath
    	int 21h
    	jnc runProgramSuccessfully
        
    runProgramNotSuccessfully:
        printMessage runProgramErrorMessage 
        jmp clearProgramPath
                                  
    runProgramSuccessfully:
        printMessage runProgramSuccessMessage
    
    clearProgramPath:  
        mov ah, 7
        int 21h     
        mov al, 0
        mov di, offset programPath
        xor cx, cx
        mov cl, programPathLength
        rep stosb
        ret
runProgram endp

codeSize = $ - main

end main