.model small
.stack 100h

.data
    windiwSizeX     equ 40
    windiwSizeY     equ 25
     
    fieldSize           equ 21
    fieldOffsetX        equ 2
    fieldOffsetY        equ 2 
    fieldOffsetInMemory equ 2 * 2 * (fieldOffsetY * windiwSizeX + fieldOffsetX)
    
    w equ 1121h;0001000100100001b ;blue space on blue     
    g equ 0021h;0000000000100001b ;black space on black
    
    ;wallBlock   dw 2 dup(w)
    groundBlock dw 2 dup(g)
    
    gameField   dw fieldSize dup(w)
                dw w,g,g,g,g,g,g,g,g,g,g,g,w,g,g,g,g,g,g,g,w
                dw w,g,w,g,w,w,w,g,w,w,w,g,w,g,w,w,w,g,w,g,w
                dw w,g,w,g,g,g,g,g,w,g,g,g,g,g,g,g,w,g,g,g,w
                dw w,g,w,g,w,g,w,w,w,g,w,w,w,g,w,g,w,g,w,w,w
                dw w,g,g,g,w,g,g,g,g,g,w,g,g,g,g,g,w,g,g,g,w
                dw w,w,w,g,w,g,w,g,w,g,w,g,w,w,w,g,w,w,w,g,w
                dw w,g,g,g,g,g,w,g,w,g,g,g,g,g,g,g,g,g,g,g,w
                dw w,g,w,g,w,w,w,g,w,g,w,g,w,w,w,w,w,g,w,g,w
                dw w,g,w,g,g,g,w,g,g,g,w,g,w,g,g,g,g,g,w,g,w
                dw w,g,w,w,w,g,w,g,w,w,w,g,w,g,w,g,w,g,w,g,w
                dw w,g,g,g,g,g,g,g,g,g,g,g,g,g,w,g,g,g,w,g,w
                dw w,g,w,g,w,w,w,g,w,g,w,w,w,g,w,w,w,g,w,g,w
                dw w,g,g,g,g,g,g,g,w,g,g,g,w,g,g,g,w,g,g,g,w
                dw w,w,w,g,w,g,w,g,w,g,w,g,w,g,w,g,w,w,w,w,w
                dw w,g,g,g,w,g,w,g,g,g,g,g,w,g,w,g,g,g,g,g,w
                dw w,g,w,g,w,g,w,w,w,g,w,g,w,g,w,w,w,g,w,g,w
                dw w,g,g,g,w,g,w,g,g,g,w,g,g,g,g,g,g,g,w,g,w
                dw w,g,w,w,w,g,w,g,w,g,w,g,w,w,w,g,w,g,w,g,w
                dw w,g,g,g,g,g,g,g,w,g,g,g,g,g,g,g,w,g,g,g,w
                dw fieldSize dup (w)
    
    scoreOffsetX                    equ 31
    scoreOffsetY                    equ 8
    scoreOffsetInMemory             equ 2 * 2 * (scoreOffsetY * windiwSizeX + scoreOffsetX)
    
    scoreMessage                    db  'Score:    '
    scoreMessageOffsetX             equ 30
    scoreMessageOffsetY             equ 6
    scoreMessageOffsetInMemory      equ 2 * 2 * (scoreMessageOffsetY * windiwSizeX + scoreMessageOffsetX)
    
    gameOverMessage                 db  'Game over!'
    gameOverMessageOffsetX          equ 29
    gameOverMessageOffsetY          equ 12
    gameOverMessageOffsetInMemory   equ 2 * 2 * (gameOverMessageOffsetY * windiwSizeX + gameOverMessageOffsetX)
   
    random              db  010010111b
    entropySourceWeak   db  ?
    entropySourceStrong db  ?   
    
    gameLoopBigPause    equ 1 ; *62.5ms (16 = 1s)
