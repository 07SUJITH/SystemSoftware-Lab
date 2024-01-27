data segment
        prompt1 db 0ah,0dh,'Enter the  first number: $'
        prompt2 db 0ah,0dh,'Enter the second number: $'
        result db 0ah,0dh,'Result is $'
        n1 db  08h dup(0)
        n2 db  08h dup(0)
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
        mov  ah,02h
        int 21h
        endm
code segment
        assume ds:data,cs: code
 start: mov ax,data
        mov ds,ax
        display prompt1
        mov si , offset n1
        mov di , offset n2
        mov cl,08h
  first:readDigit
        mov [si],al
        inc si
        dec cl
        jnz first
        display prompt2
        mov cl,08h
  second:readDigit
        mov [di],al
        inc di
        dec cl
        jnz second
        mov cl,08h
  addition: dec si
        dec di
        mov al,[si]
        adc al,[di]
        mov ah,00h
        aaa
        mov [di],al
        dec cl
        jnz addition
        display result
        mov cl,08h
        jnc resultDisplay
        mov dl,01h
        printDigit
   resultDisplay: mov dl,[di]
        printDigit
        inc di
        dec cl
        jnz resultDisplay
 finish: mov ah,4ch
        int 21h
 code ends
 end start

comment @
c:\> masm a32.asm
c:\> link a32.obj
c:\> a32.exe

Enter the  first number: 12344321
Enter the second number: 21325432
Result is 33669753

c:\> a32.exe

Enter the  first number: 34231256
Enter the second number: 91232458
Result is 125463714

@