data segment
	prompt1 db 0ah,0dh,'Enter the string : $'
	result db 0ah,0dh,'Reversed string : $'
        array db 10h dup(0)
data ends
display macro msg
	lea dx,msg
	mov ah,09h
	int 21h
endm
code segment
assume cs:code,ds:data
start:mov ax,data
	mov ds,ax
	mov si,offset array
	display prompt1
	mov cl,00h

readString: mov ah,01h
	int 21h
	cmp al,0dh
        jz exitReadString
	mov [si],al
	inc si
	inc cl
	jmp readString
exitReadString:  dec si
	mov di, offset array
reverse:
	cmp si,di
	jc displayResult 
	mov al,[si]
        mov bl,[di]
        mov [si],bl
	mov [di],al
	inc di
	dec si
	jmp reverse
        mov si,dx
displayResult: display result
        mov si,offset array
showReverse: mov dl,[si]
        mov ah,02h
        int 21h
        inc si
	dec cl
	jnz showReverse 
finish: mov ah,4ch
	int 21h
code ends
end start

comment @
c:\>masm rev.asm
c:\>link rev.obj
c:\>rev.exe

Enter the string : kerala
Reversed string : alarek

c:\>rev.exe

Enter the string : intel
Reversed string : letni

@