;   +
    gameLoopSmallPause  equ 0 ; (<16)*3.9ms (16 = 62.5ms)
    
    ghostsCount         equ 4 
    ghostsMaxDelay      equ 3
    ghostsDelayCounter  db  ?
    ghostsX             db  ghostsCount dup(?) 
    ghostsY             db  ghostsCount dup(?)
    ghostsDirection     db  ghostsCount dup(?)
    ghostsColor         db  ghostsCount dup(?)
    ghostBlue           dw  0000100111011110b, 0000100111011101b
    ghostGreen          dw  0000101011011110b, 0000101011011101b
    ghostPurple         dw  0000110111011110b, 0000110111011101b
    ghostGray           dw  0000011111011110b, 0000011111011101b
    
    packmanMaxDelay         equ 3
    packmanDelayCounter     db  ?
    packmanX                db  ?
    packmanY                db  ?
    packmanDirection        db  ?
    packmanNextDirection    db  ?
    packmanUp               dw  0000111001011100b, 0000111000101111b ; yellow "\/"  on black 
    packmanDown             dw  0000111000101111b, 0000111001011100b ; yellow "/\"  on black 
    packmanLeft             dw  0000111000111110b, 0000111000101101b ; yellow ">-"  on black 
    packmanRight            dw  0000111000101101b, 0000111000111100b ; yellow "-<"  on black 
    
    appleCount              db  0
    appleX                  db  ?
    appleY                  db  ?
    apple                   dw  0000110000101000b, 0000110000101001b ; red "()"  on black 
    appleCountString        dw  4 dup(?) 
    
.code 

;;;;;;;;;;;;;;;;;;;;;;;     field
                
drawField proc
    push si
    push di
    push ax
    push cx
    
    mov si, offset gameField 
    mov di, fieldOffsetInMemory
              
    mov cx, fieldSize  
    drawFieldLoopOnStrings:
        push cx
        mov cx, fieldSize
        drawFieldLoopOnColumns:
            push cx
            
            mov ax, ds:[si]
            mov cx, 2
            drawFieldCellLoop:
                mov word ptr es:[di], ax
                add di, 2
            loop drawFieldCellLoop
            add si, 2
            
            pop cx
        loop drawFieldLoopOnColumns
        add di, 2 * 2 * (windiwSizeX - fieldSize)
        pop cx
    loop drawFieldLoopOnStrings
    
    pop cx
    pop ax
    pop di
    pop si
    ret
drawField endp
              
              
              
;;;;;;;;;;;;;;;;;;;;;;;     messages

drawMessage proc
    mov cx, 10 
    drawMessageLoop:
        mov ah, 00001111b
        mov al, [si]
        mov word ptr es:[di], ax
        inc si
        add di, 2
    loop drawMessageLoop
    ret
drawMessage endp

drawScoreMessage proc
    mov si, offset scoreMessage
    mov di, scoreMessageOffsetInMemory
    call drawMessage
    ret
drawScoreMessage endp

drawGameOverScoreMessage proc
    mov si, offset gameOverMessage
    mov di, gameOverMessageOffsetInMemory
    call drawMessage
    ret
drawGameOverScoreMessage endp
                     
                     



;;;;;;;;;;;;;;;;;;;;;;;     macroses with interrupt

clearScreen macro
    push ax
    mov ax, 0003h
    int 10h
    pop ax
endm

sleep macro
    push ax 
    push cx
    push dx 
    
    mov ah, 86h
    mov cx, gameLoopBigPause * 0001h
    mov dx, gameLoopSmallPause * 1000h 
    int 15h
    
    pop dx
    pop cx
    pop ax
endm      

isKeyPressed macro
    push ax
    mov ah, 01h
    int 16h       
    pop ax
endm  

getKey macro
    mov ah, 00h
    int 16h  ; al = ASCII-code
endm

clearKeyboardBuffer macro
    push ax
    mov ax,0c00h
    int 21h       
    pop ax
