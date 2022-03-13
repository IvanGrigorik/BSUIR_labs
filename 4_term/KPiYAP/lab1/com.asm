	.model tiny
	
	.data
	
	hello 	db 	"Hello world!", 0Dh, 0Ah, '$'

	.code
	org 256

Start:
	
	mov dx, offset hello	; Transfer hello message to data
	mov ah, 9 				; Signal to DOS 
	int 21h					; Hey dos, check some data
	
	
	mov ax, 4C00h
	int 21h
	; Return to start

end Start					; End programm