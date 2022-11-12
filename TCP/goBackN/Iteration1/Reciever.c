// Header Files 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/socket.h>

int main()
{
    int sock ;
    char send_data[50],data[50];

    struct sockaddr_in server , client ;
    printf("\n Server Running \n");

    sock = socket(AF_INET,SOCK_STREAM , 0 );
    if(sock == -1 )
    {
        exit(1);
    }
    int port_no = 1122;
    server.sin_port = htons(port_no);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY ; 
    bzero(&(server.sin_zero),8);

    int binding  ;
    binding = bind(sock , (struct sockaddr *)&server,sizeof(struct sockaddr));

    if(binding == -1 )
    {
        printf("Error \n ");
        exit(-1);
    }
    int listener = listen(sock , 2);
    if(listener == -1)
    {
        printf("Error \n");
        exit(-1);
    }
    printf(" Waiting for connection \n ");
    int acceptingSize = sizeof(struct sockaddr);
    int connection ;
    connection = accept(sock,(struct sockaddr *)&client,&acceptingSize);

    if(connection == -1)
    {
        printf("Error \n");
        exit(1);
    }

    printf("Connected Successfully \n");
    
    
    int val ;
    ssize_t bytesRead;
    char stringVal[10];
    bytesRead = recv(connection,&val,sizeof(val),0);
    printf("Count is %d \n",val);
    ssize_t sendACK_Bytes;
    while(val != -1)
    {
        bytesRead = recv(connection,&val,sizeof(val),0);
        if(val == -1)
        {
            break;
        }
        printf("Frame : %d  Recieved \n",val);
        sprintf(stringVal,"%d",val);
        // Send acknowledgement
        strcpy(send_data,"ACK");
        strcat(send_data,stringVal);
        sendACK_Bytes = send(connection,&send_data,sizeof(send_data),0);
        if(sendACK_Bytes == -1)
        {
            printf("Didnt Send Back Acknowledgement \n");
        }
        else
        {
            printf("Sent acknowledgement \n");
        }
           
    }
    

    // To close 
    close(connection);
    close(sock);

}
