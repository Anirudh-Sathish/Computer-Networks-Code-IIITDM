// Author : @ Anirudh Sathish

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>


int main ()
{
    int serverSocket_fd , size , connection_fd ;
    char send_data[50],recieve_data[50];
    int portNo;
    struct sockaddr_in serverAddress , clientAddress ;
    printf("\n Server Running \n");
    serverSocket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket_fd == -1)
    {
        printf("Error to exit \n");
        exit(-1);
    }
    printf("Enter the port number : \n ");
    scanf("%d",&portNo);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNo);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bzero(&(serverAddress.sin_zero),8);

    if(bind(serverSocket_fd,(struct sockaddr *)&serverAddress,sizeof(struct sockaddr)) == -1)
    {
        printf("Error to exit 2 \n");
        exit(-1);
    }
    if(listen(serverSocket_fd,2) == -1)
    {
        printf("Error in listening \n");
        exit(-1);
    }

    printf("\nWaiting for connection \n ");
    size = sizeof(struct sockaddr);
    connection_fd = accept(serverSocket_fd,(struct sockaddr *)&clientAddress,&size);
    

    if(connection_fd == -1)
    {
        printf("Failed to connect \n");
        exit(-1);
    }

    int val , count ,i;
    printf("\nSucesss !!! You have connected \n");
    recv(connection_fd,&val,sizeof(val),0);
    count = val;
    
    int recdata ;
    while(1)
    {
        i = recv(connection_fd,&recdata,sizeof(recdata),0);
        if(val == -1 )
        {
            printf("\nWe are done \n");
            break;
        }
        if(count != val)
        {
            printf("Waiting ...... . Package Missing now \n ");
            strcpy(send_data,"Missing Packet");
            send(connection_fd,&count,sizeof(count),0);
            send(connection_fd,send_data,strlen(send_data),0);
        }
        else
        {
            printf("\nThe packet number is : %d \n",val);
            printf("The data is : %d \n",recdata);
            count++;
            strcpy(send_data,"ACK");
            send(connection_fd,&count,sizeof(count),0);
            send(connection_fd,send_data,strlen(send_data),0);
        }
        printf("\nThe expected packet now is : %d \n ",count);
        //printf("Low drop \n");
        recv(connection_fd,&val,sizeof(val),0);
    }
    strcpy(send_data,"ACK");
    send(connection_fd,&count,sizeof(count),0);
    send(connection_fd,send_data,strlen(send_data),0);
    close(connection_fd);
    close(serverSocket_fd);
    return 0;

}