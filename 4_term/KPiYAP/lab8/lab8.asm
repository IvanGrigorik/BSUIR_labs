.model tiny
.386 	; #286

.code
org 100h

start:		jmp 		landing
			buffer_1	db			20
			buffer_2	db			7
			cmd_buff	db			20 dup (?)
			
			;; Errors messages
			cmd_msg		db			"Wrong cmd parameters!$"
			time_msg	db			"Wrong time input!$"


			; Time vars
			hours		db			0
			minutes		db			0
			msg_len		dw			0
			alarm		db			" Alarm!!!"
			
			; Interrupts
			old_int 	dd 			0
			


clear proc near
			mov 	ah,0
			mov 	al,3
			int 	10h  
			mov 	ah,02
			mov 	dh,0
			mov 	dl,0
			int 	10h
			ret
clear endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; #############################################################################
; --NEW INTERRUPTION-----------------------------------------------------------
; #############################################################################
print_number    macro     
local @convert, @display 
            push    ax
            push    bx
            push    cx
            push    dx
            push    di

            mov     cx, 10          ; cx - base number
            xor     di, di          ; di - digits in number

            cmp     ah, 0
    @convert:
            xor     dx, dx
            div     cx
            add     dl, '0'
            inc     di
            push    dx
            or      ax, ax
            jnz     @convert

    @display:
            pop     dx              ; dl = symbol
            mov     ah, 02h
            int     21h
            dec     di              ; repeat while di<>0
            jnz     @display

            pop     di
            pop     dx
            pop     cx
            pop     bx
            pop     ax
endm


alarm_clock proc far
			push ds
			push cs
			pop ds

			pusha
			
			pushf                 
			call dword ptr cs:old_int        
			
			; There is my logic
			
			mov ah,03h
			mov bh,0
			int 10h 
			xor si, si
			mov dl, 0
out_cycle:
            mov ah,0ah
            mov al,alarm[si]
            mov cx,1
            int 10h
            inc si
            
			mov ah,02h
            mov bh,0
            inc dl
            int 10h
			cmp si, 9
			
			jne out_cycle
		
		
		; Clear screen after some time
			
			mov		cx, msg_len
			mov     dx, 4240h
			mov     ax, 8600h
			int     15h
			
			call 	clear
			
			
			
        ; End of logic
	
			popa
			pop ds       
			iret     
alarm_clock endp

not_resident:

print 	macro			str
			mov			ah, 09h
			lea			dx, str
			int 		21h
endm

atoi 	proc 			near
			xor 		di,di
			xor 		ax,ax
			xor 		bx,bx
			xor 		dx,dx
			
_parse:		mov 		al, buffer_2[di]
			
			inc 		di     
			cmp 		al, '$'
			je 			end_atoi
			
			push 		ax
			mov 		ax, bx
			mov 		bx, 10
			mul 		bx
			mov 		bx, ax
			pop 		ax
			
			sub 		al, '0'
			add 		bl, al
			jmp 		_parse
			
end_atoi:	ret
atoi 	endp

landing:	
			xor 		cx, cx
			xor 		di, di
			mov			si, 80h

get_cmd:	mov			al, [si]
			inc 		si
			cmp			al, 0
			jz			end_get
			mov			buffer_1[di], al
			inc			di
			jmp			get_cmd
			
end_get:	xor 		si, si
			xor 		di, di
			
find_ret:	mov			al, buffer_1[si]
			cmp			al, 13						; cmp buffer start with carriage return
			jz			find_end
			inc 		si
			jmp 		find_ret

find_end:	mov			buffer_1[si], byte ptr '$'

; Parse cmd process
			xor			di, di
			xor			si, si
			mov			dx, 4

; Parse hours
parse_hour: mov			al, cmd_buff[si]
			inc 		si
			cmp			al, byte ptr ' '
			jz			hour_end
			cmp 		al, byte ptr ':'
			jz 			hour_end
