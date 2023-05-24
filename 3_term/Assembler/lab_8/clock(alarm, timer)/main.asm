.model small
.8086
.8087
.386
.387

include	/8086/data.asm
include	/8086/util.asm
include	/8086/math.asm
include	/8086/d_clock.asm

;tone is a macro that will accept the frequency and send to horn to produce different sound
tone macro number
	mov bx,number			;This macro receives the tone
	call horn				;and send to call the procedures
endm

.stack 64

.code

check_one_sec_ana proc 
	cmp temp_sec_ana,60
	jne no_reset_sec_ana
	mov temp_sec_ana,0
	no_reset_sec_ana:

	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,dh
	call bcd2dec
	mov dh,dl
		cmp dh,temp_sec_ana
		jne not_yet_sec_ana
		mov is_sec_pass_ana,1b
		inc temp_sec_ana
			
	not_yet_sec_ana:	
	ret
check_one_sec_ana endp	

;in al out ax
inner_hr proc
	mov dl,12				;60/12 = 5 ;5 gaps
	mov ah,0				;meaning update the hour hand every 12 minutes 
	div dl
	mov ah,0	
	mov dl,6				;6deg rep 12 minutes
	mul dl
	mov cx,ax
	ret 
inner_hr endp

get_analog_time proc
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,dh
	call bcd2dec
	mov analog_ss,dl
	
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec	
	mov dl,cl
	call bcd2dec
	mov analog_mm,dl
	
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec	
	mov dl,ch
	call bcd2dec
	
	cmp dl,12
	jl hr_12_format
	sub dl,12
hr_12_format:		
	
	mov analog_hh,dl

	call check_one_sec_ana
	cmp is_sec_pass_ana,1b
	jne end_get_time
	mov is_sec_pass_ana,0b

;display the current second

	mov eax,6				;second gap or step
	mul analog_ss
	add eax,90				;adjust start from 90deg
	
	mov theta,eax
	mov sec_hand_color,11	
	call sec_hand	
	
;remove the previous second

	mov eax,6
	mul analog_ss
	add eax,90				;adjust to start from 90++deg

	sub eax,6
	
	mov theta,eax	
	
	mov sec_hand_color,0	
	call sec_hand	
	
;display the current minute
	mov cl,analog_mm
	mov dh,analog_ss
	
;show_min_hand:
	mov eax,6				;minute gap or step
	mul cl
	add eax,90				;adjust start from 90deg
	
	mov theta,eax
	mov min_hand_color,10
	call min_hand
	
;remove the previous minute	
	mov cl,analog_mm
	
	sub cl,1
	cmp cl,analog_ss
	jne reset_color_0
	mov min_hand_color,11
	jmp reset_min_hand

reset_color_0:
	mov min_hand_color,0	
	
reset_min_hand:
	add cl,1
	
	mov eax,6				;minute gap or step
	mul cl
	add eax,90				;adjust start from 90deg
	
	sub eax,6
	
	mov theta,eax	
	call min_hand
	
;display the current hour

;show_hour_hand:

	mov eax,0
	mov al,analog_mm
	call inner_hr
	mov inner_analog_hh,cx
	
	mov eax,30				;hour gap or step
	mul analog_hh
	add eax,90				;adjust start from 90deg
	add eax,ecx	
	
	mov theta,eax
	mov hour_hand_color,15
	call hour_hand
	
;remove the previous hour	 
	mov eax,0
	mov al,analog_mm
	mov dl,12				;60/12 = 5 ;5 gaps
	mov ah,0				;meaning update the hour hand every 12 minutes 
	div dl
	mov bx,ax
	
	;convert hour in (0-59) format for comparison
	mov ax,0
	mov dl,5				
	mov al,analog_hh
	mul dl
	add ax,bx
	mov cx,ax
	mov hour_in_60,cx
	
	sub cl,1
	cmp cl,analog_ss
	jne chk_hour_color
	mov hour_hand_color,11		;is second hand after chg hour hand
	jmp reset_hour_hand	
chk_hour_color:	
	mov cx,hour_in_60
	
	sub cl,1
	cmp cl,analog_mm
	jne reset_color_1	
	mov hour_hand_color,10		;is minute hand after chg hour hand
	jmp reset_hour_hand

reset_color_1:
	mov hour_hand_color,0	
	
reset_hour_hand:
	mov eax,30				;hour gap or step
	mul analog_hh
	add eax,90				;adjust start from 90deg

	mov cx,inner_analog_hh
	cmp cx,0
	je inner_hour_0
	sub cx,6				;delete previus hour hand
	add eax,ecx
	jmp reseted_hr_hand
inner_hour_0:	
	sub eax,6

reseted_hr_hand:
	
	mov theta,eax
	call hour_hand
	
end_get_time:	
	ret
get_analog_time endp

;to aschii procedure is used to convert the number to its specific aschii value
to_aschii proc

	mov ah,0		
	mov dl,10       
	div dl          
	add ah,30h
	add al,30h
            
	ret
to_aschii endp

get_time proc
	;input bx as the address of time buffer
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,ch
	call bcd2dec
	mov ch,dl
	mov ah,0
	
	mov is_24,1				;assign false if current time is not 24 or 12am
	
	mov al,ch     
	cmp al,24
	jne store
	
	mov is_24,0				;assign true if current time is 24 or 12am
	
	store:
	call to_aschii     
		
	mov [bx],ax     
		
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,cl
	call bcd2dec
	mov cl,dl	
	mov ah,0	
		
	mov al,cl     
	call to_aschii        
	mov [bx+3], ax     

	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,dh
	call bcd2dec
	mov dh,dl
	mov ah,0
	
	mov al,dh     
	call to_aschii      
	mov [bx+6],ax      

	ret
get_time endp

check_one_sec proc 
	cmp temp_sec,60
	jne no_reset_sec_counter
	mov temp_sec,0
	no_reset_sec_counter:

		mov ah,2ch
		int 21h
		cmp dh,temp_sec
		jne not_yet_sec
		mov is_sec_pass,1b
		inc temp_sec
			
	not_yet_sec:	
	ret
check_one_sec endp

simulate_time proc
	cmp first_sec,1b
	jne not_first_sec
	mov first_sec,0b
	mov simulate_sec,-1

not_first_sec:
	cmp simulate_sec,60
	jne	no_reset_sec
	inc simulate_minute
	mov simulate_sec,0

no_reset_sec:	

	cmp is_sec_pass,1b
	jne not_yet_sec2
	mov is_sec_pass,0b	
	inc simulate_sec
			
not_yet_sec2:	
	
	ret
simulate_time endp

init_stopwatch proc 
	mov is_24,1				;assign false if current time is not 24 or 12am
	
	cmp is_reset,1b
	jne not_reset
	mov simulate_milisec,0
	mov simulate_sec,0
	mov simulate_minute,0
	mov is_reset,0b
	
not_reset:	
	call check_one_sec	
	cmp is_start,1b
	jne not_yet_start
	call simulate_time	
	
not_yet_start:	
	
	mov al,simulate_minute   
	call to_aschii     
	mov [bx],ax     

	mov al,simulate_sec  
	call to_aschii        
	mov [bx+3], ax     

	cmp is_start,1b
	jne con4
	mov ah,2ch
	int 21h
	mov simulate_milisec,dl	
