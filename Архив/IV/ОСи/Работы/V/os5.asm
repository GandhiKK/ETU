Astack segment stack
    dw 256 dup(?)
Astack ends

data segment
    load_msg db 'Resident Interrupt Handler was loaded', 13, 10, '$'
	alrd_load_msg db 'Resident Int Handler is already loaded', 13, 10, '$'
    unload_msg db 'Resident interrupt handler was unloaded', 13, 10, '$'
data ends

code segment
    assume cs:code, ds:data, ss:Astack
rout proc far
    jmp rout_start
	signature dw 4321h ;сигнатура, которая идентифицирует резидент
	keep_psp dw ?
    keep_ip dw ?
    keep_cs dw ? 		
	sign db ?
;	keep_ax dw ?
;	keep_ss dw ?
;	keep_sp dw ?
;	keep_bp dw ?
;	rout_stack db 128 dup(?)
	rout_start:
;	mov keep_ax, ax
;	mov keep_sp, sp
;	mov keep_ss, ss	
;	mov keep_bp, bp
;	mov ax, seg rout_stack
;	mov ss, ax
;	lea ax, rout_stack
;	mov sp, ax
;	add sp, 128
;	mov bp, sp
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push es
    push ds
	mov ax, seg sign
	mov ds, ax
	in al, 60h

	irpc case, 2468A ;клавиши нечетных цифр выводят !
	cmp al, 0&case&h
	je type_M			
	endm
	irpc case, 3579 ;клавиши четных цифр выводят ?
	cmp al, 0&case&h
	je type_Z			
	endm
	irpc case, 012345 ;qwerty заменяется на 012345
	cmp al, 1&case&h
	je type_qy&case&			
	endm

	cmp al, 2Eh ;по клавише c включается CapsLk и печатается пробел
 	je on_CL	
	cmp al, 30h ;по клавише b выключается CapsLk и печатается пробел
	je off_CL

	pushf
	call dword ptr cs:keep_ip
	jmp rout_ending
		
	irpc met, 012345
	type_qy&met&:
		mov sign, 3&met&h
		jmp signal		
	endm
	type_M:
		mov	sign, '!'
		jmp	signal
	type_Z:
		mov	sign, '?'
		jmp	signal

	on_CL:
		xor ax, ax
		mov es, ax
		mov al, 01000000b ;готовим бит 6 (CapsLk) к установке
		or es:[417h], al ;меняем байт статуса
		mov	sign, ' '
		jmp	signal
	off_CL:
		xor ax, ax
		mov es, ax
		mov al, 10111111b ;сбрасываем бит 6
		and es:[417h], al ;меняем байт статуса
		mov	sign, ' '
		jmp	signal
	;сигнал подтверждения микропроцессору клавиатуры
	signal:
		in al, 61h ;читаем состояние порта 61h
		mov ah, al
		or al, 80h ;устанавливаем бит 7
		out 61h, al ;посылаем измененный байт в порт
		xchg ah, al 
		out 61h, al ;возвращаем состочние порта 61h
		mov al, 20h
		out 20h, al		
	record_sign:
		mov ah, 05h
		mov cl, sign ;пишем символ в буфер клавиатуры
		mov ch, 00h
		int 16h
		or al, al ;проверка переполнения буфера
		jz rout_ending		
		cli ;запрещаем прерывания
		xor ax, ax 
		mov es, ax 
		mov al, es:[41Ah] ;указатель на голову буфера
		mov es:[41Ch], al ;посылаем его в указатель хвоста
		sti ;разрешаем прерывания
		jmp record_sign
	rout_ending:
	pop ds
	pop es
    pop di
	pop	si
	pop dx
	pop cx
	pop bx
	pop ax
;	mov ax, keep_ss
;	mov ss, ax
;	mov sp, keep_sp
;	mov ax, keep_ax
;	mov bp, keep_bp
    mov al, 20h
    out 20h, al
    iret    
rout endp
last_byte:

print proc near
	push ax
	mov ah, 09h
	int 21h
	pop ax
	ret
print endp