endm 
      
      
      
      
;;;;;;;;;;;;;;;;;;;;;;;;;;;;        random

updateEntropy macro
    push dx
    push cx
    
    mov ah, 2ch
    int 21h
    mov entropySourceWeak, dh
    mov entropySourceStrong, dl
    
    pop cx
    pop dx
endm    

updateRandomParameter macro number shift1 multiplier summand shift2
    push ax
    
    mov al, number      ;number
    ror al, shift1      ;shift1(number)
    mov ah, multiplier
    mul ah              ;shift1(number) * multiplier
    add al, summand     ;shift1(number) * multiplier + summand
    ror al, shift2      ;shift2(shift1(number) * multiplier + summand)    
    mov number, al
    
    pop ax      
endm

updateRandom macro
    updateRandomParameter random               2   23  11  5
    updateRandomParameter entropySourceWeak    1   7   4   3 
    updateRandomParameter entropySourceStrong  7   5   8   4
    
    updateRandomParameter random               6   entropySourceWeak  entropySourceStrong  1
endm 

getRandomNumber macro limit
    push bx
    push dx
    
    updateRandom
    xor ax, ax
    mov al, random
    xor bx, bx
    mov bl, limit
    cwd
    div bx
    mov ax, dx
    ;al = random number 
    
    pop dx 
    pop bx  
endm    




;;;;;;;;;;;;;;;;;;;;;;;     common logic

calculateObjectOffsetRelativeToField macro sizeX
    xor bx, bx
    mov bl, ah
    mov ah, 0h
    mov dx, sizeX
    mul dx  
    add ax, bx
    mov dx, 2 * 2
    mul dx
    ;ax = offset
endm

drawObject macro object
    ;ah = x, al = y    
    push si
    push di
    push cx
    push bx
    push dx
    
    calculateObjectOffsetRelativeToField windiwSizeX
    mov si, offset object
    mov di, fieldOffsetInMemory     
    add di, ax
    mov cx, 2                
    rep movsw
    
    pop dx
    pop bx
    pop cx
    pop di
    pop si
endm

getObject macro
    ;ah = x, al = y    
    push si
    push bx
    push dx
    
    calculateObjectOffsetRelativeToField fieldSize
    mov bx, 2
    div bx     
    mov si, offset gameField
    add si, ax
    mov ax, [si]
    
    pop dx
    pop bx
    pop si
endm

getObjectOnDirection proc
    cmp bl, 0
    je checkObjectUp
    cmp bl, 1
    je checkObjectDown
    cmp bl, 2
    je checkObjectLeft
    cmp bl, 3
    je checkObjectRight             
    
    checkObjectUp:
        dec al
        jmp getNeighborObject
    checkObjectDown:           
        inc al
        jmp getNeighborObject
    checkObjectLeft:          
        dec ah
        jmp getNeighborObject
    checkObjectRight:           
        inc ah
        jmp getNeighborObject
        
    getNeighborObject: 
        getObject
        ret
getObjectOnDirection endp

checkMeetingPackmanAndGhost proc
    push si
    push cx
    push ax
    
    mov cx, ghostsCount
    mov si, 0
    checkMeetingPackmanAndGhostLoop:
        mov ah, ghostsX[si] 
        mov al, ghostsY[si]
        
        checkMeetingPackmanAndGhostOnX:
            cmp ah, packmanX
            je checkMeetingPackmanAndGhostOnY
            jmp checkNextMeetingPackmanAndGhost 
        checkMeetingPackmanAndGhostOnY:
            cmp al, packmanY
            je endGame
            jmp checkNextMeetingPackmanAndGhost
            
        checkNextMeetingPackmanAndGhost:    
            inc si
    loop checkMeetingPackmanAndGhostLoop
        
    pop ax
    pop cx
    pop si
    ret
checkMeetingPackmanAndGhost endp

