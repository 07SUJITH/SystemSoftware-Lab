#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define intermediate_write fprintf(intermediate,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
void display(char *fileName){
    FILE *fp = fopen(fileName,"r");
    char ch = fgetc(fp);
    printf("\n");
    while (ch != EOF){
        printf("%c",ch);
        ch = fgetc(fp);
    }fclose(fp);
    
}

int main(){
    FILE *input = fopen("assemblyProgram.txt","r");
    FILE *optab = fopen("optab.txt","r");
    FILE *intermediate = fopen("intermediate.txt","w");
    FILE *length = fopen("length.txt","w");
    FILE *symtab = fopen("symtab.txt","w");
    char label[10],opcode[10],operand[10];
    char mnemonic[10],machineCode[10]; 
    fscanf(input,"%s%s%s",label,opcode,operand);
    int startAddress,locctr,isValidOpcode;
    if(strcmp(opcode,"START")==0){
        startAddress = strtol(operand,NULL,16);
        locctr = startAddress ;
        intermediate_write
        fscanf(input,"%s%s%s",label,opcode,operand);
    }else locctr = 0;
    while(strcmp(opcode,"END")!=0){
        if(strcmp(label,"**")!=0) fprintf(symtab,"%s\t%x\n",label,locctr);
        intermediate_write
        isValidOpcode = 0;
        rewind(optab);
        fscanf(optab,"%s%s",mnemonic,machineCode);
        while(!feof(optab)){
            if(strcmp(mnemonic,opcode)==0){
                isValidOpcode = 1;
                locctr +=3;
                break;
            }
           fscanf(optab,"%s%s",mnemonic,machineCode);

        }
        if(isValidOpcode == 0){
            if(strcmp(opcode,"WORD")==0 ) locctr += 3;
            else if(strcmp(opcode,"RESB")==0) locctr += atoi(operand);
            else if(strcmp(opcode,"RESW")==0) locctr += 3*atoi(operand);
            else if(strcmp(opcode,"BYTE")==0){
                int len = strlen(operand)-3;
                if(operand[0] == 'X') locctr += ceil(len/2);
                else locctr += len;
            }else {
                printf("\ninvalid opcode !");
                exit(0);
            }
        }
        fscanf(input,"%s%s%s",label,opcode,operand);
    }
    intermediate_write
    fprintf(length,"%x",locctr-startAddress);
    fclose(input);fclose(intermediate);
    fclose(length);fclose(optab);fclose(symtab);
    display("length.txt"); display("symtab.txt");
    display("intermediate.txt");
}

/*
input
----------------------------------------
assembly program
------------
SAMPLE START 2000
**      LDA FIVE
**      ADD CONST
**      STA ALPHA
FIVE     WORD 5
CONST   RESW 1
ALPHA   RESW 2
EOF     BYTE C'EOF'
HEXF1   BYTE X'F1'
** END   2000

optab
------
LDA 00
MUL 20
ADD 18
STA 0C

output
----------------------------------
2000	SAMPLE	START	2000
2000	**	LDA	FIVE
2003	**	ADD	CONST
2006	**	STA	ALPHA
2009	FIVE	WORD	5
200c	CONST	RESW	1
200f	ALPHA	RESW	2
2015	EOF	BYTE	C'EOF'
2018	HEXF1	BYTE	X'F1'
2019	**	END	2000


19

FIVE	2009
CONST	200c
ALPHA	200f
EOF	2015
HEXF1	2018

*/