con4:	

	mov al,simulate_milisec  
	call to_aschii      
	mov [bx+6],ax      
	; set 1 million microseconds interval (1 second)
	ret
init_stopwatch endp

simulate_timer_time proc
	cmp first_timer_sec,1b
	jne not_first_timer_sec
	mov first_timer_sec,0b
	mov simulate_timer_ss,-1

not_first_timer_sec:
	cmp simulate_timer_ss,-1
	jne	no_reset_sec2
	mov simulate_timer_ss,59
	
	cmp simulate_timer_hh,0
	je con8
	cmp simulate_timer_mm,0
	jne con8
	mov simulate_timer_mm,59
	dec simulate_timer_hh
	jmp no_reset_sec2
con8:
	cmp simulate_timer_mm,0
	je no_reset_sec2
	dec simulate_timer_mm
	
no_reset_sec2:	

	cmp is_sec_pass,1b
	jne not_yet_sec3
	mov is_sec_pass,0b	
	dec simulate_timer_ss
			
not_yet_sec3:	
	
	ret
simulate_timer_time endp

init_timer proc 
	mov is_24,1				;assign false if current time is not 24 or 12am
	
	cmp is_timer_reset,1b
	jne not_reset2
	mov al,timer_hh
	mov simulate_timer_hh,al
	mov al,timer_mm
	mov simulate_timer_mm,al
	mov al,timer_ss
	mov simulate_timer_ss,al
	mov is_timer_reset,0b
	
not_reset2:	
	call check_one_sec	
	cmp is_timer_start,1b
	jne not_yet_start2
	cmp simulate_timer_hh,0
	jne con_countdown
	cmp simulate_timer_mm,0
	jne con_countdown
	cmp simulate_timer_ss,0	
	jne con_countdown
	mov is_timer_start,0b
	mov invoke_timer_alarm,1b
	jmp stop_countdown
	
con_countdown:
	call simulate_timer_time
	
stop_countdown:

not_yet_start2:	
	
	mov al,simulate_timer_hh
	call to_aschii     
	mov [bx],ax     

	mov al,simulate_timer_mm 
	call to_aschii        
	mov [bx+3], ax     

	mov al,simulate_timer_ss
	call to_aschii      
	mov [bx+6],ax      

	ret
init_timer endp

clock_int proc
;interrupt procedure activated by timer

	;get new time
	lea	bx,time_buf			;bx points to time buffer
	cmp is_show_clock,1b
	je run_get_time
	cmp is_stopwatch,1b
	je run_init_stopwatch
	cmp is_timer,1b
	je run_init_timer

run_get_time:
	cmp is_analog,1b
	jne call_get_dig_time
	call get_analog_time			;store time in buffer
	jmp no_ana_alarm
	
call_get_dig_time:	
	call get_time	
	jmp check_alarm
	
run_init_stopwatch:
	call init_stopwatch		;store time in buffer	
	jmp alarm_1_minite
	
run_init_timer:	
	call init_timer
	jmp alarm_1_minite
	
check_alarm:
	;check alarm
	mov al,alarm_buf[0]
	mov input[0],al
	mov al,alarm_buf[1]
	mov input[1],al
	mov al,alarm_buf[3]
	mov input[3],al	
	mov al,alarm_buf[4]
	mov input[4],al
	call get_alarm
	
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,ch
	call bcd2dec
	mov ch,dl
	cmp ch,alarm_hh
	jne no_alarm_invoke
	
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,cl
	call bcd2dec
	mov cl,dl
	cmp cl,alarm_mm
	jne no_alarm_invoke
	
	mov invoker_alarm,1b
	jmp alarm_1_minite		;set alarm for 1 minute only
	
no_alarm_invoke:	
	mov invoker_alarm,0b	