checkMeetingPackmanAndApple proc
    push ax                     
    
    checkMeetingPackmanAndAppleOnX:
        mov ah, appleX
        mov al, packmanX
        cmp ah, al
        je checkMeetingPackmanAndAppleOnY
        jmp endCheckMeetingPackmanAndApple 
    checkMeetingPackmanAndAppleOnY:
        mov ah, appleY
        mov al, packmanY
        cmp ah, al
        je incAppleCount
        jmp endCheckMeetingPackmanAndApple
        
    incAppleCount:
        inc appleCount
        call createApple
        
    endCheckMeetingPackmanAndApple:
        pop ax    
        ret
checkMeetingPackmanAndApple endp

checkMeetingGhostAndApple proc
    push ax                     
    
    checkMeetingGhostAndAppleX:
        mov ah, appleX
        mov al, ghostsX[si]
        cmp ah, al
        je checkMeetingGhostAndAppleOnY
        jmp endCheckMeetingGhostAndApple 
    checkMeetingGhostAndAppleOnY:
        mov ah, appleY
        mov al, ghostsY[si]
        cmp ah, al
        je redrawApple
        jmp endCheckMeetingGhostAndApple
        
    redrawApple:
        call drawApple
        
    endCheckMeetingGhostAndApple:
        pop ax    
        ret
checkMeetingGhostAndApple endp  





 
;;;;;;;;;;;;;;;;;;;;;;     packman logic

createPackman proc
    mov packmanDelayCounter, 0
    mov packmanX, 1
    mov packmanY, 1
    mov packmanDirection, 2
    mov packmanNextDirection, 2
    call drawPackman
    ret
createPackman endp

checkKeystroke proc
    isKeyPressed
        jnz keyWasPressed
    
        ;false
        ret
        
    keyWasPressed:
    
        ;true 
        getKey  ; al = ASCII-code    
        clearKeyboardBuffer 
    
        cmp al, 'w'
        je changePackmanNextDirectionOnUp
        cmp al, 's'
        je changePackmanNextDirectionOnDown
        cmp al, 'a'
        je changePackmanNextDirectionOnLeft
        cmp al, 'd'
        je changePackmanNextDirectionOnRight
            
            ;wrong key
            ret
        
        changePackmanNextDirectionOnUp:
            mov packmanNextDirection, 0
            ret
        changePackmanNextDirectionOnDown:
            mov packmanNextDirection, 1
            ret
        changePackmanNextDirectionOnLeft: 
            mov packmanNextDirection, 2
            ret
        changePackmanNextDirectionOnRight:  
            mov packmanNextDirection, 3
            ret
checkKeystroke endp

erasePackman proc
    mov ah, packmanX 
    mov al, packmanY
    drawObject groundBlock
    ret
erasePackman endp
 
changePackmanCoordinate proc
    cmp packmanDirection, 0
    je movePackmanUp
    cmp packmanDirection, 1
    je movePackmanDown
    cmp packmanDirection, 2
    je movePackmanLeft
    cmp packmanDirection, 3
    je movePackmanRight             
    
    movePackmanUp:          
        dec packmanY
        ret
    movePackmanDown:           
        inc packmanY
        ret
    movePackmanLeft:          
        dec packmanX
        ret
    movePackmanRight:           
        inc packmanX
        ret
changePackmanCoordinate endp 

drawPackman proc       
    mov ah, packmanX 
    mov al, packmanY
    
    cmp packmanDirection, 0
    je drawPackmanUp
    cmp packmanDirection, 1
    je drawPackmanDown
    cmp packmanDirection, 2
    je drawPackmanLeft
    cmp packmanDirection, 3
    je drawPackmanRight    
    
    drawPackmanUp:
        drawObject packmanUp
        jmp endDrawPackman
    drawPackmanDown:     
        drawObject packmanDown
        jmp endDrawPackman
    drawPackmanLeft:     
        drawObject packmanLeft
        jmp endDrawPackman
    drawPackmanRight:     
        drawObject packmanRight
        jmp endDrawPackman
    
    endDrawPackman:
        ret
