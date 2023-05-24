;cmd    D:\emu8086\MyBuild\lw5.exe D:\emu8086\MySource\lw5\file.txt hac    

.model small
.stack 100h

.data           

    minCmdLengthErrorMessage      db  'Error. Cmd is not entered.', 13, 10, '$'
    oneArgumentInCmdErrorMessage  db  'Error. Cmd contains one argument.', 13, 10, '$'
    excessCharInCmdErrorMessage   db  'Error. Cmd contains excess characters.', 13, 10, '$'
    deletedWordLengthErrorMessage db  'Error. Big deleted word length.', 13, 10, '$'
    openFileErrorMessage          db  'Open file error.', 13, 10, '$'
    closeFileErrorMessage         db  'Close file error.', 13, 10, '$'
    movePointerErrorMessage       db  'Move pointer error.', 13, 10, '$'
    readErrorMessage              db  'Read word error.', 13, 10, '$'
    writeErrorMessage             db  'Write word error.', 13, 10, '$'
    
    initializeBegDataMessage      db  'Initialize beginning data.', 13, 10, '$'
    deleteWordMessage             db  'Delete word.', 13, 10, '$'
    openFileMessage               db  'Open file.', 13, 10, '$'
    closeFileMessage              db  'Close file.', 13, 10, '$'
    
    
    
    maxCmdLength        equ 126                                                       
    ;cmdLength           db  32 + 1 + 3
    ;cmd                 db  'D:\emu8086\MySource\lw5\file.txt hac';maxCmdLength dup(?)
    
    cmdLength           db  ?
    cmd                 db  maxCmdLength dup(?)
     
    filePath            db  maxCmdLength + 1 dup(?)    
    fileID              dw  ?
    
    deletedWordMaxLength    equ 50
    deletedWord         db  deletedWordMaxLength dup(?)   
    deletedWordLength   db  ?
    
    bufferWord          db  deletedWordMaxLength dup(?)
    bufferChar          db  ?   
    
    currentLoopIndex    dw  2 dup(0) 
    previousLoopIndex   dw  2 dup(0)
    wordBeginIndex      dw  2 dup(?)
    wordEndIndex        dw  2 dup(?)
    lastFileIndex       dw  2 dup(?)      
    
.code 
   
copyCmd macro           
	mov es, ax     
	
	xor cx, cx        
	mov si, 80h
	mov cl, ds:[si]
	dec cl
	mov es:cmdLength, cl
	add si, 2
	mov di, offset cmd
	rep movsb                      
    
    mov ds, ax    
endm   

printMessage macro string
    mov ah, 9
    lea dx, string 
    int 21h 
endm

initializeBeginningData proc
    printMessage initializeBegDataMessage
     
    checkMinCmdLength:
        cmp cmdLength, 0
        jg checkSpaceInCmd           
        printMessage minCmdLengthErrorMessage
        jmp exit 
             
    checkSpaceInCmd:
        mov al, ' '
        mov di, offset cmd
        xor cx, cx 
        mov cl, cmdLength                
        repne scasb
        
        cmp cx, 0
        jne fillFilePath         
        printMessage oneArgumentInCmdErrorMessage
        jmp exit
    
    fillFilePath:
        xor ax, ax 
        mov al, cmdLength
        inc cx
        sub ax, cx
        mov cx, ax 
        mov si, offset cmd
        mov di, offset filePath         
        rep movsb
        mov [di], 0
        
    checkExcessSpaceInCmd:
        inc si
        mov di, si 
        xor cx, cx 
        mov cl, cmdLength
        sub cx, ax
        mov bx, cx               
        mov al, ' '
        repne scasb
        
        cmp cx, 0
        je checkExcessTabInCmd
        printMessage excessCharInCmdErrorMessage
        jmp exit
        
    checkExcessTabInCmd:
        mov di, si 
        mov cx, bx               
        mov al, 9
        repne scasb
        
        cmp cx, 0
        je checkMaxDeletedWordLength
        printMessage excessCharInCmdErrorMessage
        jmp exit    
    
    checkMaxDeletedWordLength: 
        dec bx 
        cmp bx, deletedWordMaxLength
        jle fillDeletedWord
        printMessage deletedWordLengthErrorMessage
        jmp exit
        
    fillDeletedWord: 
        mov di, offset deletedWord                       
        mov cx, bx
        mov byte ptr deletedWordLength, bl
        rep movsb 
        
    ret    
initializeBeginningData endp

openFile proc
    printMessage openFileMessage
      
    mov ah, 3dh
    mov al, 01000011b   ;read and write mode
    mov cl, 00000000b
    mov dx, offset filePath
    int 21h 
    mov fileID, ax
    jnc openFileSuccessfully
    
    printMessage openFileErrorMessage
    jmp exit
    
    openFileSuccessfully:
    ret
openFile endp

closeFile proc
    printMessage closeFileMessage
      
    mov ah, 3eh
    mov es, ax 
    mov bx, fileID
    int 21h
    jnc closeFileSuccessfully
    
    printMessage closeFileErrorMessage 
    jmp exit
    
    closeFileSuccessfully:
    ret
closeFile endp

