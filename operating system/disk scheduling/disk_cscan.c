#include <stdio.h>
#include <math.h>
#define MAX_REQUESTS 20
int lower,upper,no_of_requests,head;
int disk_queue[MAX_REQUESTS];
int head_mov = 0;
void swap(int i ,int j){
    int temp = disk_queue[i] ;
    disk_queue[i] = disk_queue[j] ;
    disk_queue[j] = temp ;
}
void sort(){//using selection sort algorithm
    for (int  i = 0; i < no_of_requests - 1; i++){
        int min = i;
        for (int  j = i+1; j < no_of_requests; j++)
            if(disk_queue[j] < disk_queue[min])
                min = j;
        if(min!=i)  swap(min,i);  
    }
}
int indexOf(int key){
    for(int i = 0;i< no_of_requests;i++)
        if(disk_queue[i] == key)
            return i;
    return -1;
}
//cscan disk scheduling algorithm 
void cscan(){
    disk_queue[no_of_requests] = lower;
    no_of_requests++;
    disk_queue[no_of_requests] = upper;
    no_of_requests++;
    disk_queue[no_of_requests] = head;
    no_of_requests++;
    sort();
    int head_idx = indexOf(head);
    printf("seek sequence in cscan : ");
    for(int i = head_idx; i != (head_idx-1); i = (i+1)%no_of_requests){
        head = disk_queue[i];
        printf("%d ->",head);
        head_mov += abs(disk_queue[(i+1)%no_of_requests] - head);
    }
    printf("%d .",disk_queue[head_idx-1]);
    printf("\ntotal head movements : %d ",head_mov);
}
int main(){
    printf("Enter the lower and upper limit of disk: ");
    scanf("%d%d",&lower,&upper);
    printf("Enter the number of requests : ") ;
    scanf("%d",&no_of_requests);
    printf("Enter the initial head position : ");
    scanf("%d",&head);
    printf("Enter the requests : ");
    for (int  i = 0; i < no_of_requests; i++){
        scanf("%d",&disk_queue[i]);
    }
    cscan();
    return 0;
}
/*
Enter the lower and upper limit of disk: 0 199
Enter the number of requests : 8
Enter the initial head position : 53
Enter the requests :  98 183 37 122 14 124 65 67
seek sequence in cscan : 53 ->65 ->67 ->98 ->122 ->124 ->183 ->199 ->0 ->14 ->37 .
total head movements : 382 
*/