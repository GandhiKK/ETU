Astack segment stack
    dw 12 dup(?)
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
    num dw 0 
	mesto db 16 dup (0)
	int_count_msg db 'No. of ints:     $'	
	rout_start:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push es
    push ds
	mov ax, cs
	mov ds, ax ;для чисел
	mov es, ax ;для строки
	mov ax, num
	inc ax
	mov num, ax
	lea si, int_count_msg + 13
	mov bx, 10
	call word_to_str
	lea bp, int_count_msg
	call outputBP
	pop ds
	pop es
    pop di
	pop	si
	pop dx
	pop cx
	pop bx
	pop ax
    mov al, 20h
    out 20h, al
    iret    
rout endp
last_byte:

word_to_str proc near
	;на входе ax число 16 бит
	;si указатель на строку
	;bx разрядность результата
    push ax
	push bx
	push cx
	push dx
	push di
	push si
    cmp bx, 16
    ja end_wts
    cmp ax, 7FFFh
    jna plus
    mov byte ptr [si], '-'
    inc si
    not ax
    inc ax
    plus:
    	xor cx, cx
    	jmp manipulation
    manipulation:
    	xor dx, dx
      	div bx
      	mov di, ax
      	mov al, dl
      	cmp al, 10
      	sbb al, 69h
      	das
	  	push di
	  	lea di, mesto
	  	add di, cx
      	mov byte ptr [di], al
	  	pop di
      	mov ax, di
    inc cx
    test ax, ax
    jz endrep
    jmp manipulation
    endrep:
    	lea di, mesto
      	add di, cx
    copyrep:
      	dec di
      	mov dl, byte ptr [di]
      	mov byte ptr [si], dl
      	inc si
      	loop copyrep
    end_wts:
    pop si
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
    ret
word_to_str endp

outputBP proc near ;вывод строки по адресу es:bp на экран
	push ax
	push bx
	push cx
	push dx
	mov ah, 13h ;функция вывода строки в bp
	mov al, 0 ;использовать атрибут в bl и не трогать курсор
	mov bl, 09h ;цвет
	;0 = Черный      8 = Серый
    ;1 = Синий       9 = Светло-синий
    ;2 = Зеленый     A = Светло-зеленый
    ;3 = Голубой     B = Светло-голубой
    ;4 = Красный     C = Светло-красный
    ;5 = Лиловый     D = Светло-лиловый
    ;6 = Желтый      E = Светло-желтый
    ;7 = Белый       F = Ярко-белый
	mov bh, 0 ;номер страницы
	mov dh, 22 ;строка начала вывода
	mov dl, 42 ;колонка начала вывода
	mov cx, 17 ;длина строки
	int 10h  
	pop dx
	pop cx
	pop bx
	pop ax
	ret
outputBP ENDP

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
	mov al, 1Ch ;номер вектора
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
	mov al, 1Ch ;номер вектора
	int 21h ;замена прерывания
	pop ds		
    ;для функции 31h прерывания 21h 
    ;al - код выхода
    ;dx - объем памяти, оставляемой резидентной, в параграфах
    ;выходит в родительский процесс, сохраняя код выхода в al
    ;DOS устанавливает начальное распределение памяти
    ;далее возвращает управление родительскому процессу, оставляя указанную память резидентной
    lea dx, last_byte ;размер в байтах от начала сегмента
	mov cl, 4 ;перевод в параграфы
	shr dx, cl 
    add dx, 10Fh
	inc dx
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
	mov al, 1Ch ;номер вектора
	int 21h ;es:bx - адрес обработчика прерывания
	push ds
	mov si, offset keep_ip
	sub si, offset rout ;si - смещение ip
	mov dx, es:[bx+si] ;адрес ip
	mov ax, es:[bx+si+2] ;адрес cs
	mov ds, ax
	mov ah, 25h
	mov al, 1ch
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
	mov al, 1Ch ;номер вектора
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