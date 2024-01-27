data segment
	prompt1 db 0ah,0dh,"Enter the string : $"
	prompt2 db 0ah,0dh,"Enter the key : $"
	result1 db 0ah,0dh,"key found $"
	result2 db 0ah,0dh,"key not found $"
	array db 0ah dup(0)
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
	mov si ,offset array
	display prompt1
	mov cl,00h	
readString:mov ah,01h
	int 21h
	cmp al,0dh
	jz readKey
	mov [si],al   	    
	inc si
	inc cl
	jmp readString
readkey:display prompt2 
	mov ah,01h
	int 21h
	mov bl,al

scanString: dec si
	cmp bl,[si]
	jz found
	dec cl 
	jnz scanString
	jmp notfound
notfound: display result2
	jmp finish
found:display result1
finish: mov ah,4ch
	int 21h
code ends
end start

comment @
Enter the string : viratkohli
Enter the key : k
key found 

Enter the string : viratkohli 
Enter the key : m
key not found 
@