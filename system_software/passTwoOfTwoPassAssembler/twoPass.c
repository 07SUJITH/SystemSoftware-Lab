#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(char *fileName){
    FILE *fp = fopen(fileName,"r");
    char ch = fgetc(fp);
    printf("\n");
    while (ch != EOF){
        printf("%c",ch);
        ch = fgetc(fp);
    }fclose(fp);
}
void textRecordWrite(FILE *fp,char *text,int textLen){
    char inter[3];
    sprintf(inter,"%02x",(textLen*3));
    text[9] = inter[0];
    text[10] = inter[1];
    fprintf(fp,"%s\n",text);
}
int main(){
    FILE *intermediate = fopen("intermediate.txt","r");
    FILE *objectProgram = fopen("objectProgram.txt","w");
    FILE *assemblyListing = fopen("assemblyListing.txt","w");
    FILE *symtab = fopen("symtab.txt","r");
    FILE *optab = fopen("optab.txt","r");
    FILE *length = fopen("prglen.txt","r");
    int prgLenD,startAddressD ;
    char text[100];
    int count=0,textLen=0;
    fscanf(length,"%x",&prgLenD);
    char locctr[10],label[10],operand[10],opcode[10];
    fscanf(intermediate,"%s%s%s%s",locctr,label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        startAddressD = strtol(operand,NULL,16);
        fprintf(objectProgram,"H^%06s^%06x^%06x\n",label,startAddressD,prgLenD);
        fprintf(assemblyListing,"%s\t%s\t%s\t%s\t**\n",locctr,label,opcode,operand);
        sprintf(text+count,"T^%06x^",startAddressD);
        count = 11;
    }
    while(!feof(intermediate)){
        fscanf(intermediate,"%s%s%s%s",locctr,label,opcode,operand);
        if(strcmp(opcode,"END")==0){
            textRecordWrite(objectProgram,text,textLen);
            fprintf(objectProgram,"E^%06x\n",startAddressD);
            fprintf(assemblyListing,"%s\t%s\t%s\t%s\t**\n",locctr,label,opcode,operand);
        }
        if (strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0){
            fprintf(assemblyListing,"%s\t%s\t%s\t%s\t**\n",locctr,label,opcode,operand);
        }else if(strcmp(opcode,"WORD")==0){
            int decObc = atoi(operand); 
            fprintf(assemblyListing,"%s\t%s\t%s\t%s\t%06x\n",locctr,label,opcode,operand, atoi(operand));
            sprintf(text+count,"^%06x",atoi(operand));
            count +=7;textLen++;
        }else if(strcmp(opcode,"BYTE")==0){
            sprintf(text+count,"%s","^");
            count++;  
            char obj[10];
            char *formatSpecifier = operand[0]=='X'?"%c":"%x";
            int increment = operand[0]=='X'? 1:2;
            int len = strlen(operand);
            int bytestart  = count;
            for (int i = 2,j=0; i < len-1;count+= increment ,i++){
                sprintf(text+count,formatSpecifier,operand[i]);  
            }
             fprintf(assemblyListing,"%s\t%s\t%s\t%s\t%06s\n",locctr,label,opcode,operand,text+bytestart);
            textLen++;
        }else{
            char mnemonic[10],machinecode[10];
            char symbol[10],address[10];
            rewind(optab);
            while(!feof(optab)){              
                fscanf(optab, "%s%s",mnemonic,machinecode);
                if(strcmp(mnemonic,opcode)==0){
                    while(!feof(symtab)){
                        fscanf(symtab,"%s%s",symbol,address);
                        if(strcmp(symbol,operand)==0){
                        sprintf(text+count,"^%s%s",machinecode,address);
                        fprintf(assemblyListing,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,text+count+1);
                        textLen++;count+=7;
                        break;
                        }
                    }
                    break;
                }
            }
        }  
    }
fclose(objectProgram);display("objectProgram.txt");
fclose(assemblyListing); display("assemblyListing.txt");
}
/*
input
------
1000	SAMPLE	START	1000
1000	FIRST	LDA	ALPHA
1003	-	MUL	BETA
1006	-	LDA	EOF
1009	ALPHA	RESB	10
1013	BETA	WORD	2
1016	EOF	BYTE	C'EOF'
1019	AAA	BYTE	X'AAA'
101C	-	END	1000

MUL 20
LDA 00



output
-------
H^SAMPLE^001000^000018
T^001000^12^001009^201013^001016^000002^454f46^AAA
E^001000

1000    SAMPLE  START   1000    **
1000    FIRST   LDA     ALPHA   001009
1003    -       MUL     BETA    201013
1006    -       LDA     EOF     001016
1009    ALPHA   RESB    10      **
1013    BETA    WORD    2       000002
1016    EOF     BYTE    C'EOF'  454f46
1019    AAA     BYTE    X'AAA'     AAA
101C    -       END     1000    **
*/