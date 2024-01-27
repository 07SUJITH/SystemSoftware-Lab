/*
input :
    number of process (np)
    arrival time,burst time of each process
output:
    display waiting time,completeion time , turn around time of each process.
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESS 20
struct process{  
    int wt;
    int arrival_time;
    int tat;
    int pid;
    int burst_time;
    int completion_time;
} p[MAX_PROCESS],temp;
int np;
void swap(int j,int i){
    temp=p[j];
    p[j]=p[i];
    p[i]=temp;
}
void sort_by_arrival_time(){
    for(int i = 0;i<np-1;i++){
        int min = i;
        for(int j=i+1;j<np;j++)
            if(p[min].arrival_time > p[j].arrival_time)
                min = j;
        if(i!=min) swap(min,i);
    }
}
void fcfs(){
    sort_by_arrival_time();
    int prev_completion_time = 0 ;
    int total_tat=0 ,total_wt = 0;
    printf("Process  Arrived  Burst_Time Waiting_Time   tat\n");
    for (int i = 0; i < np; i++){
        if(p[i].arrival_time >= prev_completion_time ){
            p[i].tat = p[i].burst_time;
            p[i].wt = 0;
            prev_completion_time = p[i].arrival_time+ p[i].tat;
        }else{
            p[i].wt = prev_completion_time - p[i].arrival_time;
            p[i].tat = p[i].burst_time + p[i].wt;
            prev_completion_time  += p[i].burst_time;
        }
        printf("   %d\t  %d\t   %d\t\t%d\t    %d \n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].wt,p[i].tat);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("Average tat : %.2f \n",(float)total_tat/np);
    printf("Average wt : %.2f \n",(float)total_wt/np);
}
int main(){
    printf("Enter the Number of Processes: ");
    scanf("%d",&np);
    printf("Enter the process id ,arrival time and burst time \n");
    for(int i=0 ;i<np ; i++){
        scanf("%d%d%d",&p[i].pid,&p[i].arrival_time,&p[i].burst_time);
    }
    fcfs();
}
/*

Enter the Number of Processes: 5
Enter the process id ,arrival time and burst time
1 0 4
2 1 3
3 2 1
4 3 2
5 4 5
Process  Arrived  Burst_Time Waiting_Time   tat
   1      0        4            0           4
   2      1        3            3           6
   3      2        1            5           6
   4      3        2            5           7 
   5      4        5            6           11
Average tat : 6.80
Average wt : 3.80

*/