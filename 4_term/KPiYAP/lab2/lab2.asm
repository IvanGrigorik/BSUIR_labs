	.model small
	.stack 100h
	
	.data
		
		;;	TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE 
		message db "hello", 0Dh, 0Ah, '$'
		;;	TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE TEST ZONE 
		
		
		
		max_string_size 		equ 	200
		cur_string_size 		db 	0
		
		enter_stirng_message	db 		"Enter your string: $"
		enter_word_message		db		"Enter your word: $"
		
		output_strin_message 	db		"Your string: $"
		
		exCode	 				db 		0
		
		end_symbol 				db 		0Dh, 0Ah, '$'
		string 					db		max_string_size DUP(?)
	
	.code
	
	Start:
		mov 	ax, @data
		mov		ds, ax
	
	;;-----------------------------------------------------------------
	;; Basic string output macros
	;;-----------------------------------------------------------------
	;; In: 			dx - output string effective address
	;; Out: 		output string in console
	;; Registers: 	ah change
	;;-----------------------------------------------------------------
	string_out		macro 	
		push 	ax
		
		mov 	ah, 9
		int 	21h
		
		pop 	ax
	endm
	
	;;-----------------------------------------------------------------
	;; String input by reading every char
	;;-----------------------------------------------------------------
	;;
	;;
	;;
	;;-----------------------------------------------------------------
	string_in 		macro
		push cx
		push si
		push dx
		
		xor dx, dx
	
		mov 	cx, max_string_size - 1
		lea 	si, string
		
		ent: 
			mov 	ah, 1
			int 	21h
			inc 	dx
			
			cmp 	al, 13
			je		end_in
			
			mov		[si], al
			inc 	si
			
			loop 	ent
		
		end_in:
			mov 	cur_string_size, dl
			mov		byte ptr [si], '$'
			
		pop dx
		pop si
		pop cx
	endm
	
	
		mov 		dx, offset enter_stirng_message
		string_out
		string_in
		
		
		
		
		mov 		dx, offset end_symbol
		string_out
		mov 		dx, offset output_strin_message
		string_out
		mov 		dx, offset string
		string_out
		
	Exit: 
		mov 		ah, 4Ch
		mov 		al, [exCode]
		int 		21h
	
	end Start