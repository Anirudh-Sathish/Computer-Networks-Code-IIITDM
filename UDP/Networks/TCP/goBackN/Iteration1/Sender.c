
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

int main()
{
    int sock_fd;
    char sendData[50];
    struct sockaddr_in server;

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

    int connection = connect(sock_fd,(struct sockaddr*)&server,sizeof(struct sockaddr));

    if(connection == -1)
    {
        printf("Error \n");
        exit(-1);
    }
    // For sending info 
    int frameCount = 10;
    int windowSize = 3;
    int array[10] = {1,2,3,4,5,6,7,8,9,10};

    // For reading Frames 
    char readData[50];
    ssize_t readACK_Bytes;

    // Send the frames
    int remainingFrame = frameCount;
    int i = 0 ;
    int currentPacket = i ;
    ssize_t sentBytes;
    while(remainingFrame >= 1)
    {
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

        // For Receiving the acknowledgements
        readACK_Bytes = recv(sock_fd,&readData,sizeof(readData),0);
        if(readACK_Bytes == -1)
        {
            printf("Didnt recieve ACK \n");
        }
        else
        {
            printf("%s \n",readData);
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




