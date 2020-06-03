ovrl2 segment
assume cs:ovrl2
main: jmp processing

info2 db 'Second overlay segment address is     ',13,10,'$'
mesto db 16 dup (0)

processing proc far
    push ax
    push bx
    push dx
    push ds
    push si
	mov ax, cs
	mov ds, ax	
	lea si, info2+34		
    mov bx, 16		
	call word_to_str
	lea dx, info2	
	call print
    pop si
    pop ds
    pop dx
    pop bx
    pop ax
	retf
processing endp

print proc near
	push ax
	mov ah, 09h
	int 21h
	pop ax
	ret
print endp

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
ovrl2 ends
end main 