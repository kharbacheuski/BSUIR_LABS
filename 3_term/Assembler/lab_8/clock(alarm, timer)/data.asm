.data
clock_title db "SMD Clock","$"
show_clock_str db "Show Clock","$"
set_alarm_str db "Set Alarm","$"
timer_str db "Timer","$"
stopwatch_str db "Stopwatch","$"
start_vga_str db "  Start ","$"
stop_vga_str db "  Stop  ","$"
reset_vga_str db " Reset ","$"
quit_str db "Leave","$"
back_str db "Back","$"
back_vga_str db "    Back    ","$"
wait_respond_str db "Waiting for mouse respond . . .","$"
wait_respond_vga_str db "      Waiting for mouse respond . . .   ","$"

arr label byte
max_length db 20
act_length db ?
input db 20 dup("$")

ten db 10
quotient db ?
remainder db ?

mouse_row dw ?
mouse_col dw ?

analog_str db  "Analog","$"
digital_str db "Digital","$"

is_show_clock db 0b
is_analog db 0b
is_digital db 0b

is_set_alarm db 0b
is_timer db 0b
is_stopwatch db 0b
is_exit db 0b

; for clock
start_row dw 0
start_col dw 0

color db 0
option_color db 3fh
clock_color db 0eh

row_1 dw 0
row_2 dw 0
row_3 dw 0
col_1 dw 0
col_2 dw 0
col_3 dw 0

time_buf db "00:00:00$"		;time buffer hr:min:sec, "ahal:ahal:ahal" al = first digit, ah = second digit
date_buf db "00/00/0000$"		
alarm_buf db "00:00$"
timer_buf db "00:00:00$"

day db ?
mon db 10,13,"Monday","$"
tue db 10,13,"Tuesday","$"
wed db 10,13,"Wednesday","$"
thu db 10,13,"Thursday","$"
fri db 10,13,"Friday","$"
sat db 10,13,"Saturday","$"
sun db 10,13,"Sunday","$"

is_24 db 0

old_vector dw ?, ?
new_vector dw ?, ?

input_alarm_str db "Set the alarm with the time in format (hh:mm) : ","$"
alarm_ok_str db "Alarm is set successfully$"
alarm_fail_str db "Alarm is set unsuccessfully$"
alarm_cancel_ok_str db "Alarm is cancel successfully$"
alarm_on_str db "Alarm is set at the time : $"
alarm_cancel_str db "Cancel alarm please enter '-'$"
alarm_off_str db "Alarm is not set yet. $"
alarm_hh db ?
alarm_mm db ?
is_alarm_set db 0b		;false
invoker_alarm db 0b

timer_hh db ?
timer_mm db ?
timer_ss db ?
timer_set_str db "Timer countdown from ","$"
input_timer_str db "Set the timer with the time in format (hh:mm:ss) : ","$"
timer_ok_str db "Timer is set successfully$"
timer_fail_str db "Timer is set unsuccessfully$"
edit_vga_str db "    Edit    ","$"
is_edit db 0b
is_timer_exit db 0b
simulate_timer_hh db 0
simulate_timer_mm db 0
simulate_timer_ss db 0
first_timer_sec db 0b
invoke_timer_alarm db 0b

temp_sec db ?

simulate_minute db 0
simulate_sec db 0
simulate_milisec db 0
first_sec db 1b
is_sec_pass db 0b

is_start db 0b
is_reset db 0b

is_timer_start db 0b
is_timer_reset db 0b


;analog data	
temp_sec_ana db ?
is_sec_pass_ana db 0b

analog_ss db 0
analog_mm db 0
analog_hh db 0
inner_analog_hh dw 0
hour_in_60 dw 0

sec_hand_color db 3
min_hand_color db 7
hour_hand_color db 10
min_hand_start_deg dd 89

radius dd 0
adjust_x dd 0
adjust_y dd 0
x dd 0
y dd 0
	
deg_180 dd 180.0	

theta dd 90.0
deg_step dd 0.01
hr_deg_step dd 30.0
sec_deg_step dd 6.0

min_hand_step dd 0.1
;analog end data