/*
input :number of process np, process details(pid,burst time)
output : watiting time ,tat , average wt and tat
*/
#include<stdio.h>
#define MAX_PROCESS 20

struct process{
    int pid;
    int burst_time;
    int wt;
    int tat;
}p[MAX_PROCESS],temp;
int np;
void swap(int i ,int j){
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}
void sort_by_burst_time(){
    for (int i = 0; i < np-1; ++i){
        int min = i;
        for(int j = i+1;j<np;j++)
            if(p[j].burst_time< p[min].burst_time)
                min = j;
        if(min!=i) swap(min,i);
    }
}
void sjf(){

    sort_by_burst_time();
    int prev_completion_time=0;
    int total_tat = 0,total_wt = 0;
    printf("Process_id Burst_Time Waiting_Time Turnaround Time\n");
    for(int i = 0 ;i< np;i++){
        p[i].wt = prev_completion_time;
        p[i].tat = p[i].wt + p[i].burst_time;
        total_wt += p[i].wt;
        total_tat+= p[i].tat;
        prev_completion_time = p[i].tat;
        printf("   %d\t\t%d\t\t%d\t%d\n",p[i].pid,p[i].burst_time,p[i].wt,p[i].tat);
    }
    printf("average watiting time : %.2f\n",(float)total_wt/np);
    printf("average turn around time : %.2f\n",(float)total_tat/np);
}
int main(){

    printf("Enter the number of process : ");
    scanf("%d",&np);
    printf("Enter the process id and burst time of processes\n");
    for(int i =0;i<np;i++)
        scanf("%d%d",&p[i].pid,&p[i].burst_time);
    sjf();
}

/*
Enter the number of process : 5
Enter the process id and burst time of processes
1 45
2 32
3 21
4 67
5 89
Process_id Burst_Time Waiting_Time Turnaround Time
   3            21              0       21
   2            32              21      53
   1            45              53      98
   4            67              98      165
   5            89              165     254
average watiting time : 67.40
average turn around time : 118.20

*/