rout_load proc near
    push ax
	push bx
	push cx
	push dx
    push es
	push ds
   	mov ah, 62h
	int 21h
	push bx
	pop es ;в es PSP
	Interrupt_handler_load: ;загрузка обработчика прерывания
	mov ah, 35h ;функция получения вектора
	mov al, 09h ;номер вектора
	int 21h ;es:bx - адрес обработчика прерывания
	mov keep_cs, es ;запоминание сегмента
    mov keep_ip, bx ;запоминание смещения	
	lea	dx, load_msg
	call print	
    ;для функции 25h прерывания 21h 
    ;al - номер прерывания
    ;ds:dx - адрес программы обработки прерывания
	lea dx, rout ;смещение процедуры
	mov ax, seg rout ;сегмент процедуры
	mov ds, ax 
	mov ah, 25h ;функция установки вектора
	mov al, 09h ;номер вектора
	int 21h ;замена прерывания
	pop ds		
    ;для функции 31h прерывания 21h 
    ;al - код выхода
    ;dx - объем памяти, оставляемой резидентной, в параграфах
    ;выходит в родительский процесс, сохраняя код выхода в al
    ;DOS устанавливает начальное распределение памяти
    ;далее возвращает управление родительскому процессу, оставляя указанную память резидентной
    lea di, last_byte 
	mov dx, (di+10Fh)/16
	;К длине резидентной части программы прибавляется размер PSP (1OOh) и еще число 15 (Fh),
	;чтобы после получения размера программы в параграфах результат был округлен в большую сторону
	xor al, al ;0 - нормальное завершение
	mov ah, 31h
	int 21h
	mov ah, 4Ch
	int 21h
    pop es
    pop dx
	pop cx
	pop bx
	pop ax
	ret
rout_load endp

rout_unload proc near
    cli 
	push ax
	push bx
	push cx
	push dx
	push ds
	push es
	push si
	push di
	mov ah, 62h
	int 21h
	push bx
	pop es ;в es PSP
	;командная строка при запуске программы находится по адресу es:[80h]
	cmp byte ptr es:[82h], '/'
	jne alrd_load_rout
	cmp byte ptr es:[83h], 'u'
	jne alrd_load_rout
	cmp byte ptr es:[84h], 'n'
	jne alrd_load_rout		
	lea	dx, unload_msg
	call print		
	mov ah, 35h ;функция получения вектора
	mov al, 09h ;номер вектора
	int 21h ;es:bx - адрес обработчика прерывания
	push ds
	mov si, offset keep_ip
	sub si, offset rout ;si - смещение ip
	mov dx, es:[bx+si] ;адрес ip
	mov ax, es:[bx+si+2] ;адрес cs
	mov ds, ax
	mov ah, 25h
	mov al, 09h
	int 21h
	pop ds
    mov ax, es:[bx+si-2] ;адрес psp
	mov es, ax
	push es
	mov ax, es:[2ch] ;сегментный адрес среды
	mov es, ax
	;DOS Function 49H: Освободить распределенный блок памяти
	mov ah, 49h
	int 21h 
	pop es ;адрес psp
	mov ah, 49h
	int 21h
	jmp unload_ending		
	alrd_load_rout:
	mov dx, offset alrd_load_msg
	call print
	unload_ending:
    sti
	xor ax, ax
	mov es, ax
	mov al, 10111111b
	and es:[417h], al
	pop di
    pop si
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
	ret	
rout_unload endp

main proc far
    push ds
    xor ax, ax
    push ax
    mov ax, DATA
    mov ds, ax
	mov 	keep_psp, es
    mov ah, 35h ;функция получения вектора
	mov al, 09h ;номер вектора
	int 21h ;es:bx - адрес обработчика прерывания
	lea di, signature ;адрес, записанный в векторе прерывания
	sub di, offset rout ;di - смещение сигнатуры
	cmp ES:[bx+di], 4321h ;сравнение значения сигнатуры с реальным кодом
	je rl ;если совпадают, то резидент установлен
	call rout_load ;иначе не установлен
	rl:	call rout_unload
	mov ax, 4C00h
	int 21h
	ret
main endp
code ends
end main