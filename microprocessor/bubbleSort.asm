data segment 
	prompt1 db 0ah,0dh,'Enter the number of elements: $'
	prompt2 db 0ah,0dh,'Enter the numbers: $'
	result db 0ah,0dh,'Sorted numbers are : $'
	array db 10h dup(0)
	n db ?
data ends
display macro msg
	lea dx,msg	
	mov ah,09h
	int 21h
endm
readDigit macro 
	mov ah,01h
	int 21h
	sub al,30h
endm
printDigit macro
	add dl,30h
	mov ah,02h
	int 21h
endm
code segment
assume cs:code,ds:data
start:mov ax,data
	mov ds,ax
	display prompt1
	readDigit         
	mov n,al
	mov cl,n
	display prompt2
	mov si,offset array
readArray: readDigit
	mov [si],al
	inc si
	dec cl
	jnz readArray
	mov cl,n
	dec cl
outerLoop:
	mov ch,cl 
	mov si,offset array
innerLoop:
	mov dl,[si]
	cmp dl,[si+1]
	jnc swap
	jmp afterSwap
swap: xchg dl,[si+1]
	mov [si],dl
afterSwap: inc si
	dec ch
	jnz innerLoop
	dec cl
	jnz outerLoop
	mov cl,n
	mov si,offset array
	display result
printResult: mov dl,[si]
	printDigit
	inc si
	dec cl
	jnz printResult
finish : mov ah,4ch
	int 21h
code ends
end start

comment @
c:\>masm sort.asm
c:\>link sort.obj
c:\>sort.exe

Enter the number of elements: 5
Enter the numbers: 98451
Sorted numbers are : 14589
c:\>sort.exe

Enter the number of elements: 9
Enter the numbers: 654321987
Sorted numbers are : 123456789
@