alarm_1_minite:
	cmp is_analog,1b
	je no_ana_alarm

	;print first digit of minutes value
	mov	start_row,65
	mov	start_col,40
	call reset_print
	
	
	mov al,is_24
	cmp al,0
	je h10
	
	mov	al,'0'
	cmp	[bx],al	
	jne	h11
	
	h10:
		call print_0
		jmp	h1
	
	h11:
		inc	al
		cmp	[bx],al
		jne	h12
		call print_1
		jmp	h1
	h12:	
		inc	al
		cmp	[bx],al
		jne	h13
		call print_2
		jmp	h1
	h13:	
		inc	al
		cmp	[bx],al
		jne	h14
		call print_3
		jmp	h1
	h14:	
		inc	al
		cmp	[bx],al
		jne	h15
		call print_4
		jmp	h1
	h15:	
		inc	al
		cmp	[bx],al
		jne	h16
		call print_5
		jmp	h1
	h16:	
		inc	al
		cmp	[bx],al
		jne	h17
		call print_6
		jmp	h1
	h17:	
		inc	al
		cmp	[bx],al
		jne	h18
		call print_7
		jmp	h1
	h18:	
		inc	al
		cmp	[bx],al
		jne	h19
		call print_8
		jmp	h1
	h19:	
		call print_9
		
	h1:
	
	;print second digit of hour value
	mov	start_row,65
	mov	start_col,70
	call reset_print
			
	mov al,is_24
	cmp al,0
	je h20
			
	mov	al,'0'
	cmp	[bx+1],al
	jne	h21
	
	h20:
		call print_0
		jmp	h2
		
	h21:	
		inc	al
		cmp	[bx+1],al
		jne	h22
		call print_1
		jmp	h2
	h22:	
		inc	al
		cmp	[bx+1],al
		jne	h23
		call print_2
		jmp	h2
	h23:	
		inc	al
		cmp	[bx+1],al
		jne	h24
		call print_3
		jmp	h2
	h24:	
		inc	al
		cmp	[bx+1],al
		jne	h25
		call print_4
		jmp	h2
	h25:	
		inc	al
		cmp	[bx+1],al
		jne	h26
		call print_5
		jmp	h2
	h26:	
		inc	al
		cmp	[bx+1],al
		jne	h27
		call print_6
		jmp	h2
	h27:	
		inc	al
		cmp	[bx+1],al
		jne	h28
		call print_7
		jmp	h2
	h28:	
		inc	al
		cmp	[bx+1],al
		jne	h29
		call print_8
		jmp	h2
	h29:	
		call print_9
	h2:	
	
	;print a seprator
	mov	start_row,65
	mov	start_col,100
	call print_seperator
	
	;print first digit of minutes value
	mov	start_row,65
	mov	start_col,130
	call reset_print
	
	mov	al,'0'
	cmp	[bx+3],al	
	jne	m11
	
	call print_0
	jmp	m1
	
	m11:
		inc	al
		cmp	[bx+3],al
		jne	m12
		call print_1
		jmp	m1
	m12:	
		inc	al
		cmp	[bx+3],al
		jne	m13
		call print_2
		jmp	m1
	m13:	
		inc	al
		cmp	[bx+3],al
		jne	m14
		call print_3
		jmp	m1
	m14:	
		inc	al
		cmp	[bx+3],al
		jne	m15
		call print_4
		jmp	m1
	m15:	
		inc	al
		cmp	[bx+3],al
		jne	m16
		call print_5
		jmp	m1
	m16:	
		inc	al
		cmp	[bx+3],al
		jne	m17
		call print_6
		jmp	m1
	m17:	
		inc	al
		cmp	[bx+3],al
		jne	m18
		call print_7
		jmp	m1
	m18:	
		inc	al
		cmp	[bx+3],al
		jne	m19
		call print_8
		jmp	m1
	m19:	
		call print_9
		
	m1:
	
	;print second digit of minute value
	mov	start_row,65
	mov	start_col,160
	call reset_print
			
	mov	al,'0'
	cmp	[bx+4],al
	jne	m21
	call print_0
	jmp	m2
		
	m21:	
		inc	al
		cmp	[bx+4],al
		jne	m22
		call print_1
		jmp	m2
	m22:	
		inc	al
		cmp	[bx+4],al
		jne	m23
		call print_2
		jmp	m2
	m23:	
		inc	al
		cmp	[bx+4],al
		jne	m24
		call print_3
		jmp	m2
	m24:	
		inc	al
		cmp	[bx+4],al
		jne	m25
		call print_4
		jmp	m2
	m25:	
		inc	al
		cmp	[bx+4],al
		jne	m26
		call print_5
		jmp	m2
	m26:	
		inc	al
		cmp	[bx+4],al
		jne	m27
		call print_6
		jmp	m2
	m27:	
		inc	al
		cmp	[bx+4],al
		jne	m28
		call print_7
		jmp	m2
	m28:	
		inc	al
		cmp	[bx+4],al
		jne	m29
		call print_8
		jmp	m2
	m29:	
		call print_9
	m2:
	
	;print a seprator
	mov	start_row,65
	mov	start_col,190
	call print_seperator
	
	;print first digit of second value
	mov	start_row,65
	mov	start_col,220
	call reset_print
	
	mov	al,'0'
	cmp	[bx+6],al	
	jne	s11
	
	call print_0
	jmp	s1
	
	s11:
		inc	al
		cmp	[bx+6],al
		jne	s12
		call print_1
		jmp	s1
	s12:	
		inc	al
		cmp	[bx+6],al
		jne	s13
		call print_2
		jmp	s1
	s13:	
		inc	al
		cmp	[bx+6],al
		jne	s14
		call print_3
		jmp	s1
	s14:	
		inc	al
		cmp	[bx+6],al
		jne	s15
		call print_4
		jmp	s1
	s15:	
		inc	al
		cmp	[bx+6],al
		jne	s16
		call print_5
		jmp	s1
	s16:	
		inc	al
		cmp	[bx+6],al
		jne	s17
		call print_6
		jmp	s1
	s17:	
		inc	al
		cmp	[bx+6],al
		jne	s18
		call print_7
		jmp	s1
	s18:	
		inc	al
		cmp	[bx+6],al
		jne	s19
		call print_8
		jmp	s1
	s19:	
		call print_9
		
	s1:
	;print second digit of second value
	mov	start_row,65
	mov	start_col,250
	call reset_print
			
	mov	al,'0'
	cmp	[bx+7],al
	jne	s21
	call print_0
	jmp	s2
		
	s21:	
		inc	al
		cmp	[bx+7],al
		jne	s22
		call print_1
		jmp	s2
	s22:	
		inc	al
		cmp	[bx+7],al
		jne	s23
		call print_2
		jmp	s2
	s23:	
		inc	al
		cmp	[bx+7],al
		jne	s24
		call print_3
		jmp	s2
	s24:	
		inc	al
		cmp	[bx+7],al
		jne	s25
		call print_4
		jmp	s2
	s25:	
		inc	al
		cmp	[bx+7],al
		jne	s26
		call print_5
		jmp	s2
	s26:	
		inc	al
		cmp	[bx+7],al
		jne	s27
		call print_6
		jmp	s2
	s27:	
		inc	al
		cmp	[bx+7],al
		jne	s28
		call print_7
		jmp	s2
	s28:	
		inc	al
		cmp	[bx+7],al
		jne	s29
		call print_8
		jmp	s2
	s29:	
		call print_9
	s2:

no_ana_alarm:
	iret	;interupt return
clock_int	endp

setup_int proc

	;saves old vector and sets up new vector
	;input:	al = interrupt number
	;		di = address of buffer for old vector
	;		si = address of buffer containing new vector
	;save old interrupt vector
	
	mov	ah,35h				;35h gets vector
	int	21h					;es:bx = vector
			
	mov	[di],bx				;save offset
	mov	[di+2],es			;save segment, di associtaed with es and support string handling operation
	
	;setup new vector
	mov	dx,[si]				;dx has offset
	push ds					;save ds
	mov	ds,[si+2]			;ds has segment number, si associtaed with ds and support string handling operation
			
	mov	ah,25h				;25h sets vector, DS:DX = new vector to be used for specified interrupt
	int	21h
			
	pop	ds					;restore ds
	ret
	
setup_int endp
;//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION
main proc
	mov ax,@data
	mov ds,ax         
	
show_menu:

	call clr_src
	call menu

	mov ax,0000h
	int 33h
	
	mov ax,0001h
	int 33h
	
	chk_mouse:
	call mouse
	
	call chk_show_clock
	cmp is_show_clock,1b
	je call_show_clock
	
	call chk_set_alarm
	cmp is_set_alarm,1b
	je call_set_alarm	
	
	call chk_timer
	cmp is_timer,1b
	je call_timer
	
	call chk_stopwatch
	cmp is_stopwatch,1b
	je call_stopwatch	
	
	call check_exit
	
	cmp is_exit,1b
	mov is_exit,0b
	jne re_chk_press

	jmp exit
	
re_chk_press:
	jmp chk_mouse

call_show_clock:
	mov ax,0002h
	int 33h
	call select_clock
	mov is_show_clock,0b	
	
	jmp show_menu
	
call_set_alarm:
	mov ax,0002h
	int 33h
	call set_alarm
	mov is_set_alarm,0b	
	jmp show_menu
	
call_timer:
	call timer
	mov is_timer,0b
	jmp show_menu
	
call_stopwatch:
	call stopwatch
	mov is_stopwatch,0b	
	jmp show_menu
	
exit:	
	mov ax,0002h
	int 33h
	
	call clr_src
	mov	ax,4c00h     
	int 21h    
	
main endp
;//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION//MAIN FUNCTION

menu proc
	mov ax,0600h
	mov bh,option_color
	mov cx,0508h	;ul r:c
	mov dx,0546h	;lr r:c
	int 10h
	
	mov dh,05h		;set row
	mov dl,24h		;set column
	call res_cur
	
	lea dx,clock_title
	call print
	
	mov ax,0600h
	mov bh,option_color
	mov cx,0a08h	;ul r:c
	mov dx,0a20h	;lr r:c
	int 10h	
	
	mov dh,0ah		;set row
	mov dl,10h		;set column
	call res_cur
	
	lea dx,show_clock_str
	call print
	
	mov ax,0600h
	mov bh,option_color
	mov cx,0a30h	;ul r:c
	mov dx,0a46h	;lr r:c
	int 10h
	
	mov dh,0ah		;set row
	mov dl,37h		;set column
	call res_cur
	
	lea dx,set_alarm_str
	call print
	
	mov ax,0600h
	mov bh,option_color
	mov cx,0e08h	;ul r:c
	mov dx,0e20h	;lr r:c
	int 10h	
	
	mov dh,0eh		;set row
	mov dl,12h		;set column
	call res_cur
	
	lea dx,timer_str
	call print
	
	mov ax,0600h
	mov bh,option_color
	mov cx,0e30h	;ul r:c
	mov dx,0e46h	;lr r:c
	int 10h	
	
	mov dh,0eh		;set row
	mov dl,37h		;set column
	call res_cur
	
	lea dx,stopwatch_str
	call print	
	
	mov ax,0600h
	mov bh,option_color
	mov cx,1208h	;ul r:c
	mov dx,1220h	;lr r:c
	int 10h
	
	mov dh,12h		;set row
	mov dl,12h		;set column
	call res_cur
	
	lea dx,quit_str
	call print	
	
	mov dh,16h		;set row
	mov dl,08h		;set column
	call res_cur
	
	lea dx,wait_respond_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur
	
	ret
