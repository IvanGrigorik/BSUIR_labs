.model small
.stack 100h
.data
    maxCLLen equ 127
    cmd_size db ?
    dirPath db maxCLLen dup(0)

    DTAsize equ 2Ch
    DTAblock db DTAsize dup(0)

    startStr db "Program is started$", 13, 10
    endStr db "Program is ended", '$', 13, 10
    badDirStr db "Open directory error. Error code: ", '$' ,13, 10
    reallocErrStr db "Error relocation memory. Error code: ", '$' ,13, 10
    runErrStr db "Error running other program. Error code: ", '$', 13, 10
    clError db "Wrond command line arguments", '$', 13, 10
    endl db 10, 13, '$'

                                            ; EXEC Parameter Block
    EPBstruct 	dw 0                        ; 0 - используется текущее окружение
    			dw offset line, 0           ; Параметры программы
    			dw 005Ch, 0, 006Ch, 0		; Адреса FCB (File control block).
    			; 005Ch - смещение первого блока psp
                ; 0 - первый блок psp
                ; 006Ch - смещение второго блока psp
                ; 0 - второй блок psp


    line        db 0
    lineStr     db maxCLLen - 1 dup(0), 0dh

    exeStr      db "*.exe", 0

    DataLen     =   $ - cmd_size


print macro str
  	mov     ah, 09h
	mov     dx, offset str
	int     21h
endm

println macro str
    print   str
    print   endl
endm

printErrCode macro
	add al, '0'
	mov dl, al
	mov ah, 06h
	int 21h
endm

.code
start:
	mov ah, 4Ah                                                 		;сокращаем выделенную программе память до минимума
	mov bx, (CodeLen / 16 + 1) + (DataLen / 16 + 1) + 32 			    ;требуемый размер
	int 21h
	jnc noReallocErr                           				            ;если ошибок не произошло
	print reallocErrStr
	printErrCode
	print endl
	jmp endProgramm

    noReallocErr:
    mov ax, @data
    mov ds, ax
    mov es, ax

	println startStr
    call readCL
    call openDir

	call findFirstEXE
	call run

    runLoop:
	print endl
	call findNextEXE
	call run
	jmp runLoop

    endProgramm:
    print endl
	print endStr
	mov ah, 4Ch                 ;завершение программы
	int 21h

openDir proc
    mov ah, 3Bh
    lea dx, dirPath
    int 21h			;открываем нужный каталог
    jnc openDirOK
    print endl
	print badDirStr
	printErrCode
	print endl
	jmp endProgramm
	openDirOK:
    ret
endp

readCL proc
    mov ah, 62h
    int 21h
    mov ds, bx			;сегментный адрес PSP выполняющей программы

    mov si, 80h			;устанавливаем на начало командной строки
    lea di, dirPath		;путь к каталогу
    lodsb

    skipSpacesCL:		;пропускаем первый пробел
    lodsb
    cmp al, ' '
    je skipSpacesCL

    cmp al, 0dh
    je errorCL

    mov es:di, al
    inc di

    readCLLoop:
    lodsb
    cmp al, ' '
    je endReadCL
    cmp al, 0dh
    je endReadCL
    mov es:di, al
    inc di
    jmp readCLLoop

    errorCL:
    mov ax, @data
    mov ds, ax
    pop ax
    println clError
    jmp endProgramm

    endReadCL:
    mov ax, @data
    mov ds, ax
	ret
endp

run proc
	mov ah, 4Bh				            ; загрузить и выполнить
	lea bx, EPBstruct
	mov dx, offset DTAblock + 1Eh			;имя файла из DTA
	int 21h

	jnc runOK
	print runErrStr
	printErrCode
    print endl
    jmp endProgramm
    runOK:
	ret
endp

installDTA proc
	mov ah,1Ah                              ; устанавливаем область DTA
    lea dx, DTAblock
    int 21h
    ret
endp

findFirstEXE proc
	call installDTA

    mov ah,4Eh
    xor cx,cx               		; атрибут файла для сравнения
    lea dx, exeStr                  ; адрес строки с именем файла
    int 21h

    jnc findFirstEXEOK
    jmp endProgramm
    findFirstEXEOK:
	ret
endp

findNextEXE proc
	call installDTA

	mov ah, 4Fh                   ;поиск следующего совпадающего файла
    lea dx, DTAblock
    int 21h

    jnc findNextEXEOK
    jmp endProgramm
    findNextEXEOK:
	ret
endp

CodeLen = $ - start

end start