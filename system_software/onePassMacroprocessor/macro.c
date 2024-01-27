#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display(char *filename){
  FILE *fp = fopen(filename, "r");
  char ch = fgetc(fp);
  while (ch != EOF){
      printf("%c", ch);
      ch = fgetc(fp);
  }printf("\n");
  fclose(fp);
}

void readFile(FILE *file, char *label, char *opcode, char *operand) {
  fscanf(file, "%s%s%s", label, opcode, operand);
}

void onePassMacro()
{
  FILE *fin, *namtab, *deftab, *argtab, *output;
  int len, i, posInt= 1;
  char arg[20], opcode[20], operand[20], label[20], name[20];
  char opcode1[20], operand1[20];
  char  posStr[10], questionMark[5];
  fin = fopen("minput.txt", "r");
  namtab = fopen("namtab.txt", "w+");
  deftab = fopen("deftab.txt", "w+");
  argtab = fopen("argtab.txt", "w+");
  output = fopen("op.txt", "w+");
  readFile(fin, label, opcode, operand);
  while (strcmp(opcode, "END") != 0){
      if (strcmp(opcode, "MACRO") == 0){
          fprintf(namtab, "%s\n", label);
          fprintf(deftab, "%s\t%s\n", label, operand);
          readFile(fin, label, opcode, operand);
          while (strcmp(opcode, "MEND") != 0){
              if (operand[0] == '&'){
                sprintf(posStr, "%d", posInt);
                strcpy(questionMark, "?");
                strcpy(operand, strcat(questionMark, posStr));
                posInt++;
              }
              fprintf(deftab, "%s\t%s\n", opcode, operand);
              readFile(fin, label, opcode, operand);
          }
          fprintf(deftab, "%s", opcode);
      }
      else{
          rewind(deftab);rewind(namtab);
          fscanf(namtab, "%s", name);
          if (strcmp(opcode, name) == 0){
              len = strlen(operand);
              for (i = 0; i < len; i++){
                if (operand[i] != ',')
                    fprintf(argtab, "%c", operand[i]);
                else
                    fprintf(argtab, "\n");
              }
              rewind(argtab);
              fscanf(deftab, "%s%s", opcode1, operand1); 
              fscanf(deftab, "%s%s", opcode1, operand1);
              while (strcmp(opcode1, "MEND") != 0){
                if (operand1[0] == '?'){
                    fscanf(argtab, "%s", arg);
                    fprintf(output, "-\t%s\t%s\n", opcode1, arg);
                }else
                    fprintf(output, "-\t%s\t%s\n", opcode1, operand1);
                fscanf(deftab, "%s%s", opcode1, operand1);
              }
          }
          else
              fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
      }
      readFile(fin, label, opcode, operand);
  }
  fprintf(output, "%s\t%s\t%s", label, opcode, operand);
  fclose(fin); fclose(namtab); fclose(deftab); 
  fclose(argtab); fclose(output);
}

int main(){
  onePassMacro();
  printf("\nArgument table:\n\n"); display("argtab.txt");
  printf("\nName table:\n\n"); display("namtab.txt");
  printf("\nDefinition table:\n\n"); display("deftab.txt");
  printf("\nExpanded code:\n\n"); display("op.txt");
}
/*
input

EX1 MACRO &A,&B
- LDA &A
- STA &B
- MEND -
SAMPLE START 1000
- EX1 N1,N2
N1 RESW 1
N2 RESW 1
- END -

output

Argument table:

N1
N2

Name table:

EX1


Definition table:

EX1     &A,&B
LDA     ?1
STA     ?2
MEND

Expanded code:

SAMPLE  START   1000
-       LDA     N1
-       STA     N2
N1      RESW    1
N2      RESW    1
-       END     -
*/