menu endp

mouse proc
	chk_press:
	mov ax, 3
	int 33h     			;Check the mouse
	cmp bx, 0   			;See if button is pressed
	je chk_press    		;If Not pressed, go back and check again

	xor bx, bx  			;Okay, button is pressed, clear the result

	chk_release:
	mov ax, 3
	int 33h     			;Check the mouse
	cmp bx, 0   			;See if button is released
	jne chk_release   		;If NOT equal, then not released, go check again.

	xor bx, bx  			;button is released, clear the result
	
	mov mouse_col,cx
	mov mouse_row,dx

	;divide 8 is for text mode
	mov ax,mouse_col
	mov dl,8
	div dl
	mov mouse_col,ax
	
	mov ax,mouse_row
	mov dl,8
	div dl
	mov mouse_row,ax	

	ret
mouse endp

check_exit proc
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl not_exit
	cmp al,20h
	jg not_exit
	mov ax,mouse_row		;real value store in al	
	cmp al,12h
	jne not_exit
	mov is_exit,1b
not_exit:
	ret
check_exit endp

chk_show_clock proc
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl not_show_clock
	cmp al,20h
	jg not_show_clock
	mov ax,mouse_row		;real value store in al	
	cmp al,0ah
	jne not_show_clock
	mov is_show_clock,1b
not_show_clock:
	ret
chk_show_clock endp

chk_select_clock proc
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl not_analog
	cmp al,20h
	jg not_analog
	mov ax,mouse_row		;real value store in al	
	cmp al,0ah
	jne not_analog
	mov is_analog,1b
	jmp not_digital
not_analog:	
	mov ax,mouse_col		;real value store in al
	cmp al,30h				
	jl not_digital
	cmp al,46h
	jg not_digital
	mov ax,mouse_row		;real value store in al	
	cmp al,0ah
	jne not_digital
	mov is_digital,1b
not_digital:
	ret
chk_select_clock endp

select_clock proc
	call clr_src
	
	mov ax,0600h
	mov bh,option_color
	mov cx,0a08h	;ul r:c
	mov dx,0a20h	;lr r:c
	int 10h	
	
	mov dh,0ah		;set row
	mov dl,11h		;set column
	call res_cur
	
	lea dx,analog_str
	call print
	
	mov ax,0600h
	mov bh,option_color
	mov cx,0a30h	;ul r:c
	mov dx,0a46h	;lr r:c
	int 10h
	
	mov dh,0ah		;set row
	mov dl,38h		;set column
	call res_cur
	
	lea dx,digital_str
	call print
	
	mov dh,16h		;set row
	mov dl,00h		;set column
	call res_cur
	
	lea dx,wait_respond_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur	
	
	mov ax,0000h
	int 33h		
	chk_mouse_8:

	mov ax,0001h
	int 33h		
	call mouse
	
	call chk_select_clock
	cmp is_analog,1b
	je call_analog_clock
	
	cmp is_digital,1b
	je call_digital_clock
	
re_chk_press_8:
	jmp chk_mouse_8	
	
call_analog_clock:
	call analog_clock
	mov is_analog,0b		
	jmp return_8
	
call_digital_clock:
	call digital_clock
	mov is_digital,0b	
	
return_8:
	mov ax,0002h
	int 33h	
	ret
select_clock endp

check_ana_exit proc
	mov ax,mouse_col		;real value store in al
	cmp al,02h				
	jl not_ana_exit
	cmp al,0ah
	jg not_ana_exit
	mov ax,mouse_row		;real value store in al	
	cmp al,32h
	je chk_ana_2_line
	cmp al,33h
	jne not_ana_exit	
	
chk_ana_2_line:	
	
	mov is_exit,1b
not_ana_exit:
	ret
check_ana_exit endp

analog_clock proc
	mov ax,0012h
	int 10h
	
	mov dx,0010h
	call res_cur

	mov eax,90
	mov theta,eax
	
	call circle
	call analog_time_num

	call sec_indicator
	call hour_indicator	
	
	mov ah,02h				;get real time
	int 1ah                	;ch = hr, cl = min, dh = sec
	mov dl,dh
	call bcd2dec
	mov dh,dl
	mov temp_sec_ana,dh	
	mov is_sec_pass_ana,1b
	
	mov	new_vector,offset clock_int
	mov	new_vector+2,seg clock_int
	
	lea	di,old_vector		;di points to vector buffer
	lea	si,new_vector		;si points to new vector
	mov	al,1ch				;timer interrupt
	call setup_int			;setup new interrupt vector
		
	mov dh,19h		;set row
	mov dl,02h		;set column
	call res_cur
	
	lea dx,back_vga_str
	call print			
		
	mov dh,1ch		;set row
	mov dl,00h		;set column
	call res_cur
	
	lea dx,wait_respond_vga_str
	call print	
	
chk_mouse_9:
	mov ax,0001h
	int 33h	
	call mouse
	
	call check_ana_exit
	
	cmp is_exit,1b
	mov is_exit,0b
	jne re_chk_press_9

	jmp return_9
	
re_chk_press_9:
	;invoker alarm
	;cmp invoker_alarm,1b
	;jne chk_mouse_9
	;mov invoker_alarm,0b
	;call two_tigers
	
	jmp chk_mouse_9

return_9:	
	mov ax,0002h
	int 33h		
	
	;restore old interrupt vector
	lea	di,new_vector		
	lea	si,old_vector	
	mov	al,1ch				;timer interrupt
	call setup_int			;restore old vector
	
	;reset to original mode
	mov	ah,0
	mov	al,3
	int	10h		

	ret
analog_clock endp

digital_clock proc
	;set to graphics mode vga (320x200 256 color)
	mov	ah,0				;set console mode
	mov	al,13h				;to 320x200 256
	int	10h

	row_drawer 	0, 0, 32000, clock_color		;15h	
	row_drawer 	100, 0, 32000, clock_color		;320 = one whole line	
	
	call get_date
	lea dx,date_buf
	call print	
	
	call chk_day	
	
	;setup interrupt procedure by
	;placing segment:offset of clock_int in new_vec
	
	mov	new_vector,offset clock_int
	mov	new_vector+2,seg clock_int
	
	lea	di,old_vector		;di points to vector buffer
	lea	si,new_vector		;si points to new vector
	mov	al,1ch				;timer interrupt
	call setup_int			;setup new interrupt vector
	
con3:	

	mov dh,12h		;set row
	mov dl,04h		;set column
	call res_cur
	
	lea dx,back_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,00h		;set column
	call res_cur
	
	lea dx,wait_respond_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur
	
