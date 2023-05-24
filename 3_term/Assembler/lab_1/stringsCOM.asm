; strings COM
    
.model tiny
.code
org 100h;
start:  mov ah, 9;

        mov dx, offset stringOne;
        int 21h;  
        
        mov dx, offset stringTwo;
        int 21h;
        
        mov dx, offset stringThree;
        int 21h;       
        
        ret;
        
        stringOne db 'Smells Like$';   
        stringTwo db 10, 13, 'Teen Spirit$';
        stringThree db 10, 13, 'Nirvana - (Grunge)$';   
end start;