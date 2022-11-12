#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>

int main()
{
    int serverSock_fd;

    serverSock_fd = socket(AF_INET, SOCK_DGRAM,0);
    if(serverSock_fd <0)
    {
        printf("Connection Error Exit \n");
        exit(-1);
    }
    char msg[100];
    int port = 1125;
    struct sockaddr_in server, client;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    bzero(&(msg),8);

    int bind_fd;
    bind_fd = bind(serverSock_fd,(struct sockaddr*)&server,sizeof(server));
    if(bind_fd <0)
    {
        printf("Exit due to unable to bind \n");
        exit(-1);
    }
    socklen_t len = sizeof(client);
    ssize_t recvBytes = recvfrom(serverSock_fd,&msg,sizeof(msg),0,(struct sockaddr *)&client,&len);
    if(recvBytes < 0)
    {
        printf("Didnt Recieve data \n");
    }
    else
    {
        printf("Data : %s \n",msg);
    }
}