drawPackman endp
 
movePackman proc
    push ax
    push bx
    
    call checkKeystroke
        
    checkPackmanDelayCounter:
        inc packmanDelayCounter
        cmp packmanDelayCounter, packmanMaxDelay
        jne endMovePackman
        
        ;it's max delay
        mov packmanDelayCounter, 0
                
    checkNextDirection:
        mov ah, packmanX 
        mov al, packmanY
        mov bl, packmanNextDirection        
        call getObjectOnDirection
        cmp ax, g
        je setPackmanDirectionOnNext
        cmp ax, w
        je checkCurrentDirection
       
    checkCurrentDirection:
        mov ah, packmanX 
        mov al, packmanY
        mov bl, packmanDirection        
        call getObjectOnDirection
        cmp ax, g
        je redrawPackman
        cmp ax, w
        je endMovePackman    
    
    
    setPackmanDirectionOnNext:
        mov ah, packmanNextDirection     
        mov packmanDirection, ah
                
    redrawPackman:    
        call erasePackman 
        call changePackmanCoordinate
        call checkMeetingPackmanAndGhost
        call checkMeetingPackmanAndApple
        call drawPackman
        
    endMovePackman:     
        pop bx 
        pop ax  
        ret
movePackman endp
 
 

;;;;;;;;;;;;;;;;;;;;;;;     ghosts logic
           
createGhosts proc
    updateEntropy
    
    mov cx, ghostsCount
    mov si, 0
    createGhostsLoop:
        createGhost:
            getRandomNumber fieldSize
            mov ghostsX[si], al 
            getRandomNumber fieldSize
            mov ghostsY[si], al 
            getRandomNumber 4
            mov ghostsDirection[si], al
            getRandomNumber 4
            mov ghostsColor[si], al
            mov ah, ghostsX[si]
            mov al, ghostsY[si]
            getObject
            cmp ax, g
            je createNextGhosts
            cmp ax, w
            je createGhost
                 
        createNextGhosts:
            call drawGhost
            inc si
    loop createGhostsLoop    
    
    mov ghostsDelayCounter, 0
    
    ret
createGhosts endp

eraseGhost proc
    mov ah, ghostsX[si] 
    mov al, ghostsY[si]
    drawObject groundBlock
    ret
eraseGhost endp
 
changeGhostCoordinate proc
    cmp bl, 0
    je moveGhostUp
    cmp bl, 1
    je moveGhostDown
    cmp bl, 2
    je moveGhostLeft
    cmp bl, 3
    je moveGhostRight             
    
    moveGhostUp:         
        dec ghostsY[si]
        ret
    moveGhostDown:           
        inc ghostsY[si]
        ret
    moveGhostLeft:          
        dec ghostsX[si]
        ret
    moveGhostRight:           
        inc ghostsX[si]
        ret
changeGhostCoordinate endp
     
drawGhost proc
    mov ah, ghostsX[si] 
    mov al, ghostsY[si]
    
    mov bl, ghostsColor[si] 
    cmp bl, 0
    je drawGhostBlue
    cmp bl, 1
    je drawGhostGreen
    cmp bl, 2
    je drawGhostPurple
    cmp bl, 3
    je drawGhostGray 
    
    drawGhostBlue:
        drawObject ghostBlue
        jmp endDrawGhost
    drawGhostGreen:     
        drawObject ghostGreen
        jmp endDrawGhost
    drawGhostPurple:     
        drawObject ghostPurple
        jmp endDrawGhost
    drawGhostGray:     
        drawObject ghostGray
        jmp endDrawGhost
    
    endDrawGhost:
        ret
drawGhost endp         

