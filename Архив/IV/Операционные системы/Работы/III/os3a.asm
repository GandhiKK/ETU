lab segment
assume cs:lab, ds:lab, es:nothing, ss:nothing
org 100h
main: jmp processing

LastMCB EQU 5Ah ;тип последнего MCB
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

word_to_dec proc near
	;перевод числа в 16 сс 
	;в ax - число, si - адрес последнего символа
	push cx
	push dx
	mov cx, 10
	pr: div cx
	or dl, 30h
	mov [si], dl
	dec si
	xor dx, dx
	cmp ax, 10
	jae pr
	cmp al, 0
	je end_pr
	or al, 30h
	mov [si], al
	end_pr:	pop dx
	pop cx
	ret
word_to_dec endp

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

print proc near
	push ax
	mov ah, 09h
	int 21h
	pop ax
	ret
print endp

MemoryInfo proc near
	push ax
	push bx
	push cx
	push dx
	push di
	push si
	mov si, offset avlmem
	add si, 18
	int 12h
	;Reports the number of contiguous 1K memory blocks in the system (up to 640K)
	;This is the amount of memory available to the entire system
	;This is not the amount of memory available to the user's program
	mov bx, 10
	call word_to_str
	lea dx, avlmem
	call print

	mov al, 30h
    out 70h, al
    in al, 71h ;чтение младшего байта
    mov bl, al 
    mov al, 31h  
    out 70h, al
    in al, 71h ;чтение старшего байта
	mov ah, al
	mov al, bl
	lea si, expmem
	add si, 17
	mov bx, 10
	call word_to_str
	lea dx, expmem
	call print
	pop si
	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	ret 
MemoryInfo endp

MCB_processing PROC near
	push ax
	push bx
	push cx
	push dx
	mov ah, 52h     
    int 21h          
    sub bx, 2       
    mov ax, word ptr es:[bx] 
    mov es, ax ;адрес первого блока
    xor di, di     
	mov cx, 1
	lea dx, tit ;таблица
	call print

manipulations:
	mov ax, cx
	inc cx
	lea si, count
	add si, 5
	mov bx, 10
	call word_to_str
	lea dx, count
	call PRINT ;номер MCB блока	
	push cx
	xor ax, ax
	mov al, es:[0h] ;тип MCB
	push ax
	mov ax, es:[1h]	;владелец

	irpc case, 0678
	cmp ax, 000&case&h
	je MCB_label_&case&			
	endm
	irpc case, ADE
	cmp ax, 0FFF&case&h
	je MCB_label_&case&			
	endm
	
	lea di, space
	add di, 5
	call word_to_hex 
	lea dx, space
	call print
	jmp MCB_size	

	irpc met, 0678ADE	
	MCB_label_&met&:
		lea dx, owner_&met&
		call print
		jmp MCB_size		
	endm
	
MCB_size: ;размер
	mov ax, es:[3h]
	mov bx, 16
	mul bx	
	lea si, space
	add si, 5
	call word_to_dec
	lea dx, space
	call print
	mov cx, 8
	xor si, si	
	Linr: mov dl, es:[si+8h]
	mov ah, 02h
	int 21h
	inc si
	loop Linr	
	mov ax, es:[3h]
	mov bx, es
	add bx, ax
	inc bx
	mov es, bx ;адрес следующего блока
	pop ax
	pop cx
	cmp al, LastMCB
	je ending
	jmp manipulations

ending:	
	lea dx, endstr
	call print
	pop dx
	pop cx
	pop bx
	pop ax
	ret
MCB_processing endp

processing:
	call MemoryInfo
	call MCB_processing
	mov ah, 4ch
	int	21h
	ret 
  
avlmem db 'Available memory:    K', 13, 10, '$' 
expmem db 'Expanded memory:      K', 13, 10, '$' 
mesto db 16 dup (0)
tit db 13, 10, '  MCB    Possessor  Area size(B)   Command Linr $'
endstr db 13, 10, '      ___End of Memory Block List___$'
space db 13 dup (?), '$'
count db 13, 10, 9 dup (?), '$'
owner_0 db '  free       $'
owner_6 db 'OS XMS UMB$'
owner_7 db 'Excluded top memory of driver$'
owner_8 db '  MS DOS     $'
owner_A db '386MAX UMB$'
owner_D db '386MAX$'
owner_E db '386MAX UMB$'
lab ends  
end main