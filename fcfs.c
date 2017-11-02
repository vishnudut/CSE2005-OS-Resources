#include<stdio.h>
 
int main()
{
    int n,burst_time[10],waiting_time[20],tat[20],avg_waiting_time=0,avtat=0,i,j;
    printf("Enter total number of processes:");
    scanf("%d",&n);
    printf("Enter the processes in the order of their arrival time\n");
    printf("\nEnter Process Burst Time\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&burst_time[i]);
    }
    waiting_time[0]=0;    
 
    for(i=1;i<n;i++)
    {
        waiting_time[i]=0;
        for(j=0;j<i;j++)
            waiting_time[i]+=burst_time[j];
    }
 
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
 
    for(i=0;i<n;i++)
    {
        tat[i]=burst_time[i]+waiting_time[i];
        avg_waiting_time+=waiting_time[i];
        avtat+=tat[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,burst_time[i],waiting_time[i],tat[i]);
    }
 
    avg_waiting_time/=i;
    avtat/=i;
    printf("\n\nAverage Waiting Time:%d",avg_waiting_time);
    printf("\nAverage Turnaround Time:%d\n",avtat);
 
    return 0;
}
