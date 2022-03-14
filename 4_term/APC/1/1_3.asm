.model small
.stack 100h

.data

Error_Write db "Write error!",0Dh,0Ah,'$'
Error_Read db "Read error!",0Dh,0Ah,'$'
Information db "Byte sent: $"
Data_Byte db 'A'
Data_Byte2 db ?
           
.code
           
;#####################################################################################################
; INITIALIZE FIRST PORT
;#####################################################################################################
Init_COM1 proc
; set 7 bit = 1 to 3FB -- 3F8, 3F9 able to control speed
    mov al,80h  				; 7bit = 1
    mov dx,3FBh 				; Set LCR
    out dx,al					; Set setting
	
    mov dx,3F8h 				; COM1 number
    mov al,00h 					; No interrupt
    out dx,al					
    mov al,0Ch					; Set frequency
    mov dx,3F9h					; setting data
    out dx,al					; transfer frequency 

; set in Modem Control Register required bytes
; RTS, DTR, 3 bit
    mov dx,3FCh ; 
    mov al,00001011b			; set frequency 
    out dx,al
    
    mov dx,3F9h					; Settings data
    mov al,0					; 
    out dx,al					; Set
    ret
Init_COM1 endp


;#####################################################################################################
; TEST FIRST PORT
;#####################################################################################################
IsWrite_COM1 proc
    xor al,al
    mov dx,3FDh 				; portout function
    in al,dx
    test al,10h 				; check 5 = 1 setted
    jnz NoWRite 				; If we cant write ... @099
    ret
IsWrite_COM1 endp

;Function-support 
NoWRite proc					
   mov ah,9
   mov dx,offset Error_Write	;@099 ... - also show error message!
   int 21h
   ret 
NoWRite endp

;#####################################################################################################
; TEST SECOND PORT
;#####################################################################################################
IsRead_COM2 proc
    xor al,al
    mov dx,3FDh
    in al,dx
    test al,10b 				; check bit setted
    jnz NoRead 					; bit = 0, some error in port
    ret
IsRead_COM2 endp

NoRead proc
   mov ah,9
   mov dx,offset Error_Read
   int 21h
   ret 
NoRead endp

;#####################################################################################################
; LOAD BYTE TO THE FIRST PORT
;#####################################################################################################
Send_Byte proc
    mov dx,3F8h
    mov al,Data_Byte
    out dx,al					; load data in COM1-port
    ret
Send_Byte endp

;#####################################################################################################
; READ BYTE FROM SECOND PORT
;#####################################################################################################
Read_Byte proc
    mov dx,3F8h
    in al,dx
    mov Data_Byte2,al 			; load byte from COM1-port
    ret
Read_Byte endp

Exit proc
    mov ax,4C00h
    int 21h
    ret
Exit endp

;#####################################################################################################
; MAIN FUNCTION
;#####################################################################################################
start:
    mov ax,@data
    mov ds,ax
    call Init_COM1
    call IsWrite_COM1
    call Send_Byte
    mov al,2 
    call IsRead_COM2
    call Read_Byte
    mov dx,offset Information
    mov ah,9
    int 21h
    mov ah,02h
    mov dl,Data_Byte2
    int 21h 
    call Exit
   
end start