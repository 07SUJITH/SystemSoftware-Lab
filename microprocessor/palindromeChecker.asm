data segment 
	prompt1 db 0ah,0dh,'Enter the string: $'
	result1 db 0ah,0dh,'String is palindrome $'
	result2 db 0ah,0dh,'String is not palindrome $'
	array db 10h dup(0)
data ends
display macro msg
	lea dx,msg
	mov ah,09h
	int 21h
endm
code segment
assume cs:code,ds:data
start:  mov ax,data
	mov ds,ax
	mov si,offset array
	display prompt1
readString: mov ah,01h
	int 21h
	cmp al,0dh
	jz exitReading
	mov [si],al
	inc si
	jmp readString
exitReading: dec   si
	mov di,offset array
palindromeCheck:
	cmp si,di
	jc palindrome
	mov al,[si]
	cmp al,[di]
	jnz notPalindrome
	inc di
	dec si
	jmp palindromeCheck
palindrome: display result1
	jmp finish
notPalindrome: display result2
finish: mov ah,4ch
	int 21h
code ends
end start


comment @
c:\>masm pal.asm
c:\>link pal.obj
c:\>pal.exe

Enter the string: kerala
String is not palindrome 

c:\>pal.exe

Enter the string: malayalam
String is palindrome 
@
