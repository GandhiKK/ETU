lab segment
assume cs:lab, ds:lab, es:nothing, ss:nothing
org 100h
main: jmp processing

tetr_to_hex	proc near
	and	al, 0fh
	cmp al, 09
	jbe	next
	add	al, 07
	next: add al, 30h
	ret
tetr_to_hex	endp

byte_to_hex	proc near
	;байт в al переводится в два символа 16 числа в ax
	push cx
	mov	ah, al
	call tetr_to_hex
	xchg al, ah
	mov	cl, 4
	shr	al, cl
	call tetr_to_hex ;в al старшая цифра
	pop	cx 			 ;в ah младшая цифра
	ret
byte_to_hex	endp

word_to_hex	proc near
	;перевод в 16 сс 16 разрядного числа
	;в ax - число, di - адрес последнего символа
	push bx
	mov	bh, ah
	call byte_to_hex
	mov [di], ah
	dec	di
	mov [di], al
	dec	di
	mov	al, bh
	xor	ah, ah
	call byte_to_hex
	mov	[di], ah
	dec	di
	mov	[di], al
	pop	bx
	ret
word_to_hex	endp

byte_to_dec	proc near
	;перевод в 10 сс, si - адрес поля младшей цифры
	push cx
	push dx
	push ax
	xor	ah, ah
	xor	dx, dx
	mov	cx, 10
loop_bd: 
	div	cx
	or dl, 30h
	mov	[si], dl
	dec	si
	xor	dx, dx
	cmp	ax, 10
	jae	loop_bd
	cmp	ax, 00h
	jbe	end_l
	or al, 30h
	mov	[si], al
end_l:	
	pop	ax
	pop	dx
	pop	cx
	ret
byte_to_dec	endp

print proc near
	push ax
	mov ah, 09h
	int 21h
	pop ax
	ret
print endp

processing:
	push ds
	pop es

	;Unavailable memory segment address
	mov ax, es:[02h]
	mov di, offset memData + 39	
	call word_to_hex
	mov dx, offset memData
	call print
  
	;Segment address of the environment
	mov di, offset blcData + 39
	mov ax, es:[2ch]
	mov blcSeg, ax ;запоминаем сегмент
	call word_to_hex
	mov dx, offset blcData
	call print 

	;Command line tail
	mov cl, es:[80h]
	mov di, offset CmdLine + 18
	test cl, cl
	je noCmdLine	
	mov si,081h
    
	copy: 
		mov al, es:[si]
		mov [di], al
		inc si
		inc di
		loop copy
  
	mov al, '$'
	mov [di], al
	mov dx, offset CmdLine
	call print
	jmp contents
    noCmdLine:
		mov dx, offset ZCmdLine
		call print
	
	;contents	
	contents:	
	mov es, blcSeg
	xor si, si
	mov cl, 2 ;счетчик нулей	
	mov di, offset Cont + 12
	mov al, 13
	inc di
	mov [di], al
	mov al, 10
	dec si
	jmp conti
	copyO:  mov al, es:[si] ;копируем окружение
	test al, al
	jnz notZero
	
	mov al, 20h ;0 заменяем на пробел
	dec cl ;если 2-а нуля подряд конец окружения
	jz ending
	
	mov al, 13
	mov [di], al
	mov al, 10
	inc di
	
	conti:	mov [di], al
	inc si
	inc di
	jmp short copyO	
	notZero: mov cl, 2 ;востанавливаем счетчик
	jmp short conti

	ending: 
	inc si
	inc si
	push si	
	mov al, '$'
	mov [di], al
	mov dx, offset Cont
	call print

	
	mov di, offset Path + 7
	mov cx, 5

	CopyD:  mov al,[si]
	mov [di],al
	inc si
	inc di
	loop CopyD
	pop si

	FullPath: mov al, es:[si]
	or al,al
	jz okSave
	mov [di],al
	inc si
	inc di
	jmp short FullPath
	
	okSave:
	mov dx, offset Path
	call print
	
	

	mov ah, 4ch
	int	21h
	ret 
  
blcSeg dw ?
memData db 'Unavailable memory segment address:     ', 13, 10, '$' 
blcData db 'Segment address of the environment:     ', 13, 10, '$' 
CmdLine db 'Command line tail:', 256 dup(?), 13, 10, '$'  
ZCmdLine db 'No command line tail', '$'  
Cont db 13, 10, 'Contents:', 70 dup(?), '$' 
Path db 'Path:             ', 13, 10, '$' 

lab ends  
end main