chk_mouse_4:
	mov ax,0001h
	int 33h	
	call mouse
	
	call check_exit
	
	cmp is_exit,1b
	mov is_exit,0b
	jne re_chk_press_4

	jmp return_4
	
re_chk_press_4:
	;invoker alarm
	cmp invoker_alarm,1b
	jne chk_mouse_4
	mov invoker_alarm,0b
	call two_tigers
	
	jmp chk_mouse_4

return_4:	
	mov ax,0002h
	int 33h
	
	;read keyboard, return al = char
	;mov	ah,0
	;int	16h
	
	;restore old interrupt vector
	lea	di,new_vector		
	lea	si,old_vector	
	mov	al,1ch				;timer interrupt
	call setup_int			;restore old vector
	
	;reset to original mode
	mov	ah,0
	mov	al,3
	int	10h	
	ret
digital_clock endp

chk_set_alarm proc
	mov ax,mouse_col		;real value store in al
	cmp al,30h				
	jl not_set_alarm
	cmp al,46h
	jg not_set_alarm
	mov ax,mouse_row		;real value store in al	
	cmp al,0ah
	jne not_set_alarm
	mov is_set_alarm,1b
not_set_alarm:
	ret
chk_set_alarm endp

get_alarm proc
	mov ah,0
	mov al,input[0]
	sub al,30h
	mul ten
	mov dl,input[1]
	sub dl,30h
	add al,dl
	mov alarm_hh,al
	
	mov ah,0
	mov al,input[3]
	sub al,30h
	mul ten
	mov dl,input[4]
	sub dl,30h
	add al,dl
	mov alarm_mm,al	
	ret
get_alarm endp

set_alarm proc
	call clr_src
	
	cmp is_alarm_set,1b
	jne no_alarm
	
	mov dh,09h		;set row
	mov dl,09h		;set column
	call res_cur	
	
	lea dx,alarm_on_str
	call print	
	lea dx,alarm_buf
	call print	

	mov dh,0ah		;set row
	mov dl,09h		;set column
	call res_cur	
	
	lea dx,alarm_cancel_str
	call print	
	
	jmp alarm_menu
	
no_alarm:	
	mov dh,0ah		;set row
	mov dl,09h		;set column
	call res_cur	
	
	lea dx,alarm_off_str
	call print	

alarm_menu:	
	mov dh,0ch		;set row
	mov dl,09h		;set column
	call res_cur	
	
	lea dx,input_alarm_str
	call print	
	lea dx,arr
	call scan
	
	cmp is_alarm_set,0b
	je go_alarm
	cmp input[0],'-'
	je cancel_alarm
	jmp go_alarm
	
cancel_alarm:
	mov alarm_buf[0],'9'
	mov alarm_buf[1],'9'
	mov alarm_buf[3],'9'	
	mov alarm_buf[4],'9'
	
	mov is_alarm_set,0b
	
	mov dh,0eh		;set row
	mov dl,09h		;set column
	call res_cur
	
	lea dx,alarm_cancel_ok_str
	call print
	
	jmp con2
	
go_alarm:	
	call get_alarm
	
	mov ah,2dh
	mov ch,alarm_hh
	mov cl,alarm_mm
	int 21h
	
	cmp input[2],':'
	jne wrong_format
	
	cmp al,00h
	je alarm_ok
	
wrong_format:	
	mov dh,0eh		;set row
	mov dl,09h		;set column
	call res_cur
	
	lea dx,alarm_fail_str
	call print	

	jmp con2
	
alarm_ok:

	mov al,input[0]
	mov alarm_buf[0],al
	mov al,input[1]
	mov alarm_buf[1],al
	mov al,input[3]
	mov alarm_buf[3],al	
	mov al,input[4]
	mov alarm_buf[4],al
	
	mov is_alarm_set,1b
	
	mov dh,0eh		;set row
	mov dl,09h		;set column
	call res_cur
	
	lea dx,alarm_ok_str
	call print
	
con2:	
	
	mov ax,0600h
	mov bh,option_color
	mov cx,1208h	;ul r:c
	mov dx,1220h	;lr r:c
	int 10h
	
	mov dh,12h		;set row
	mov dl,13h		;set column
	call res_cur
	
	lea dx,back_str
	call print	
	
	mov dh,16h		;set row
	mov dl,08h		;set column
	call res_cur
	
	lea dx,wait_respond_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur
	
chk_mouse_2:
	mov ax,0001h
	int 33h	
	call mouse
	
	call check_exit
	
	cmp is_exit,1b
	mov is_exit,0b
	jne re_chk_press_2

	jmp return_2
	
re_chk_press_2:
	jmp chk_mouse_2

return_2:	
	mov ax,0002h
	int 33h
	ret
set_alarm endp

chk_timer proc
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl not_timer
	cmp al,20h
	jg not_timer
	mov ax,mouse_row		;real value store in al	
	cmp al,0eh
	jne not_timer
	mov is_timer,1b
not_timer:
	ret
chk_timer endp

timer_btn proc
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl chk_stop_2
	cmp al,17h
	jg chk_stop_2
	mov ax,mouse_row		;real value store in al	
	cmp al,04h
	jne chk_stop_2
	cmp simulate_timer_hh,0
	jne not_zero
	cmp simulate_timer_mm,0
	jne not_zero
	cmp simulate_timer_ss,0
	jne not_zero	
	jmp chk_stop_2
not_zero:	
	mov is_timer_start,1b
chk_stop_2:
	mov ax,mouse_col		;real value store in al
	cmp al,20h				
	jl chk_reset_2
	cmp al,2fh
	jg chk_reset_2
	mov ax,mouse_row		;real value store in al	
	cmp al,04h
	jne chk_reset_2
	mov is_timer_start,0b
chk_reset_2:
	mov ax,mouse_col		;real value store in al
	cmp al,38h				
	jl chk_edit
	cmp al,45h
	jg chk_edit
	mov ax,mouse_row		;real value store in al	
	cmp al,04h
	jne chk_edit
	mov is_timer_start,0b
	mov is_timer_reset,1b
chk_edit:	
	mov ax,mouse_col		;real value store in al
	cmp al,30h				
	jl chk_exit
	cmp al,47h
	jg chk_exit
	mov ax,mouse_row		;real value store in al	
	cmp al,12h
	jne chk_exit
	mov is_edit,1b
chk_exit:
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl con7
	cmp al,20h
	jg con7
	mov ax,mouse_row		;real value store in al	
	cmp al,12h
	jne con7
	mov is_timer_exit,1b
con7:
	ret
timer_btn endp

get_timer proc
	mov ah,0
	mov al,input[0]
	sub al,30h
	mul ten
	mov dl,input[1]
	sub dl,30h
	add al,dl
	mov timer_hh,al
	
	mov ah,0
	mov al,input[3]
	sub al,30h
	mul ten
	mov dl,input[4]
	sub dl,30h
	add al,dl
	mov timer_mm,al	
	
	mov ah,0
	mov al,input[6]
	sub al,30h
	mul ten
	mov dl,input[7]
	sub dl,30h
	add al,dl
	mov timer_ss,al	
	ret
get_timer endp

