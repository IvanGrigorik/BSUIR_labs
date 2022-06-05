.model small
.stack 100h

.data
strError    db      'Invalid input$'
greeting    db      'Input amount of numbers: $'
strInput    db      'Input a number from -32768 to 32767: $'
strRepeat   db      'Please, repeat input$'
result      db      'Result: $'
_enter      db      10, 13, '$'
array       dw      30 dup (?)
;; GLOBAL BUFFER VAR
i           db      7,8 dup('$')
repeat1     db      ?
repeat2     db      ?
lenght      dw      ?
sign        db      "-$"
number      dw      ?
.code

string_out	macro 	string_to_output
            push 	ax
            push 	dx

            lea 	dx, string_to_output
            mov 	ah, 9
            int 	21h

            pop 	dx
            pop 	ax
endm

input   proc
            mov     ah, 0ah
            mov     dx, offset i
            int     21h
            ret
input endp

atoi    proc
            xor     ax, ax
            xor     dx, dx
            lodsb
            push    ax
            cmp     ax, '-'
            jne     cycle
            dec     cx
            lodsb

cycle:      cmp     ax, '0'
            jb      error
            cmp     ax, '9'
            ja      error
            sub     ax, '0'
            push    ax
            mov     ax, array[di]
            jo      error2
            mul     bx
            jo      error2
            mov     array[di], ax
            jo      error2
            pop     ax
            add     array[di], ax
            jo      error
            cmp     array[di], 32767
            ja      error
            lodsb
        loop    cycle
            pop     ax
            cmp     ax, '-'
            je      minus
            jmp     endParse

error:      pop     ax
            cmp     ax, '-'
            je      minus

error1:     mov     ah, 09h
            lea     dx, _enter
            int     21h
            mov     ah, 09h
            lea     dx, strError
            int     21h
            mov     dx, 1
            jmp     endParse

error2:     pop     ax
            pop     ax
            mov     ah, 09h
            lea     dx, _enter
            int     21h
            mov     ah, 09h
            lea     dx, strError
            int     21h
            mov     dx, 1
            jmp     endParse

minus:      not     array[di]
            add     array[di], 1
            cmp     array[di], -32768
            js      error1
            jmp     endParse
endParse:
            ret
atoi        endp

seach       proc
            mov     repeat1, 0
            mov     cx, lenght

go:         xor     ax, ax

            mov     ax, array[si]
            repne   scasw

            jne     my_ret

            inc     repeat1
            mov     dl, repeat1
            jcxz    my_ret
            jmp     go

my_ret:     inc     si
            inc     si
            ret
seach       endp

itoa  proc
@not_end:         div     bx
            add     dx, '0'
            push    dx
            inc     cx
            xor     dx, dx
            cmp     ax, 0
            jne     @not_end

@end:       pop     bx
            mov     i[si+2], bl
            inc     si
            loop    @end
            mov     i[si+2], '$'
            ret
itoa  endp


;;--MAIN ZONE------------------------------------------------------------------
main:       mov     ax,@data
            mov     ds, ax
            mov     es, ax

start:      string_out  _enter

            mov     array[di], 0
            mov     di, 0

            string_out  greeting

            call    input
            lea     si, i+2
            mov     bx, 10
            xor     cx, cx
            mov     cl, i[1]
            call    atoi
            add     cx, array[di]
            ; If enter unsigned - enter again
            js      start
            xor     cx, cx
            mov     ax, array[di]
            mov     array[di], 0
            mov     lenght, ax
            mov     bx, 30
            cmp     bx, lenght
            ; If length more than 30 or less than 0 - start again
            jl      start
            mov     bx, 0
            cmp     bx, lenght
            je      start
            mov     cx, lenght
            mov     di, 0
            mov     repeat2, 0
            jmp     main1

;just error
repeat:     string_out  _enter
            string_out strRepeat

            dec     di
            dec     di
            mov     array[di], 0

main1:      push    cx
            string_out  _enter
            string_out  strInput
            call    input
            lea     si, i+2
            mov     bx, 10
            mov     cl, i[1]
            call    atoi
            pop     cx
            inc     di
            inc     di
            cmp     dx, 1
            je      repeat
            loop    main1
            ; Just remind array length
            mov     cx, lenght
            mov     repeat1, 0
            xor     si, si

seach1:     push    cx
            mov     di, offset array
            call    seach
            mov     bl,repeat2
            mov     bh,repeat1
            cmp     bh, bl
            jg      swap
            pop     cx
            loop    seach1
            jcxz    exit

swap:       mov    bl, bh
            mov    repeat2, bl
            pop    cx
            mov    number, ax
            loop   seach1
jcxz        exit

exit:       string_out  _enter
            string_out  result
            xor     ax,ax
            add     ax, number
            js      step2
            jns     print

step2:      not     ax
            add     ax, 1
            xor     cx, cx
            mov     cx, ax
            mov     ah, 09h
            lea     dx, sign
            int     21h
            mov     ax, cx

print:     mov     bx, 10
            xor     si, si
            xor     dx, dx
            xor     cx, cx
            call    itoa
            mov     ah, 09h
            lea     dx, i+2
            int     21h
            mov     ah, 4ch
            int     21h
end main

; Векторы перываний хранятся от 0000 до 03FF в начале оп. памяти
; Заносится флаги, CS, IP
; 1 вектор занимает 4 байта. Т.е. вектор 0 - 0000, вектор 1 - 0004, 2 - 0008