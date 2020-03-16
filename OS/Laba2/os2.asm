dosseg
.MODEL small
.stack 100h

.DATA
blcSeg  dw ?
File_Handle dw ?
File_Name db 'psp.txt',0
dbCont  db 'окружение до:'
szCont  equ $-dbCont
dbPath  db 'путь:'
szPath  equ $-dbPath
outString db 'недоступная память:'
memData  db 5 dup(' ')
  db 13,10,'сегмент окружения:'
blcData  db 5 dup(' ')
  db 13,10,'коммандная строка:'
cmdLine  db 256 dup(?);
  db 2048 dup(?);
  
.CODE
start:
;
  push ds
;
  mov ax,@DATA
  mov ds,ax
;
  pop es
;1)
  mov ax,es:[02h]
  mov di,offset memData+3
  call SaveData
;2)
  mov di,offset blcData+3
  mov ax,es:[2ch]
  mov blcSeg,ax;запоминаем сегмент
  call SaveData
;3)
  mov cl,es:[80h]
  mov di,offset cmdLine
  or cl,cl
  jz noCmdLine
  mov si,081h
;копируем коммандную строку
CopyA:  mov al,es:[si]
  mov [di],al
  inc si
  inc di
  loop CopyA
;записываем перевод строки
noCmdLine: mov ax,0a0dh
  mov [di],ax
  inc di
  inc di
;
  mov si,offset dbCont
  mov cx,szCont
;
CopyB:  mov al,[si]
  mov [di],al
  inc si
  inc di
  loop CopyB
;4)
  mov es,blcSeg
  xor si,si
  mov cl,2;счетчик нулей
;копируем окружение
CopyC:  mov al,es:[si]
  or al,al
  jnz noZero
  mov al,20h;0 заменяем на пробел
  dec cl;если 2-а нуля подряд конец окружения
  jz noCopyC
  mov al,20h
okNext:  mov [di],al
  inc si
  inc di
  jmp short CopyC
noZero:  mov cl,2;востанавливаем счетчик
  jmp short okNext
;записываем конец строки
noCopyC: inc si
  mov ax,0a0dh
  mov [di],ax
  inc di
  inc di
;2-а пропускаем
  inc si
  inc si
  push si
;5)
  mov si,offset dbPath
  mov cx,szPath
;копируем
CopyD:  mov al,[si]
  mov [di],al
  inc si
  inc di
  loop CopyD
  pop si
;копируем полный путь
FullPath: mov al,es:[si]
  or al,al
  jz okSave
  mov [di],al
  inc si
  inc di
  jmp short FullPath
;открываем файл
okSave:  mov ah,3ch
  xor cx,cx
  mov dx,offset File_Name
  int 21h
  mov File_Handle,ax
;записываем в файл
  mov bx,ax
  mov dx,offset outString
  mov cx,di
  sub cx,dx
  mov bx,File_Handle
  mov ah,40h
  int 21h
;закрываем файл
  mov ah,3eh
  mov bx,File_Handle
  int 21h
;выход
  mov ah,4ch
  int 21h
;пп записи 16-го числа
SaveData: mov bx,16
  mov cx,4
;получаем 4-е цифры 16-го числа
SaveWord: xor dx,dx
  div bx
;преобразуем в 16-ю форму
noDiv:  or dl,30h
  cmp dl,3ah
  jl noHext
  add dl,7
;записываем значение
noHext:  mov [di],dl
  dec di
  loop SaveWord
  ret
 end start