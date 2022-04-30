org 100h

;;#############################################################################
;;---------MACRO---------------------------------------------------------------
;;#############################################################################
%macro      INPUT_STR   2 ; %1 is input buffer, %2 is buffer size
            push        bx

            mov         ah, 0x01
            mov         cx, %2-1

%%input:    mov         bx, cx                  ; bx is -cx
            neg         bx

            int         0x21                    ; read byte from stdin

            cmp         al, 0x0d                ; '\r'
            jz          %%end
            cmp         al, '$'
            jz          %%end

            ; [%1-cx+%2-1] is forbidden
            mov         [%1+bx+%2-1], al
            loop        %%input
            inc         bx                      ; not overwrite last byte by '$'

%%end:      mov         [%1+bx+%2-1], byte '$'

            pop         bx
%endmacro


%macro  print 1
            push        ax
            push        dx
            lea         dx, %1
            mov         ah, 09h
            int         21h
            pop         dx
            pop         ax
%endmacro

%macro      print_number    0
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
%endmacro

;1 - word, 2 - container
%macro  str_size 2
            push    cx

            mov     cx, 0ffffh
            lea 	si, %1

word_start: cmp		byte [si], ' '
            jz		end_symbol
            cmp 	byte [si], '$'
            jz		end_symbol

            inc si

            loop word_start

end_symbol: not 	cx
            mov     [%2], cx

            pop     cx
%endmacro

; 1 - filepath, 2 - file descriptor, 3 - var to error
%macro      open_file   3
openFile_start:
            lea         dx, %1
            mov         al, 0
            mov         ah, 3Dh
            int         21h
            jc          find_error          ;   if any errors
            mov         [fd], ax
            jmp         open_f_end

find_error: cmp         ax, 02h
            je          no_file
            cmp         ax, 03h
            je          path_err
            cmp         ax, 05h
            je          access_err

no_file:    print       no_file_msg
            mov         word [%3], 1
            jmp         open_f_end

path_err:   print       path_msg
            mov         word [%3], 1
            jmp         open_f_end

access_err: print       access_msg
            mov         word [%3], 1
            jmp         open_f_end
open_f_end:
%endmacro

; 1 - dir, 2 - new position, 3 - fd
%macro      chpos       3
            mov         ah, 42h
            mov         al, 1
            mov         bx, [fd]
            mov         dx, %2
            mov         cl, 0
            cmp         cl, %1
            jz          %%_change

            neg         dx
            mov         cx, 0FFFFh
            jmp         %%_int_ch

%%_change:  mov         cx, 0
%%_int_ch:  int         21h

%endmacro


;1 - string to find in line, 2 - fd
%macro      checkline   1
            jmp         _start

found_subs: mov         bx, [fd]      ;bx, [%2]
            mov         cx, 1
            mov         ah, 3Fh
            lea         dx, char
            int         21h

            cmp         ax, 0
            jz          subs
            mov         al, [char]
            cmp         al, ' '
            jz          subs
            cmp         al, 9
            jz          subs
            cmp         al, 10
            jz          subs
            cmp         al, 13
            jz          subs
            jmp         no_subs

subs:       mov         byte [is_substring], 1
            jmp         _check_end
no_subs:    jmp         _check_for
            jmp         _check_end


; ---PROCESS START---
_start:     lea         di, %1
            mov         byte [is_substring], 0
            mov         word [file_end], 0

_check_for: mov         bx, [fd]          ; read single char
            mov         cx, 1
            lea         dx, char
            mov         ah, 3Fh
            int         21h

            ; if end of file
            cmp         ax, 0
            je          _end_find

            mov         al, 10      ; to check '\n'
            cmp         byte [char], al
            je          _check_end

            mov         al, 13      ; to check '\r'
            cmp         byte [char], al
            je          _check_end

            mov         al, [di]
            cmp         al, byte [char]
            jne         _start

            inc         di
            mov         al, [di]
            cmp         al, '$'
            je          found_subs

            jmp         _check_for

_end_find:  mov         word [file_end], 1
            jmp         _check_end

_check_end:
%endmacro

%macro      skip_line 0
            inc         word [count]

;skip_start: mov         ah, 42h
;            mov         al, 0
;            mov         bx, [fd]
;            mov         cx, [line_beg_dx]
;            mov         cx, [line_beg_ax]
;            int         21h

_skip_loop: mov         bx, [fd]
            mov         cx, 1
            mov         ah, 3Fh
            lea         dx, char
            int         21h

; Comparing zone
            cmp         ax, 0                       ; EOF
            jz          fl_end
            ;mov        al, 10
            cmp         byte [char], 10             ; '\n'
            jz          cycle_end
            ;mov        al, 13
            jmp         _skip_loop

cycle_end:


fl_end:     mov         byte [file_end], 1

skip_end:
;
%endmacro


;;#############################################################################
;;--END OF MACRO---------------------------------------------------------------
;;#############################################################################

;;#############################################################################
;;--DATA-----------------------------------------------------------------------
;;#############################################################################
section .bss

filepath        resb    50
string          resb    50
fd              resw    5
error           resw    1
file_end        resw    1

section .data

message         db      "Hello world$"
inp_msg         db      "Enter string: $"
new_line        db      10, 13, "$"
word_size       db      0

path_msg        db      "Invalid path!$"
access_msg      db      "Invalid access!$"
no_file_msg     db      "No such file!$"


line_beg_dx     db      0
line_beg_ax     db      0

is_substring    db      0
char            db      0

count           dw      0
;;#############################################################################
;;--END OF DATA----------------------------------------------------------------
;;#############################################################################

;;#############################################################################
;;--CODE-----------------------------------------------------------------------
;;#############################################################################
section .text
            mov         cl, es:[80h]
            cmp         cl, 0
            je          _exit       ;if no args - exit

            mov         si, 82h
            xor         di, di
            dec         cl          ; to skip .com

;; -- Cycle to get cmd params
get_params: mov         al, es:si
            mov         [filepath + di], al
            inc         di
            inc         si
            loop        get_params
            mov         byte [filepath + di], 0

            ; --FAST DB--
            ; -- mov         byte [filepath + di], '$'
            ; -- print       filepath

            print       inp_msg
            INPUT_STR   string, 50

            ;print       string
            ;print       new_line

            str_size    string, word_size
            ;mov         ax, [word_size]
            ;print_number
            open_file   filepath, fd, error
            cmp         word [error], 1
            jz          _exit

            ; -- There start word counting process

check_line: chpos       0, 1, fd
            chpos       1, 1, fd

            checkline   string
            cmp         word [file_end], 1
            jz          count_end

            cmp         byte [is_substring], 1
            jnz         check_line

            chpos       -1, 1, fd
            skip_line
            jmp         check_line
count_end:
            ; -- There end word counting process
            print       new_line
            mov         ax, [count]
            print_number

close_file: mov         ah, 3Eh
            mov         bx, fd
            int         21h
_exit:

.exit:      ret
;;#############################################################################
;;--END OF CODE----------------------------------------------------------------
;;#############################################################################