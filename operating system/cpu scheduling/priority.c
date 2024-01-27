/*
input :number of process np, process details(pid,burst time, priority)
output : watiting time ,tat , average wt and tat
*/
#include<stdio.h>
#define MAX_PROCESS 20
struct process {
    int pid;
    int burst_time;
    int priority;
    int wt;
    int tat;
}p[MAX_PROCESS],temp;
int np;
void swap(int i,int j){
    temp=p[i];
    p[i]=p[j];
    p[j]=temp;
}
void sort_by_priority(){
    for (int i = 0; i < np-1; ++i){
        int min = i;
        for(int j = i+1;j<np;j++)
            if(p[j].priority < p[min].priority)
                min = j;
        if(min!=i) swap(min,i);
    }
}

void priority_scheduling(){
    sort_by_priority();
    int prev_completion_time = 0;
    int total_tat = 0, total_wt = 0;
    printf("Process_id priority Burst_Time Waiting_Time Turnaround Time\n");
    for(int i = 0;i<np;i++){
        p[i].wt = prev_completion_time;
        p[i].tat = p[i].wt+p[i].burst_time;
        total_wt += p[i].wt ;
        total_tat += p[i].tat;
        prev_completion_time +=p[i].burst_time;
    printf("   %d\t%d\t\t%d\t\t%d\t%d\n",p[i].pid,p[i].priority,p[i].burst_time,p[i].wt,p[i].tat);
    }
    printf("average watiting time : %.2f\n",(float)total_wt/np);
    printf("average turn around time : %.2f\n",(float)total_tat/np);
}
int main(){
    printf("Enter the number of process : ");
    scanf("%d",&np);
    printf("Enter the process_id  burst_time and  priority \n");
    for(int i = 0;i<np;i++)
        scanf("%d%d%d",&p[i].pid,&p[i].burst_time,&p[i].priority);
    priority_scheduling();
}
/*
Enter the number of process :5
Enter the process_id  burst_time and  priority
1 10 3                 
2 1 1
3 2 4
4 1 5
5 5 2

Process_id priority burst_time waiting_time turnaround time
        2       1       1       0         1
        5       2       5       1         6
        1       3       10      6         16
        3       4       2       16        18
        4       5       1       18        19
Average turnaround time : 12.00
Average waiting time : 8.20

*/