timer proc
back_timer:
	;set to graphics mode vga (320x200 256 color)
	mov	ah,0				;set console mode
	mov	al,13h				;to 320x200 256
	int	10h

	row_drawer 	0, 0, 32000, clock_color		;15h	
	row_drawer 	100, 0, 32000, clock_color		;320 = one whole line	
	
	call get_date
	lea dx,date_buf
	call print	
	
	call chk_day	
	
	mov dh,04h		;set row
	mov dl,04h		;set column
	call res_cur
	
	lea dx,start_vga_str
	call print		
	
	mov dh,04h		;set row
	mov dl,10h		;set column
	call res_cur
	
	lea dx,stop_vga_str
	call print		
	
	mov dh,04h		;set row
	mov dl,1ch		;set column
	call res_cur
	
	lea dx,reset_vga_str
	call print		
	
	mov ah,2ch
	int 21h	
	mov temp_sec,dh
	;setup interrupt procedure by
	;placing segment:offset of clock_int in new_vec
	
	mov	new_vector,offset clock_int
	mov	new_vector+2,seg clock_int
	
	lea	di,old_vector		;di points to vector buffer
	lea	si,new_vector		;si points to new vector
	mov	al,1ch				;timer interrupt
	call setup_int			;setup new interrupt vector
 
	mov dh,12h		;set row
	mov dl,04h		;set column
	call res_cur
	
	lea dx,back_vga_str
	call print	
	
	mov dh,12h		;set row
	mov dl,40h		;set column
	call res_cur
	
	lea dx,edit_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,00h		;set column
	call res_cur
	
	lea dx,wait_respond_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur
	
chk_mouse_7:
	mov ax,0001h
	int 33h	
	call mouse
	
	call timer_btn
	
	cmp is_edit,1b
	mov is_edit,0b
	jne re_chk_timer_exit
	
	;restore old interrupt vector
	lea	di,new_vector		
	lea	si,old_vector	
	mov	al,1ch				;timer interrupt
	call setup_int			;restore old vector	
	;reset to original mode
	mov	ah,0
	mov	al,3
	int	10h	
	
	call edit_timer
	jmp back_timer
	
re_chk_timer_exit:
	
	cmp is_timer_exit,1b
	mov is_timer_exit,0b
	jne re_chk_press_7

	jmp return_7
	
re_chk_press_7:
	;invoker alarm
	cmp invoke_timer_alarm,1b
	jne chk_mouse_7
	mov invoke_timer_alarm,0b
	call two_tigers
	
	jmp chk_mouse_7

return_7:	
	mov ax,0002h
	int 33h
	
	;restore old interrupt vector
	lea	di,new_vector		
	lea	si,old_vector	
	mov	al,1ch				;timer interrupt
	call setup_int			;restore old vector
	
	;reset to original mode
	mov	ah,0
	mov	al,3
	int	10h	
	ret
timer endp

check_edit_exit proc
	mov ax,mouse_col		;real value store in al
	cmp al,30h				
	jl not_edit_exit
	cmp al,46h
	jg not_edit_exit
	mov ax,mouse_row		;real value store in al	
	cmp al,16h
	jne not_edit_exit
	mov is_exit,1b
not_edit_exit:
	ret
check_edit_exit endp

edit_timer proc
	call clr_src
	
	;cmp is_timer_set,1b
	;jne no_timer_set
	
	mov dh,09h		;set row
	mov dl,09h		;set column
	call res_cur	
	
	lea dx,timer_set_str
	call print	
	lea dx,timer_buf
	call print	

	mov dh,0ah		;set row
	mov dl,09h		;set column
	call res_cur	

	mov dh,0ch		;set row
	mov dl,09h		;set column
	call res_cur	
	
	lea dx,input_timer_str
	call print	
	lea dx,arr
	call scan
	
	call get_timer
	
	mov ah,2dh
	mov ch,timer_hh
	mov cl,timer_mm
	mov dh,timer_ss
	int 21h
	
	cmp input[2],':'
	jne wrong_format2
	cmp input[5],':'
	jne wrong_format2	
	
	cmp al,00h
	je timer_ok
	
wrong_format2:	
	mov dh,0eh		;set row
	mov dl,09h		;set column
	call res_cur
	
	lea dx,timer_fail_str
	call print	

	jmp con6
	
timer_ok:
	mov is_timer_start,0b

	mov al,timer_ss
	mov simulate_timer_ss,al
	mov al,timer_mm
	mov simulate_timer_mm,al	
	mov al,timer_hh
	mov simulate_timer_hh,al
	
	mov al,input[0]
	mov timer_buf[0],al
	mov al,input[1]
	mov timer_buf[1],al
	mov al,input[3]
	mov timer_buf[3],al	
	mov al,input[4]
	mov timer_buf[4],al
	mov al,input[6]
	mov timer_buf[6],al	
	mov al,input[7]
	mov timer_buf[7],al	
	
	mov dh,0eh		;set row
	mov dl,09h		;set column
	call res_cur
	
	lea dx,timer_ok_str
	call print
	
con6:	
	
	mov ax,0600h
	mov bh,option_color
	mov cx,1630h	;ul r:c
	mov dx,1646h	;lr r:c
	int 10h
	
	mov dh,16h		;set row
	mov dl,3ah		;set column
	call res_cur
	
	lea dx,back_str
	call print	
	
	mov dh,16h		;set row
	mov dl,08h		;set column
	call res_cur
	
	lea dx,wait_respond_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur
	
chk_mouse_6:
	mov ax,0001h
	int 33h	
	call mouse
	
	call check_edit_exit
	
	cmp is_exit,1b
	mov is_exit,0b
	jne re_chk_press_6

	jmp return_6
	
re_chk_press_6:
	jmp chk_mouse_6

return_6:	
	mov ax,0002h
	int 33h
	ret
edit_timer endp

chk_stopwatch proc
	mov ax,mouse_col		;real value store in al
	cmp al,30h				
	jl not_stopwatch
	cmp al,46h
	jg not_stopwatch
	mov ax,mouse_row		;real value store in al	
	cmp al,0eh
	jne not_stopwatch
	mov is_stopwatch,1b
not_stopwatch:
	ret
chk_stopwatch endp

stopwatch_btn proc
	mov ax,mouse_col		;real value store in al
	cmp al,08h				
	jl chk_stop
	cmp al,17h
	jg chk_stop
	mov ax,mouse_row		;real value store in al	
	cmp al,04h
	jne chk_stop
	mov is_start,1b
chk_stop:
	mov ax,mouse_col		;real value store in al
	cmp al,20h				
	jl chk_reset
	cmp al,2fh
	jg chk_reset
	mov ax,mouse_row		;real value store in al	
	cmp al,04h
	jne chk_reset
	mov is_start,0b
chk_reset:
	mov ax,mouse_col		;real value store in al
	cmp al,38h				
	jl con5
	cmp al,45h
	jg con5
	mov ax,mouse_row		;real value store in al	
	cmp al,04h
	jne con5
	mov is_start,0b	
	mov is_reset,1b
	mov first_sec,1b
con5:
	ret
stopwatch_btn endp

