#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

int main()
{
    int clientSock_fd;

    clientSock_fd = socket(AF_INET , SOCK_DGRAM,0);
    if(clientSock_fd == -1)
    {
        printf("Error \n");
        exit(-1);
    }
    int port = 1125;
    char message[50] = "Client says hi \n";
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    client.sin_port = htons(port);
    bzero(&(client.sin_zero),8);

    ssize_t sentBytes ;

    sentBytes = sendto(clientSock_fd,message,sizeof(message),0,(struct sockaddr *)&client,sizeof(client));
    if(sentBytes < 0)
    {
        printf("Error in sending \n");
    }
    else
    {
        printf("Data Sent \n");
    }
    close(clientSock_fd);
}