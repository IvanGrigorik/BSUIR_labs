		IDEAL
		MODEL small
		STACK 100h
		
		DATASEG
hello 		db	"Hello, world!", '$'
exCode	 	db 	0

		CODESEG
Start:
		mov ax, @data
		mov ds, ax

		mov	dx, offset hello
		mov ah, 9

		int 21h
	
Exit:
		mov ah, 4Ch
		mov al, [exCode]
		int 21h
		
END Start