stopwatch proc
	;set to graphics mode vga (320x200 256 color)
	mov	ah,0				;set console mode
	mov	al,13h				;to 320x200 256
	int	10h

	row_drawer 	0, 0, 32000, clock_color		;15h	
	row_drawer 	100, 0, 32000, clock_color		;320 = one whole line	
	
	call get_date
	lea dx,date_buf
	call print	
	
	call chk_day	
	
	mov dh,04h		;set row
	mov dl,04h		;set column
	call res_cur
	
	lea dx,start_vga_str
	call print		
	
	mov dh,04h		;set row
	mov dl,10h		;set column
	call res_cur
	
	lea dx,stop_vga_str
	call print		
	
	mov dh,04h		;set row
	mov dl,1ch		;set column
	call res_cur
	
	lea dx,reset_vga_str
	call print		
	
	mov ah,2ch
	int 21h	
	mov temp_sec,dh
	;setup interrupt procedure by
	;placing segment:offset of clock_int in new_vec
	
	mov	new_vector,offset clock_int
	mov	new_vector+2,seg clock_int
	
	lea	di,old_vector		;di points to vector buffer
	lea	si,new_vector		;si points to new vector
	mov	al,1ch				;timer interrupt
	call setup_int			;setup new interrupt vector
 
	mov dh,12h		;set row
	mov dl,04h		;set column
	call res_cur
	
	lea dx,back_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,00h		;set column
	call res_cur
	
	lea dx,wait_respond_vga_str
	call print	
	
	mov dh,16h		;set row
	mov dl,28h		;set column
	call res_cur
	
chk_mouse_5:
	mov ax,0001h
	int 33h	
	call mouse
	
	call stopwatch_btn
	call check_exit
	
	cmp is_exit,1b
	mov is_exit,0b
	jne re_chk_press_5

	jmp return_5
	
re_chk_press_5:

	jmp chk_mouse_5

return_5:	
	mov ax,0002h
	int 33h
	
	;restore old interrupt vector
	lea	di,new_vector		
	lea	si,old_vector	
	mov	al,1ch				;timer interrupt
	call setup_int			;restore old vector
	
	;reset to original mode
	mov	ah,0
	mov	al,3
	int	10h	
	ret
stopwatch endp

; check day procedure is used to compare the day of the week and return its String
chk_day proc
	mov al,day
	
	cmp al,0
	jne mon_day

	lea dx,sun
	call print	
	jmp return_3	
mon_day:	
	cmp al,1
	jne tue_day

	lea dx,mon
	call print	
	jmp return_3	
tue_day:		
	cmp al,2
	jne wed_day

	lea dx,tue
	call print	
	jmp return_3	
wed_day:	
	cmp al,3
	jne thu_day
	
	lea dx,wed
	call print	
	jmp return_3
	
thu_day:	
	cmp al,4
	jne fri_day

	lea dx,thu
	call print	
	jmp return_3	
fri_day:	
	cmp al,5
	jne sat_day

	lea dx,fri
	call print	
	jmp return_3
sat_day:	
	
	lea dx,sat
	call print	

return_3:	
	
	ret
chk_day endp

get_date proc

	;input si as the address of date buffer
	mov ah,2ah     			;get date
	int 21h                 ;dh = mm, dl = dd, cx = yy
	
	mov day,al
	
	mov al,dl
	call to_aschii     
		
	mov date_buf[0],al     
	mov date_buf[1],ah   
	
	mov al,dh     
	call to_aschii        
	mov date_buf[3],al     
	mov date_buf[4],ah    

	mov ax,cx     
	div ten
	mov quotient,al
	add ah,30h
	mov date_buf[9],ah    

	mov ax,0
	mov al,quotient
	div ten
	mov quotient,al
	add ah,30h
	mov date_buf[8],ah 
	
	mov ax,0
	mov al,quotient
	div ten
	mov quotient,al
	add ah,30h
	mov date_buf[7],ah 
	
	mov ax,0
	mov al,quotient
	div ten
	mov quotient,al
	add ah,30h
	mov date_buf[6],ah 		    

	ret
get_date endp

;start analog function
;setup the hour hand size and draw it on screen
hour_hand proc
	mov di,80		;length of the line
	mov si,1		;number of line
	
	;midpoint = (320,245)
	mov eax,80
	mov radius,eax
	mov eax,240
	mov adjust_x,eax		
	mov eax,165
	mov adjust_y,eax
	
	finit
	fild theta		
	
	fstp theta
drawing_hour_hand:
 	finit
	fld theta			

	call circle_func	
	
    mov al,hour_hand_color	;color
    mov bh,0				;page 1 
	mov ecx,x				;column	= x	(max = 640)
	mov edx,y				;row	= y	(max = 480)
    mov ah,0ch 
    int 10h 				
	
	dec si
	cmp si,0
	jne drawing_hour_hand	
	cmp di,0
	je end_draw_hour_hand
	dec di
	mov si,36
	
	dec radius
	inc adjust_x	
	inc adjust_y	
	
	jmp drawing_hour_hand
	
end_draw_hour_hand:
	ret
hour_hand endp

;setup the minute hand size and draw it on screen
min_hand proc
	mov di,120		;length of the line
	mov si,1		;number of line
	
	;midpoint = (320,245)
	mov eax,120
	mov radius,eax
	mov eax,200
	mov adjust_x,eax		
	mov eax,125
	mov adjust_y,eax
	
	finit
	fild theta		
	
	fstp theta
drawing_min_hand:
 	finit
	fld theta			

	call circle_func	
	
    mov al,min_hand_color	;color
    mov bh,0				;page 1 
	mov ecx,x				;column	= x	(max = 640)
	mov edx,y				;row	= y	(max = 480)
    mov ah,0ch 
    int 10h 				
	
	dec si
	cmp si,0
	jne drawing_min_hand	
	cmp di,0
	je end_draw_min_hand
	dec di
	mov si,36
	
	dec radius
	inc adjust_x	
	inc adjust_y	
	
	jmp drawing_min_hand
	
end_draw_min_hand:
	ret
min_hand endp

;setup the second hand size and draw it on screen
sec_hand proc
	mov di,140		;length of the line
	mov si,1		;number of line
	
	;midpoint = (320,245)
	mov eax,120
	mov radius,eax
	mov eax,200
	mov adjust_x,eax		
	mov eax,125
	mov adjust_y,eax	
	
drawing_sec_hand:	
	finit
	fild theta		 	

	call circle_func	
	
    mov al,sec_hand_color	;color
    mov bh,0				;page 1 
	mov ecx,x				;column	= x	(max = 640)
	mov edx,y				;row	= y	(max = 480)
    mov ah,0ch 
    int 10h 		
	
	dec si
	cmp si,0
	jne drawing_sec_hand	
	cmp di,0
	je end_draw_sec_hand
	dec di
	mov si,1
		
	dec radius
	inc adjust_x	
	inc adjust_y

	jmp drawing_sec_hand
	
end_draw_sec_hand:
	ret
sec_hand endp

;setup the hour indicator size and draw it on screen
hour_indicator proc
	mov di,22		;length of the line
	mov si,12		;number of line
	;midpoint = (320,245)
	mov eax,165
	mov radius,eax
	mov eax,155
	mov adjust_x,eax		
	mov eax,80
	mov adjust_y,eax	
	mov eax,0
	mov theta,eax
	