getOppositeDirection proc
    cmp bl, 2
    jge OppositeOfLeftOrRight
    jmp OppositeOfUpOrDown
    
    OppositeOfLeftOrRight:
        cmp bl, 2
        je OppositeOfLeft
        jmp OppositeOfRight
    OppositeOfUpOrDown:
        cmp bl, 1
        je OppositeOfDown
        jmp OppositeOfUp
    
    OppositeOfUp:
        mov bl, 1
        ret 
    OppositeOfDown:
        mov bl, 0
        ret
    OppositeOfLeft:
        mov bl, 3
        ret
    OppositeOfRight:
        mov bl, 2        
        ret
getOppositeDirection endp

moveGhosts proc
    push ax
    push bx
    push cx
                  
    checkGhostsDelayCounter:
        inc ghostsDelayCounter
        cmp ghostsDelayCounter, ghostsMaxDelay
        jne endMoveGhosts
        
        ;it's max delay
        mov ghostsDelayCounter, 0
        updateEntropy
            
    mov cx, ghostsCount
    mov si, 0
    moveGhostsLoop: 
        checkRandomDirection:
            getRandomNumber 4
            mov bl, al
            mov ah, ghostsX[si] 
            mov al, ghostsY[si]
            call getObjectOnDirection
            cmp ax, g
            je checkPreviousDirection
            cmp ax, w
            je checkRandomDirection
        
        checkPreviousDirection: 
            call getOppositeDirection
            mov bh, ghostsDirection[si]
            cmp bh, bl
            je checkRandomDirection 
            
        setGhostDirectionOnNext:
            call getOppositeDirection
            mov ghostsDirection[si], bl
            
        redrawGhost:    
            call eraseGhost                  
            call checkMeetingGhostAndApple
            call changeGhostCoordinate
            call checkMeetingPackmanAndGhost             
            call drawGhost
            
        inc si
    loop moveGhostsLoop
    
    endMoveGhosts:     
        pop cx 
        pop bx
        pop ax  
        ret
moveGhosts endp




;;;;;;;;;;;;;;;;;;;;;;;     apple
            
numberToString proc
    push bp
    mov bp, sp 
                  
    mov ax, [bp + 6]
    mov si, [bp + 4]
    xor cx, cx
    mov bx, 10
        
    pushDigits:
        xor dx, dx
        div bx
        push dx    
        inc cx
        cmp ax, 0
    jne pushDigits
        
    loopFillStr:
        pop dx
        add dx, 30h
        mov dh, 00001111b   
        mov word ptr [si], dx
        add si, 2
    loop loopFillStr

    pop bp
    ret 4
numberToString endp

drawAppleCount proc
    xor cx, cx
    mov cl, appleCount
    push cx
    push offset appleCountString   
    call numberToString

    mov si, offset appleCountString
    mov di, scoreOffsetInMemory
    mov cx, 4                
    rep movsw
    ret
drawAppleCount endp

drawApple proc
    mov ah, appleX 
    mov al, appleY
    drawObject apple
    ret
drawApple endp

createApple proc
    updateEntropy
         
    setAppleCoordinates:
        getRandomNumber fieldSize
        mov appleX, al 
        getRandomNumber fieldSize
        mov appleY, al 
        mov ah, appleX 
        mov al, appleY
        getObject
        cmp ax, g
        je drawAppleAndAppleCount
        cmp ax, w
        je setAppleCoordinates
    
    drawAppleAndAppleCount:
        call drawApple
        call drawAppleCount
        ret
createApple endp
                    
                    
                    
;;;;;;;;;;;;;;;;;;;;;;;     start

start:
    mov ax, @data
    mov ds, ax
    mov ax, 0B800h
    mov es, ax      
                             
    clearScreen   
    call drawField  
    call drawScoreMessage
    call createPackman    
    call createGhosts
    call createApple    
    
    gameLoop:
        sleep
        call movePackman
        call moveGhosts
    jmp gameLoop    
    
    endGame:
        call drawGameOverScoreMessage
        mov ax, 4c00h
        int 21h
end start