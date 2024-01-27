#include<stdio.h>
#include<math.h>
 
int lower, upper,nr,head;
int disk_queue[20];
int head_mov = 0;

void swap(int i ,int j){
    int temp = disk_queue[i];
    disk_queue[i] = disk_queue[j];
    disk_queue[j] = temp;
}

void sort(){
    // selection sort
    for(int i = 0; i< nr-1;i++){
        int min = i;
        for (int j = i +1; j< nr;j++)
            if(disk_queue[j] < disk_queue[min])
                min = j;
        if (min!= i)  swap(min,i);
    }
}

int  indexOf(int key ){
    for(int i =0; i<nr;i++)
        if(key == disk_queue[i]) return i;
}


void scan(){
    disk_queue[nr++] = upper;
    disk_queue[nr++] = head;
    sort();
    printf("seek sequence in scan : ");
    int head_idx = indexOf(head);
    for(int i =head_idx+1; i<nr;i++){
        head_mov += abs(disk_queue[i] - head);
        printf("%d -> ",head);
        head = disk_queue[i];
    }
    for (int  i = head_idx -1; i>=0; i--){
        head_mov += abs(head- disk_queue[i]);
        printf("%d -> ",head);
        head = disk_queue[i];
    }
    printf("%d .",disk_queue[0]);
    printf("\nTotal head movements : %d ",head_mov);
}

int main(){
    printf("Enter the lower and upper limit of disk: ");
    scanf("%d%d",&lower,&upper);
    printf("Enter the initial position of head : ");
    scanf("%d",&head);
    printf("Enter the number of requests : ");
    scanf("%d",&nr);
    printf("Enter the requests : ");
    for(int i = 0; i< nr; i++)
        scanf("%d",&disk_queue[i]);
    scan();
    return 0;
}

/*
Enter the lower and upper limit of disk: 0 199
Enter the initial position of head : 53
Enter the number of requests : 8
Enter the requests :  98 183 37 122 14 124 65 67
seek sequence in scan : 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 37 -> 14 .
Total head movements : 331 

*/