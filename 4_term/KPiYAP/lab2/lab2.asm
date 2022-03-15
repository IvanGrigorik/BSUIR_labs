	.model small
	
	;;--MACROS ZONE---------------------------------------------------------------------------------------------------------------------------------
	;;##############################################################################################################################################
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; Basic string output macros
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			string_to_output - -//-
	;; Out: 		output string in console
	;; Registers: 	ah change
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	string_out		macro 		string_to_output
		push 	ax
		push 	dx
		
		lea 	dx, string_to_output
		mov 	ah, 9
		int 	21h
		
		pop 	dx
		pop 	ax
	endm
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; String input by reading every char
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			"string_to_input", "max_size", "current_string_size" variables
	;; Out: 		Filled /\ variables
	;; Registers: 	ax change
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	string_in 		macro		max_size, current_string_size, string_to_input 
		local	 ent, end_in
		
		push 	cx
		push 	si
		push 	dx
		
		xor 	dx, dx
	
		mov 	cx, max_size - 1
		lea 	si, string_to_input
		
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
			mov 	current_string_size, dl
			mov		byte ptr [si], '$'
			
		pop dx
		pop si
		pop cx
	endm
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; Remove substring from string
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			string, string size, substring, substring size
	;; Out: 		reformate string and string size
	;; Registers: 	???????????
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	remove_substr	macro		string, string_size, substring, substring_size
		
	
	endm
	
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; Determine string lenght
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			String
	;; Out: 		cx - string lenght
	;; Registers: 	cx, di
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	string_lenght	macro		string
		local not_end, is_end
		;zxc$ qweq$
		
		push 	si
		
		lea 	si, string
		
		mov 	cx, 0FFFFh
		
		not_end:
			cmp byte ptr [si], '$'
			jz is_end
			
			inc	si
		loop not_end
		
		is_end:
		not 	cx
		
		pop 	si
	endm
	
	
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; Compare strings
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			Two strings
	;; Out: 		Falgs for jumps
	;; Registers: 	none
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	compare_strings	macro		string1, string2
		local testing, not_equal

		push ax
		push di
		push si

		string_lenght string1
		mov ax, cx
		string_lenght string2
		cmp ax, cx
		jne not_equal

		lea		di, string1
		lea 	si, string2

		repe cmpsb
		jnz  not_equal

		not_equal:

		pop si
		pop di
		pop ax
	endm
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; Find substring in the string
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			???????????
	;; Out: 		???????????
	;; Registers: 	???????????
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	find_substr 	macro		string, substring
	local is_end, not_end
		
		push ax
		push cx
		push bx
		push di
		
		lea 	di, string
		lea 	si, substring
		
		string_lenght 	string
		mov 	ax, cx
		string_lenght substring
		mov 	bx, cx
		
		sub 	ax, bx
		jb 		is_end
		
		; Запомнить начало слова
		; В строке дойти до пробела (если его нету - просто сравнить строку string со строкой substring) или $
 		; Запомнить эту позицию
		; Поставить там $ символ
		; Вызвать функцию сравнения с начала слова
		; Если слова равны - выйти и вернуть позицию в каком-либо регистре (предпочтительно si)
		
		cycle:
			mov 
		
		
		
		
		pop di
		pop bx
		pop cx
		pop ax
	
	
	endm
	
	
	;;##############################################################################################################################################
	;;--END OF MACROS AND PROCESSES ZONE------------------------------------------------------------------------------------------------------------
	
	.stack 100h
	
	;;--CONSTANTS AND VARIABLES ZONE----------------------------------------------------------------------------------------------------------------
	.data
		max_string_size 		equ 	200
		cur_string_size 		db 		0
		cur_substring_size		db		0
		
		enter_stirng_message	db 		"Enter your string: $"
		enter_word_message		db		"Enter your substring: $"
		
		out_string_message 		db		"Your string: $"
		out_substring_message 	db		"Your substring: $"
		out_reformat_string		db		"String after reformat: $"
		
		;;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		equals					db		"Equals$"
		;;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		
		ex_code	 				db 		0
		
		end_symbol 				db 		0Dh, 0Ah, '$'
		substring				db 		max_string_size DUP(?)
		string 					db		max_string_size DUP(?)
	;;--END OF CONSTANTS AND VARIABLES ZONE---------------------------------------------------------------------------------------------------------
	
	
	;;--MAIN CODE ZONE------------------------------------------------------------------------------------------------------------------------------
	.code
	
	Start:
		mov 	ax, @data
		mov		ds, ax
	
		mov 	es, ax
	
	;;--MAIN PROCESS--------------------------------------------------------------------------------------------------------------------------------
	;; Remove substring "substring" from string "string"
	 
		string_out			enter_stirng_message
		string_in			max_string_size, cur_string_size, string
		
		string_out			enter_word_message
		string_in			max_string_size, cur_substring_size, substring
		
		string_out 			out_string_message
		string_out			string
		string_out 			end_symbol
		
		string_out			out_substring_message
		string_out 			substring
		string_out 			end_symbol
		
	;; test
		
		compare_strings		string, substring
		jnz mark
		
		string_out			end_symbol
		string_out 			equals
		
		mark:
		
	;; test
		
	;;--EXIT PROCESS--------------------------------------------------------------------------------------------------------------------------------
	;; Just terminate programm with exit code "ex_code"
	Exit: 
		mov 		ah, 4Ch
		mov 		al, [ex_code]
		int 		21h
	
	end Start
	
	;;--END OF MAIN CODE ZONE-----------------------------------------------------------------------------------------------------------------------