/* Anirudh Sathish */

/* Stop and Wait */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void sender(int frames)
{
    // Send frames 1 by 1 to the reciever
    int count = 1;
    int response = 0;
    while(count <= frames+1)
    {
        response = 0;
        printf("Sending frame %d \n",count);
        printf("Waiting for response \n");
        response = reciever(count);
        count++;
        printf("Recieved ACK %d \n",count);
    }
}
int reciever(int value)
{
    int v ;
    int even = 0 ;
    do
    {
        v = rand()%10000 ;
        if(v%2 == 0)
        {
            even = 1;
        }
        printf("Waiting \n");
    }
    while(even != 1);
    printf("Sending ACK \n");

    return 1; 
}

int main()
{
    int frame_input;
    printf("Enter the number of frames you want to send \n");
    scanf("%d",&frame_input);
    sender(frame_input);
    return 0 ; 
}