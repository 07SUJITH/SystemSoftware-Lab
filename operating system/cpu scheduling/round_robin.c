/*
input: np(no.of process),quantum_time,process details(pid,burst time)
output: wt,tat of each process , average wt and tat

*/
#include<stdio.h>
#define MAX_PROCESS 20 
struct process {
    int pid;
    int burst_time;
    int remain_time;
    int isComplete;
    int wt;
    int tat;
}p[MAX_PROCESS];
int quantum_time,np;

void display(){
    printf("\nProcess_ID Burst_Time Waiting_Time Turnaround_Time\n");
    int total_wt = 0, total_tat =0;
    for (int i = 0; i < np; ++i){
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("%d \t %d \t\t %d \t\t %d\n", p[i].pid, p[i].burst_time, p[i].wt, p[i].tat);
    }
    printf("average watiting time : %.2f\n",(float)total_wt/np);
    printf("average turn around time : %.2f ",(float)total_tat/np);
}

void round_robin(){
 int one_more = np;
 for(int i=0;i<np;i++){
    p[i].remain_time = p[i].burst_time;
    p[i].isComplete = 0;
 }
 int rotate_idx = -1;
 int prev_completion_time = 0,i;
 while(one_more>0){
    rotate_idx = (rotate_idx + 1)%np;
    i = rotate_idx;
    if(p[i].isComplete) continue;
    if(p[i].remain_time > quantum_time){
        p[i].remain_time -= quantum_time;
        p[i].tat = prev_completion_time+ quantum_time;
    }else{
        p[i].tat = prev_completion_time + p[i].remain_time;
        p[i].isComplete = 1;
        one_more--;
    }
    prev_completion_time = p[i].tat;
 }
 for(int i = 0;i<np;i++)    
    p[i].wt = p[i].tat - p[i].burst_time;  
 display();
}

int main(){
    printf("Enter the number of process:  ");
    scanf("%d",&np);
    printf("Enter the time_quantum : ");
    scanf("%d",&quantum_time);
    printf("Enter the process_id burst_time \n");
    for(int i = 0;i<np;i++)
        scanf("%d%d",&p[i].pid,&p[i].burst_time);
    round_robin();
    return 0;
}
/*
Enter the number of process:  5
Enter the time_quantum : 6
Enter the process_id burst_time
1 21
2 18
3 12
4 30
5 15

Process_ID Burst_Time Waiting_Time Turnaround_Time
1        21              63              84
2        18              54              72
3        12              36              48
4        30              66              96
5        15              66              81
average watiting time : 57.00
average turn around time : 76.20

*/