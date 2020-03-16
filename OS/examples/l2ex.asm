CODE		SEGMENT	

ASSUME 	CS:CODE, DS:CODE, ES:NOTHING, SS:NOTHING


;PSP_Env =   2Ch     ; смещение до сегмента окружения(environment)
 
    org 100h
	
start:  
	push ds
	pop es
	mov     ax, es:[2ch]
    mov     ds,ax
    xor     si,si
    mov dx,si
_loop:  call    prfx
    call    cputs
nxt:    inc dx ; счетчик строк++
	mov cl, [si+1]
    test cl, cl
    jnz _loop
;выводим путь, откуда запущена прога
    lodsw
_l1:    mov cx, ax
        call    cputs
        loop    _l1
        ret
; выводим ASCIZ-строку
cputs:  lodsb
    or  al,al
    jz  @F
    int 29h
    jmp cputs
@@: ret
; выводим префикс строки
prfx:   mov ax, 0D0Ah   ; новая строка - CR/LF
    call    cputw
; выводим номер строки
    mov ax, dx
    aam
    xchg    ah, al
    or  ax, '00'
    call    cputw
; выводим пробел и двоеточие
    mov ax,' :'
; выводит 2 байта из AX
cputw:  int 29h
    xchg    ah, al
    int 29h
    ;ret
	XOR		AL, AL
		MOV		AH, 4CH
		INT		21H
		
	CODE		ENDS
END 		START