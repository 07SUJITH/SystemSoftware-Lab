#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char bit[20];
void bitmask_convert(char mask[4]){
    strcpy(bit,"");
    char hex_to_bin[16][5] = {
    "0000",  "0001","0010", "0011","0100",  "0101", "0110", "0111",
    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
    };
    for(int i =0;i< strlen(mask);i++)
        if(mask[i]<='9')
            strcat(bit,hex_to_bin[mask[i]-'0']);
        else 
            strcat(bit,hex_to_bin[mask[i]-'0'-7]); 
}

int main(){
    printf("enter the loaded address: ");
    int loadedAddressD;
    scanf("%x",&loadedAddressD);
    FILE *objectPorgram = fopen("objectProgram.txt","r");
    char record[100],bitmask[10];
    int addressD,textRecordLD;
        int   bitmask_index;
    char opcodeOb[3],addressOb[5];
    int addressObD;
    fgets(record,sizeof(record),objectPorgram);
    fscanf(objectPorgram,"%s",record);
    while(strcmp(record,"E")!=0){
        if(strcmp(record,"T")==0){
            fscanf(objectPorgram,"%x",&addressD);
            fscanf(objectPorgram,"%x",&textRecordLD);
            fscanf(objectPorgram,"%s",bitmask);
            bitmask_convert(bitmask);
            bitmask_index=0;
            addressD += loadedAddressD;
            fscanf(objectPorgram,"%s",record);
        }
        if(bit[bitmask_index]=='1'){
            for(int i =0;i<6;i++){
                if(i<2) opcodeOb[i]= record[i];
                else addressOb[i-2] = record[i];
            }
            opcodeOb[2] = '\0';addressOb[4]='\0';
            addressObD = strtol(addressOb, NULL,16) ;
            addressObD+= loadedAddressD;
            printf("%x  %s%x\n",addressD,opcodeOb,addressObD);
        }else printf("%x  %s\n",addressD,record);
            addressD += 3; 
            bitmask_index++;
            fscanf(objectPorgram,"%s",record);
    }
    fclose(objectPorgram);
}

/*
input
H SAMPLE 001000 0036
T 001000 12 F80 001016 201018 141025 481030 201050 14106A
T 002000 12 380 001016 201018 141025 481030 201050 14106A
E 001000


output
enter the loaded address: 2000
3000  003016
3003  203018
3006  143025
3009  483030
300c  203050
300f  14106A
4000  001016
4003  201018
4006  143025
4009  483030
400c  203050
400f  14106A
*/