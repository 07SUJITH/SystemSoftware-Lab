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
  subtraction: dec si
        dec di
        mov al,[si]
        sbb al,[di]
        mov ah,00h
        aas
        mov [di],al
        dec cl
        jnz subtraction
        display result
        mov cl,08h
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
c:\> masm s32.asm
c:\> link s32.obj
c:\> s32.exe

Enter the  first number: 87654321
Enter the second number: 12345678
Result is 75308643

c:\> s32.exe

Enter the  first number: 55115511
Enter the second number: 22112211
Result is 33003300

@data segment
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
  subtraction: dec si
        dec di
        mov al,[si]
        sbb al,[di]
        mov ah,00h
        aas
        mov [di],al
        dec cl
        jnz subtraction
        display result
        mov cl,08h
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
c:\> masm s32.asm
c:\> link s32.obj
c:\> s32.exe

Enter the  first number: 87654321
Enter the second number: 12345678
Result is 75308643

c:\> s32.exe

Enter the  first number: 55115511
Enter the second number: 22112211
Result is 33003300

@