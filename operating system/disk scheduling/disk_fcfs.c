/*
input : no_of_requests,head,requests in disk queue.
output : seek sequence , total_head movements
fcfs disk scheduling algorithm.. 
*/
#include<stdio.h>
#include<math.h>
#define MAX_SIZE 20
int main(){
    int headmov = 0;
    int head ,disk_queue[MAX_SIZE],no_of_requests;
    printf("Enter the number of requests : ");
    scanf("%d",&no_of_requests);
    printf("Enter the initial position of head : ");
    scanf("%d",&head);
    printf("Enter the requests : ");
    for(int i =0;i< no_of_requests;i++){
        scanf("%d",&disk_queue[i]);
    }
    // fcfs
    printf("seek sequence in fcfs : ");
    for(int i =0; i< no_of_requests; i++){
        printf("%d->",head);
        headmov += abs(head - disk_queue[i]);
        head = disk_queue[i];
    }
    printf("%d .\n",head);
    printf("Total head movements : %d ",headmov);
}




/*
Enter the number of requests : 8
Enter the initial position of head : 53
Enter the requests : 98 183 37 122 14 124 65 67

Seek sequenece in FCFS : 53 98 183 37 122 14 124 65 67 
Total head movements : 640 
*/
