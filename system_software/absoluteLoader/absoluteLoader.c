#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    FILE *fp = fopen("objectProgram.txt","r");
    char userEnteredName[7],nameInObj[7],textAddress[7],record[80];
    int addressD,i,j;
    printf("Enter program name: ");
    scanf("%s",&userEnteredName);
    fscanf(fp,"%s",record);
    for(i=0,j=2;j<=7;j++)
        nameInObj[i++] = record[j];
    nameInObj[6] = '\0';
     printf("\nProgram name in objectCode : %s\n",nameInObj);
     if(!strcmp(userEnteredName,nameInObj)){
        while(!feof(fp)){
            fscanf(fp,"%s",record);
            if(record[0]=='T'){
                for( i=0,j=2;j<=7;)
                    textAddress[i++] = record[j++];
                textAddress[6]= '\0';
                addressD = strtol(textAddress,NULL,16);
                i=12;
                while(record[i]!='$'){
                    if(record[i]!='^'){
                        printf("00%x  %c%c\n",addressD++,record[i],record[i+1]);
                        i = i+2;
                    }else i++;
                }
            }
        } fclose(fp);
    }
}
/*
Enter program name: SAMPLE

Program name in objectCode : SAMPLE
001009  00
00100a  10
00100b  03
00100c  07
00100d  10
00100e  09
00100f  11
001010  11
001011  11
*/