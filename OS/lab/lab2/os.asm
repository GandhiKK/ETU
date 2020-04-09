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

print proc near
	push ax
	mov ah, 09h
	int 21h
	pop ax
	ret
print endp

processing:
	;Unavailable memory segment address
	mov ax, ds:[02h]
	mov di, offset memData + 39	
	call word_to_hex
	mov dx, offset memData
	call print
  
	;Segment address of the environment
	mov di, offset envData + 39
	mov ax, ds:[2ch]
	mov env_seg, ax ;запоминаем сегмент
	call word_to_hex
	mov dx, offset envData
	call print 

	;Command line tail
	mov cl, ds:[80h]
	mov di, offset cmdLine + 18
	test cl, cl
	je noCmdLine	
	mov si, 81h    
	copy: 
		mov al, ds:[si]
		mov [di], al
		inc si
		inc di
		loop copy  
	mov dx, offset cmdLine
	call print
	jmp env
    noCmdLine:
		mov dx, offset ZcmdLine
		call print
	
	;Environment
	env:	
	mov dx, offset content
	call print
	xor di, di
	mov ds, env_seg	
	mov cx, 2
	reading:
		cmp byte ptr [di], 00h ;конец строки
		je output
		mov dl, [di]
		mov ah, 02h
		int 21h
		jmp env_end	
   	output:
		cmp cx, 0
		jz env_end
		mov dl, 13
		mov ah, 02h
		int 21h
		mov dl, 10
		mov ah, 02h
		int 21h
		dec cx
    env_end:		
		inc di
		cmp byte ptr [di], 0001h 
		je path
		jmp reading
		
	;Path
	path:
	add di, 2 ;пропуск байтов 00h, 01h
	mov cx, cs
	mov ds, cx
	lea	dx, path_string
	call print
	mov ds, env_seg			
   	reading_path:
		cmp byte ptr [di], 00h
		je end_path
		mov dl, [di]
		mov ah, 02h
		int 21h
		inc di
		jmp reading_path
	end_path:
		mov cx, cs
		mov ds, cx
		lea dx, env_string
		call print
	mov ah, 4ch
	int	21h
	ret 
  
env_seg dw ?
memData db 'Unavailable memory segment address:     ', 13, 10, '$' 
envData db 'Segment address of the environment:     ', 13, 10, '$' 
cmdLine db 'Command line tail:            ', '$'  
ZcmdLine db 'No command line tail', '$' 
content db 13, 10, 'Content:', 13, 10, '$'
path_string db 13, 10, 'Path: ', '$' 
env_string db  '$' 
lab ends  
end main