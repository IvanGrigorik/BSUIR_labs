.model small
.stack 100h

.data

Error_Write db "Write error!",0Dh,0Ah,'$'
Error_Read db "Read error!",0Dh,0Ah,'$'
Information db "Byte sent: $"
           
.code

jmp start

;#####################################################################################################
; WORK WITH TRANSMITTED PORT
;#####################################################################################################
Init_COM1 proc			
   xor ax,ax					; Clear ax register 
   mov al,10100011b				; Set transfer frequency 
   mov dx,0						; Initialize port name
   int 14h				
   ret            
Init_COM1 endp

IsWrite_COM1 proc		
   mov al,'A'					; Initialize symbol
   mov ah,1						; Write symbol to the port
   mov dx,0						; Initialize port name
   int 14h				
   test al,80h					; Test DSR
   jnz NoWRite					; If we cant write ... @099
   ret 
IsWrite_COM1 endp

; Support function
NoWRite proc
   mov ah,9
   mov dx,offset Error_Write	;@099 ... - show error message
   add dx,2
   int 21h
   ret 
NoWRite endp

;#####################################################################################################
; WORK WITH RECIVED PORT
;#####################################################################################################
IsRead_COM2 proc				; Read in the second port
    mov ah,2					; Read symbol
    mov dx,1					; Initialize port name
    int 14h					
    test al,80h					; Test RTS
    jnz NoRead					; If we cant write ... @099
    ret
IsRead_COM2 endp

NoRead proc
   mov ah,9
   mov dx,offset Error_Read		;@099 ... - also show error message!
   add dx,2
   int 21h
   ret 
NoRead endp

;#####################################################################################################
; OUTPUT BYTE
;#####################################################################################################
Output proc
   mov ah,02h					; Read byte from secong port
   mov dl,al					; And show
   int 21h
   ret
Output endp

;#####################################################################################################
; EXIT FUNCTION
;#####################################################################################################
Exit proc
    mov ax,4C00h			
    int 21h
    ret
Exit endp

;#####################################################################################################
; MAIN FUNCTION
;#####################################################################################################
start:
   call Init_COM1
   call IsWrite_COM1
   mov al,'e'
   call IsRead_COM2
   ;push ax
   
   ;mov ah,9
   ;mov dx,offset Information
   ;add dx,2
   ;int 21h
           
   ;pop ax        
   call Output
   call Exit

end start