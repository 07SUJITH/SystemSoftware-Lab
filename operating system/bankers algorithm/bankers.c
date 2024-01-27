#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int nr,np,avail[10],work[10];
int alloc[10][10],max[10][10],need[10][10];
int safeSequence[10],s;
bool finish[10];

bool safetyAlgorithm(){
    s = 0; 
    bool possible ;
    for (int i = 0; i < nr ; i++) work[i] = avail[i];
    for(int i = 0;i<np;i++) finish[i] = false;
    for(int i = 0 ;i<np;i++)
        for(int j = 0 ;j<nr;j++)
            need[i][j] = max[i][j] - alloc[i][j];
    
    for(int k = 0;k<5;k++)
        for(int i = 0;i<np;i++ )
            if(finish[i] == false){
                
                possible = true;
                for(int j = 0;j<nr;j++)
                    if(need[i][j] > work[j]){
                        possible = false;
                        break;
                    }

                    if(possible){
                        for(int j = 0;j< nr ; j++) work[j] += alloc[i][j];
                        finish[i] = true;
                        safeSequence[s++] = i;
                    }
            }
    for(int i =0;i<np;i++)
        if(finish[i] == false) return false;
    
    printf("The system is in safe state .\n");
    printf("Safe sequence : ");
    for(int j = 0;j< s;j++)
        printf("P%d ",safeSequence[j]);
    return true;
}
void resourceRequestAlgorithm(){

    int pNumber,req[10];
    printf("Enter the new request \n ");
    printf("Enter the process number :");
    scanf("%d",&pNumber);
    printf("Enter the amount of requested resources : ");
    for(int i =0;i<nr;i++)
        scanf("%d",&req[i]);
    for( int i =0;i< nr;i++)
        if(req[i] > need[pNumber][i]){
            printf("Resources not granted ! requested resource greater than needed");
            exit(1);
        }
    for(int i = 0;i<nr ;i++){
        avail[i] -= req[i];
        alloc[pNumber][i] += req[i];
        need[pNumber][i] -= req[i]; 
    }
    if(safetyAlgorithm())
        printf("\nRequest can be granted immediately");
    else 
        printf("Request not allocated --deadlock will occur \n");
}


int main(){
    printf("Enter the number of resources: ");
    scanf("%d",&nr);
    printf("Enter the resources: ");
    for(int i = 0 ;i< nr ;i++)
        scanf("%d",&avail[i]);
    printf("Enter the  number of process : ");
    scanf("%d",&np);
    printf("Enter the allocation matrix \n");
    for (int  i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter the max matrix : ");
    for (int i=0; i < np; i++ )
        for (int  j = 0;  j< nr ; j++)
            scanf("%d",&max[i][j]); 
    bool safe = safetyAlgorithm();
    if(safe) resourceRequestAlgorithm();
    else 
        printf("\nSystem is not in safe state");
}

/*
Enter the number of resources: 4
Enter the resources: 1 5 2 0
Enter the  number of process : 5
Enter the allocation matrix
0 0 1 2
1 0 0 0
1 3 5 4
0 6 3 2
0 0 1 4
Enter the max matrix : 0 0 1 2
1 7 5 0
2 3 5 6
0 6 5 2
0 6 5 6
The system is in safe state .
Safe sequence : P0 P2 P3 P4 P1 Enter the new request
 Enter the process number :1
Enter the amount of requested resources : 0 4 2 0
The system is in safe state .
Safe sequence : P0 P2 P3 P4 P1 
Request can be granted immediately
*/