; Compare to correct input
			cmp			dx, 0
			jz			wrong_cmd
			cmp			al, byte ptr '0'
			jb 			wrong_cmd
			cmp			al, byte ptr '9'
			ja 			wrong_cmd
; Load to buffer
			mov			buffer_2[di], al
			inc 		di
			mov			buffer_2[di], byte ptr '$'
			dec			dx
			jmp			parse_hour

hour_end:	call 		atoi
			cmp			bx, 23				; Max hours
			ja			wrong_time
			mov			hours, bl
			
; Parse minutes
			xor			di, di
			mov			dx, 4
			mov			al, cmd_buff[si]
			cmp			al, byte ptr ' '
			jz 			wrong_cmd
			
minute:		mov			al, cmd_buff[si]
			inc 		si
	
			cmp 		al, byte ptr ' '
			jz 			minute_end
			
			cmp			dx, 0
			jz 			wrong_cmd
			cmp 		al, byte ptr '0'
			jb 			wrong_cmd
			cmp			al, byte ptr '9'
			ja 			wrong_cmd
			mov			buffer_2[di], al
			inc 		di
			mov			buffer_2[di], byte ptr '$'
			dec 		dx
			jmp			minute
			
minute_end:	call 		atoi
			cmp			bx, 59
			ja			wrong_time
			mov			minutes, bl

; Parse duration
			xor 		di, di
			mov			dx, 4
			mov			al, cmd_buff[si]
			cmp			al, byte ptr ' '
			jz			wrong_cmd
			
duration:	mov			al, cmd_buff[si]
			inc			si
			cmp			al, byte ptr '$'
			jz 			dur_end
			
			cmp			dx, 0
			jz 			wrong_cmd
			cmp 		al, byte ptr '0'
			jb 			wrong_cmd
			cmp 		al, byte ptr '9'
			ja 			wrong_cmd
			
			mov			buffer_2[di], al
			inc 		di
			mov			buffer_2[di], byte ptr '$'
			dec 		dx
			jmp 		duration
			
dur_end:	call 		atoi

			mov			msg_len, bx
			mov			ax, msg_len
			print_number

			mov			ax, 000Fh
			mov			dx, msg_len
			mul			dx
			mov			msg_len, ax
			
			mov			ax, msg_len
			print_number
			
; Set alarm clock
			xor			ax, ax
			mov			al, hours	
			mov			bl, 10
			div			bl
			mov			ch, al
			mov			cl, ah
			xor 		ax, ax
			mov			al, ch
			mov 		bl, 16
			mul 		bl
			add			al, cl
			mov			hours, al
			
			xor 		ax, ax
			mov			al, minutes	
			mov			bl, 10
			div			bl
			mov			ch, al
			mov			cl, ah
			xor 		ax, ax
			mov			al, ch
			mov 		bl, 16
			mul 		bl
			add			al, cl
			mov			minutes, al
			
			; May be add seconds atthe future
			
			; Delete last alarm
			mov			ah, 7
			int 		1Ah
			
			; Set alarm
			mov			ch, hours
			mov			cl, minutes
			mov			dh, 00	; 00000000b
			mov			ah, 6
			int 		1Ah
			
			; Load resident
			cli
			
			mov			ah, 35h
			mov			al, 4Ah
			int 		21h
			mov			word ptr cs:old_int, bx
			mov			word ptr cs:old_int+2, es
			
			; Set inter. address.. 
			mov			ah, 25h
			; for 4Ah inter. ...
			mov			al, 4Ah
			; to my procedure.
			lea			dx, alarm_clock
			int 		21h
			
			sti
			
			jmp _res_end


wrong_cmd:	print		cmd_msg
			jmp			_end

wrong_time: print 		time_msg
			jmp 		_end

; Default end (some errors)
_end:		mov 		ah, 4Ch
			int 		21h
			
; End with loaded resdent
_res_end:	lea			dx, not_resident
			int 		27h
end start