drawing_hr_line:	
	finit
	fld theta		 	

	call circle_func	
	
    mov al,15			;color
    mov bh,0			;page 1 
	mov ecx,x			;column	= x	(max = 640)
	mov edx,y			;row	= y	(max = 480)
    mov ah,0ch 
    int 10h 				
	
	finit
	fld theta
	fadd hr_deg_step
	fst theta

	dec si
	cmp si,0
	jne drawing_hr_line	
	cmp di,0
	je end_draw_hr_ln
	dec di
	mov si,12
		
	dec radius
	inc adjust_x	
	inc adjust_y

	jmp drawing_hr_line
	
end_draw_hr_ln:
	ret
hour_indicator endp

;setup the second indicator size and draw it on screen
sec_indicator proc
	mov di,10		;length of the line
	mov si,60		;number of line
	
	;midpoint = (320,245)
	mov eax,165
	mov radius,eax
	mov eax,155
	mov adjust_x,eax		
	mov eax,80
	mov adjust_y,eax	
	mov eax,0
	mov theta,eax
	
drawing_sec_line:	
	finit
	fld theta		 	

	call circle_func	
	
    mov al,11			;color
    mov bh,0			;page 1 
	mov ecx,x			;column	= x	(max = 640)
	mov edx,y			;row	= y	(max = 480)
    mov ah,0ch 
    int 10h 	
	
	finit
	fld theta
	fadd sec_deg_step
	fst theta

	dec si
	cmp si,0
	jne drawing_sec_line	
	cmp di,0
	je end_draw_sec_ln
	dec di
	mov si,60
		
	dec radius
	inc adjust_x	
	inc adjust_y

	jmp drawing_sec_line
	
end_draw_sec_ln:
	ret
sec_indicator endp

;setup the circle size and draw it on screen
circle proc      
	mov di,1			;extra number of circle
	mov si,36000		;number of dot
	
	;midpoint = (320,245)
	mov eax,165
	mov radius,eax
	mov eax,155
	mov adjust_x,eax		
	mov eax,80
	mov adjust_y,eax	
	
	finit 
	fild theta
	fstp theta
	
drawing_cir:
	dec si
	finit
	fld theta		 	;start from 90deg

	call circle_func	
			
    mov al,11			;color
    mov bh,0			;page 1 
	mov ecx,x			;column	= x	(max = 640)
	mov edx,y			;row	= y	(max = 480)
    mov ah,0ch 
    int 10h 		
	
	finit
	fld theta
	fadd deg_step		;increase by 0.01deg
	fst theta

	cmp si,0
	jne drawing_cir	
	cmp di,0
	je end_draw_cir
	dec di
	mov si,36000

	sub radius,10
	add adjust_x,10	
	add adjust_y,10

	jmp drawing_cir
	
end_draw_cir:
	ret
circle endp   	

;for display the 0-12 in fixed circle position
analog_time_num proc
	mov dh,8
	mov dl,47
	call res_cur
	mov dl,'1'
	mov ah,2
	int 21h	 
		   
	mov dh,11
	mov dl,53
	call res_cur
	mov dl,'2'
	mov ah,2
	int 21h	  
               
	mov dh,15
	mov dl,56
	call res_cur
	mov dl,'3'
	mov ah,2
	int 21h	 			   
			   
	mov dh,19
	mov dl,53
	call res_cur
	mov dl,'4'
	mov ah,2
	int 21h	 			   		   
   
	mov dh,22
	mov dl,47
	call res_cur
	mov dl,'5'
	mov ah,2
	int 21h	    

	mov dh,23
	mov dl,40
	call res_cur
	mov dl,'6'
	mov ah,2
	int 21h	
	
	mov dh,22
	mov dl,32
	call res_cur
	mov dl,'7'
	mov ah,2
	int 21h	    
   
	mov dh,19
	mov dl,26
	call res_cur
	mov dl,'8'
	mov ah,2
	int 21h	 

	mov dh,15
	mov dl,23
	call res_cur
	mov dl,'9'
	mov ah,2
	int 21h	 
	
	mov dh,11
	mov dl,25
	call res_cur
	mov dl,'1'
	mov ah,2
	int 21h	  
 
	mov dh,11
	mov dl,26
	call res_cur
	mov dl,'0'
	mov ah,2
	int 21h	 
 
	mov dh,8
	mov dl,30
	call res_cur
	mov dl,'1'
	mov ah,2
	int 21h	  
 
	mov dh,8
	mov dl,31
	call res_cur
	mov dl,'1'
	mov ah,2
	int 21h	 
         
	mov dh,7
	mov dl,39
	call res_cur
	mov dl,'1'
	mov ah,2
	int 21h	
	
	mov dh,7
	mov dl,40
	call res_cur
	mov dl,'2'
	mov ah,2
	int 21h	
	ret
analog_time_num endp
;end analog function

;start sound
;two_tigers is a procedure that contains a pre-coded aka two tigers
two_tigers proc
	tone 523
	tone 587
	tone 659
	tone 523
	tone 523
	call delay
	tone 523
	tone 587
	tone 659
	tone 523
	tone 523
	call delay
	tone 659
	tone 698
	tone 784
	call delay
	tone 659
	tone 698
	tone 784
	call delay
	tone 784
	tone 880
	tone 784
	tone 698
	tone 659
	tone 523
	call delay
	tone 784
	tone 880
	tone 784
	tone 698
	tone 659
	tone 523
	call delay
	tone 523
	tone 392
	tone 523
	call delay
	tone 523
	tone 392
	tone 523
	ret
two_tigers endp
;delay procedure is to delay the SYSTEM - WAIT for < one seconds 
delay proc
	mov     cx, 01h
	mov     dx, 240h
	mov     ah, 86h
	int     15h
	ret
delay endp

hornon proc                  	;activa la horn
    in al, 61h
    or al, 11b
    out 61h, al
    ret
hornon endp

hornoff proc                 	;desactiva la horn
    in al, 61h					;read from a port
    and al, 11111100b
    out 61h, al					;write to a port
    ret
hornoff endp

adjust proc                  	;adjust the horn with the given frequency
    push bp
    mov bp,sp
    mov dx,18      
    mov ax,13353   
	mov bx,[bp + 4]
	div bx
	mov bx,ax  
	mov al,0b6h
	out 43h,al
	;send to port the frequency in two bytes separately.
	mov ax,bx
	out 42h,al 					;send first byte. (parallel port = 378h)
	mov al,ah
	out 42h,al 					;send second byte. (serial port = 3f8h)
	pop bp
	ret
adjust endp

sound proc                      ;activate the horn and place the name of
	call hornon             	;the key.
	mov ax,40h
	mov es,ax
	mov dx,es:[006eh]
	mov ax,es:[006ch]
	add ax,7
	adc dx,0            		;7 units are added to this value
	clic:
		cmp dx,es:[006eh]   	;and compare until they are equal
		jb fini            		;going through a cycle, when they arrive
		ja clic            		;to be the same one leaves the cycle
		cmp ax,es:[006ch]
		ja clic
	fini:
		call hornoff       		;the horn is disconnected and returns.
		ret
sound endp

horn proc                     	;this procedure saves ax and bx in
	push bx              		;the pile to not lose its value, with
	mov ax, bx          		;this calls to fit and sound
	push ax
	call adjust         		;put the frequency in the port.
	pop ax
	pop bx
	call sound           		;activate the speaker and deactivate it.
	ret
horn endp
;end sound

end main
