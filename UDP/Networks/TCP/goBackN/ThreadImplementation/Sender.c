// Header files 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdbool.h>
#include<pthread.h>
#define framecount 10
#define windowSize 3

int sock_fd;
char sendData[50];
int windowStart = 0  ; 
int currentFrame = 0 ;
struct sockaddr_in server;
int connection;
void *SendFrameFunction();
void *RecvACK_Fuction();

int main()
{
    pthread_t sending_t , recACK_t;

    printf("Client Running \n");
    sock_fd = socket(AF_INET,SOCK_STREAM,0);

    if(sock_fd == -1)
    {
        printf("ERror \n ");
        exit(-1);
    }
    int port_no = 1122;
    server.sin_family = AF_INET;
    server.sin_port = htons(port_no);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(server.sin_zero),8);

    connection = connect(sock_fd,(struct sockaddr*)&server,sizeof(struct sockaddr));

    if(connection == -1)
    {
        printf("Error \n");
        exit(-1);
    }

    pthread_create(&sending_t,NULL,SendFrameFunction,NULL);
    pthread_create(&recACK_t,NULL,RecvACK_Fuction,NULL);

    pthread_join(sending_t,NULL);
    pthread_join(recACK_t,NULL);

}


void *SendFrameFunction()
{
    // For sending info 
    int array[10] = {1,2,3,4,5,6,7,8,9,10};

    // Send the frames
    int remainingFrame = framecount;
    int i = 0 ;
    int currentPacket = i ;
    ssize_t sentBytes;
    int prevWindowStart = 0 ; 
    while(remainingFrame >= 1)
    {
        if(remainingFrame == framecount)
        {
            prevWindowStart = 0 ;
            for(i = 0 ; i < windowSize; i++)
            {
                sentBytes = send(sock_fd,&currentPacket,sizeof(currentPacket),0);
                if(sentBytes == -1)
                {
                    printf("Failure in sending \n");
                }
                remainingFrame-=1;
                currentPacket+=1;
            }
        }
        else
        {
            if(currentFrame == prevWindowStart)
            {
                printf("Wait for ACK \n");
            }
            else
            {
                prevWindowStart = currentFrame ;
                int wSize ;
                if(currentFrame+windowSize > framecount)
                {
                    wSize = framecount;
                }
                else
                {
                    wSize = currentFrame+windowSize ;
                }
                for(i = currentFrame ; i < wSize; i++)
                {
                    sentBytes = send(sock_fd,&currentPacket,sizeof(currentPacket),0);
                    if(sentBytes == -1)
                    {
                        printf("Failure in sending \n");
                    }
                    remainingFrame-=1;
                    currentPacket+=1;
                }
            }
        }
        
    }
    // -1 to show end of coversation
    int end = -1;
    sentBytes = send(sock_fd,&end,sizeof(end),0);
    if(sentBytes == -1)
    {
        printf("Failure in sending \n");
    }
    
    close(sock_fd);
    return 0 ;
}



void *RecvACK_Fuction()
{
    int remainingFrame = framecount;
    int timebreak = 0 ;
    // For reading Frames 
    char readData[50];
    ssize_t readACK_Bytes;

    int i ; 
    while(remainingFrame >= 1)
    {
        // For Receiving the acknowledgements
        for(i = 0 ; i < windowSize ; )
        {
            readACK_Bytes = recv(sock_fd,&readData,sizeof(readData),0);
            if(readACK_Bytes == -1)
            {
                timebreak++;
                if(timebreak == 20)
                {   
                    printf("Time Out \n ");
                    break;
                }
                printf("Didnt recieve ACK \n");
            }
            else
            {
                timebreak = 0;
                printf("%s \n",readData);
                i++;
            }

        }
        remainingFrame -= i;
        windowStart = i;
        currentFrame+=windowStart; 
        
        
    }
    close(sock_fd);

}