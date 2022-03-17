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
			
			cmp 	al, '$'
			je 		end_in
			
			mov		[si], al
			inc 	si
			
		loop 	ent
		
		end_in:
			mov		byte ptr [si], '$'
			mov 	current_string_size, dl
			
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
	string_length	macro		string
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
		push cx

		string_length string1
		mov ax, cx
		string_length string2
		cmp ax, cx
		jne not_equal

		lea		di, string1
		lea 	si, string2

		repe cmpsb
		jnz  not_equal

		not_equal:

		pop cx
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
		
		string_length 	string
		mov 	ax, cx
		string_length substring
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
	
	;;--MACROS--------------------------------------------------------------------------------------------------------------------------------------
	;; Find substring in the string
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	;; In: 			???????????
	;; Out: 		???????????
	;; Registers: 	???????????
	;;----------------------------------------------------------------------------------------------------------------------------------------------
	word_end		macro		string
		local word_start, end_symbol

		mov		cx, 0FFFFh
		lea 	si, string
		
		word_start:
			cmp		byte ptr [si], ' '
			jz		end_symbol
			cmp 	byte ptr [si], '$'
			jz		end_symbol
			
			inc si
			
		loop word_start
		
		end_symbol:
			not 	cx
		
	endm
	
	
	;;##############################################################################################################################################
	;;--END OF MACROS AND PROCESSES ZONE------------------------------------------------------------------------------------------------------------
	
	.stack 100h
	
	;;--CONSTANTS AND VARIABLES ZONE----------------------------------------------------------------------------------------------------------------
	.data
	
		max_string_size 		equ 	200
		string 					db		max_string_size DUP(?)
		word_to_find			db 		max_string_size DUP(?)
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
		
		string_out 			end_symbol
		string_out			enter_word_message
		string_in			max_string_size, cur_substring_size, word_to_find
		string_out 			end_symbol
		
		string_out 			out_string_message
		string_out			string
		string_out 			end_symbol
		
		string_out			out_substring_message
		string_out 			word_to_find
		string_out 			end_symbol
		
	;; test
		
		cld
		
		lea si, string
		lea di, word_to_find
		
		
		;REPE 	CMPSB
		;JNZ  	not_same
		
		
		; No Yes Yes$
		
		find_word:
			
			push 	si
			
			
			word_end	[si]
			
			cmp		byte ptr [si], '$'
			jz		string_end
			
			mov 	byte ptr [si], '$'
			pop 	si
			
			compare_strings	word_to_find, [si]
			
			jz word_delete
			
			; There cx must be equal to word length in string
			
			to_space:
				inc si
			loop to_space		; to '$'
			
			mov 	byte ptr [si], ' '
			inc 	si
		loop find_word
			
		;++
		word_delete:
		; cx there must be equal to word length
		; si there - beginning of a word
		
		; Инкрементируем cx, чтобы di в будущем указывало на начало нового слова (ситуации, если di будет равен $ не боимся, ибо для этого вообще другая обработка)
		; Устанавливаем di в si+cx
		; заходим в цикл (бесконечный с безусловным джампом) и смотрим, чему равен di
		; Если di равен $ - выходим из цикла и свапаем его с si
		; Если не равен - меняем (mov) si на di; inc di; inc si
		
			push si
		
			string_length [si]
			add		cx, 1	; word + symbol to space (' ')
			mov 	di, si
			add 	di, cx
			
			delete_process:
				cmp		byte ptr [di], '$'
				jz 		delete_process_end
				
				mov 	al, [di]
				mov 	[si], al
				
				inc 	si
				inc 	di
			
			jmp delete_process
		
			delete_process_end:
			mov 	al, [di]
			mov 	[si], al
			
			pop si
		jmp find_word
		;++
		
		string_end:
		; We have 'si' at the top of stack
			pop 	si
			compare_strings		word_to_find, [si]
			jnz		Exit
		
		delete_last_word:
			cmp		si, 00
			jz		one_word
			
			dec 	si
			
			one_word:
			mov 	byte ptr [si], '$'
	
			
		
	;;--EXIT PROCESS--------------------------------------------------------------------------------------------------------------------------------
	;; Just terminate programm with exit code "ex_code"
	Exit: 
			lea 	dx, out_reformat_string
			mov 	ah, 9
			int 	21h
			lea 	dx, string
			int 	21h
			lea 	dx, end_symbol
			int 	21h
			
			
			
			
		mov 		ah, 4Ch
		mov 		al, [ex_code]
		int 		21h
	
	end Start
	
	;;--END OF MAIN CODE ZONE-----------------------------------------------------------------------------------------------------------------------