getLastFileIndex proc 
    mov ah, 42h  
    mov al, 2
    mov bx, fileID
    mov cx, 0ffffh
    mov dx, 0ffffh
    int 21h         
    jnc initializeFileLengthSuccessfully
    
    printMessage movePointerErrorMessage
    jmp finishMain
    
    initializeFileLengthSuccessfully: 
    mov [lastFileIndex], dx
    mov [lastFileIndex + 2], ax 
    ret
getLastFileIndex endp

readFile proc
    ;dx = offset buffer, cl = length
    mov ah, 3fh
    mov bx, fileID 
    xor ch, ch
    int 21h
    jnc checkCharsCountAfterReading
    
    printMessage readErrorMessage
    jmp finishMain
    
    checkCharsCountAfterReading:
    cmp ax, cx
    je readFileSuccessfully
    
    jmp finishMain
    
    readFileSuccessfully: 
    ret
readFile endp

writeFile proc
    ;dx = offset buffer, cl = length       
    mov ah, 40h
    mov bx, fileID
    xor ch, ch
    int 21h 
    jnc writeFileSuccessfully
    
    printMessage writeErrorMessage
    jmp finishMain
    
    writeFileSuccessfully: 
    ret
writeFile endp

compareCharWithSeparator proc 
    compareCharWithSpace:
        cmp bufferChar, 32
        jne compareCharWithTab
        ret             
    compareCharWithTab:
        cmp bufferChar, 9
        jne compareCharWithCret
        ret        
    compareCharWithCret:
        cmp bufferChar, 13
        jne compareCharWithNewl
        ret       
    compareCharWithNewl:
        cmp bufferChar, 10
        ret
compareCharWithSeparator endp    

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
    jmp finishMain
    
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
    jmp finishMain
    
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

incIndex proc      
        cmp [si + 2], 0ffffh
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
   
compareIndexes proc
    compsreBigParts:    
        mov ax, [si]
        cmp ax, [di]
        je compsreSmallParts
        ret
    compsreSmallParts:
        mov ax, [si + 2]
        cmp ax, [di + 2]    
        ret      
compareIndexes endp
 
 
 
main: 
    mov ax, @data
    copyCmd                                                      
    call initializeBeginningData
    
    call openFile
    call getLastFileIndex    
    mov ah, 0    
    mov al, 0
    call movePointer 
    
    fileMainLoop: 
        saveMainLoopIndex:
            mov si, offset currentLoopIndex
            call getPointer
            
        saveWordBeginIndex:
            mov si, offset wordBeginIndex
            call getPointer    
            
        readWordAndCompare:
            mov cl, deletedWordLength
            mov dx, offset bufferWord 
            call readFile
            mov si, offset deletedWord 
            mov di, offset bufferWord
            xor cx, cx 
            mov cl, deletedWordLength
            repe cmpsb 
            jne nextIteration 
            
        saveWordEndIndex:
            mov si, offset wordEndIndex
            call getPointer
                           
        checkEndOfFile:
            mov si, offset lastFileIndex
            call incIndex
            mov si, offset wordEndIndex 
            mov di, offset lastFileIndex
            call compareIndexes
            call getLastFileIndex
            je checkBeginOfFile
            
        checkRightChar:
            mov si, offset wordEndIndex
            call setPointer 
            mov cl, 1
            mov dx, offset bufferChar 
            call readFile          
            call compareCharWithSeparator    
            jne nextIteration
        
        checkBeginOfFile:
            mov si, offset currentLoopIndex 
            mov di, offset previousLoopIndex
            call compareIndexes  
            je deleteWord  
                        
        checkLeftChar:        
            mov si, offset previousLoopIndex
            call setPointer
            mov cl, 1
            mov dx, offset bufferChar 
            call readFile
            call compareCharWithSeparator    
            jne nextIteration 
            
        deleteWord:     
            printMessage deleteWordMessage
             
            mov si, offset lastFileIndex
            call incIndex
            mov si, offset wordEndIndex 
            mov di, offset lastFileIndex
            call compareIndexes
            call getLastFileIndex
            jne deleteWordLoop 
            
            mov si, offset wordBeginIndex
            call setPointer
            mov cl, 0 
            call writeFile
            jmp finishMain  

            deleteWordLoop: 
                mov si, offset wordEndIndex
                call setPointer             
                mov cl, 1
                mov dx, offset bufferChar 
                call readFile   
                
                mov si, offset wordBeginIndex
                call setPointer                  
                mov cl, 1
                mov dx, offset bufferChar 
                call writeFile  
                
                mov si, offset wordEndIndex 
                mov di, offset lastFileIndex
                call compareIndexes
                
                je cutFile          
                mov si, offset wordBeginIndex
                call incIndex         
                mov si, offset wordEndIndex
                call incIndex
            jmp deleteWordLoop
            
            cutFile:
                mov cl, 0 
                call writeFile   
                call getLastFileIndex
                            
        nextIteration:                    
            mov si, offset currentLoopIndex
            call setPointer      
            savePreviousIndex:
                mov si, offset previousLoopIndex
                call getPointer           
            mov ah, 1    
            mov al, 1
            call movePointer

    jmp fileMainLoop
                             
    finishMain:
        call closeFile
        exit:                  
        mov ax, 4c00h
        int 21h
end main