dosseg
.model small
.stack 100h
.data
pc_F db	'PC', 0dh, 0ah, '$'
pc_E db 'PC/XT', 0dh, 0ah, '$'
pc_C db	'AT or PS2 .50/60', 0dh, 0ah, '$'
pc_A db 'PS2 .30', 0dh, 0ah, '$'
pc_8 db 'PS2 .80', 0dh, 0ah, '$'
pc_D db 'PCjr', 0dh, 0ah, '$'
pc_9 db 'PC Convertible', 0dh, 0ah, '$'
pc_arg db 'PC type: ', '$'
os_arg db 'MSDOS version:  .   ', 0dh, 0ah, '$'
oem_arg	db 'OEM serial number:         ', 0dh, 0ah, '$'
user_arg db	'User serial number:        ', 0dh, 0ah, '$'
.code
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

processing proc far
	push ds
	xor ax, ax
	push ax
	mov ax, @data
	mov ds, ax
	lea dx, pc_arg
	call print

	mov ax, 0F000h ;указывает ES на ПЗУ
	mov es, ax
	mov al, es:[0FFFEh]
		
	irpc case, FECA8D9
	cmp al, 0F&case&h
	je type_&case&			
	endm

	irpc met, FECA8D9	
	type_&met&:
		lea dx, pc_&met&
		call print
		jmp OS		
	endm		

OS:
	mov ah, 30h
	int 21h ;al - осноная версия, ah - модификация, bh - OEM, bl:cx - номер пользователя
	
	lea si, os_arg
	add si, 15	
	call byte_to_dec ;пишется основная версия	
	add	si, 3
	xchg al, ah
	call byte_to_dec ;пишется модификация
	lea dx, os_arg
	call print

OEM:
	mov al, bh
	lea si, oem_arg
	add si, 19
	call byte_to_dec
	lea dx, oem_arg
	call print

serial_number:
	mov	al, bl
	lea si, user_arg
	call byte_to_hex
	mov [si+20], ax
	add	si, 25 
	mov	di, si ;ax - число, di - адрес последнего символа для word_to_hex
	mov ax, cx
	call word_to_hex
	lea dx, user_arg
	call print
	
	mov ah, 4ch
	int	21h
	ret
processing endp
end processing