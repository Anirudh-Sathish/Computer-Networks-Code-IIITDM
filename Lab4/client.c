// Anirudh Sathish 

// Client side

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 7078
  
int main(int argc, char const* argv[])
{
    int client_socket = 0, input, client;
    struct sockaddr_in serv_addr;
    char* msg = "Client says hi";
    char buffer_res[1024] = { 0 };
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_LOCAL;
    serv_addr.sin_port = htons(PORT);
  
  
    if (inet_pton(AF_LOCAL, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((client
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(client_socket, msg, strlen(msg), 0);
    printf("Message sent\n");
    input = read(client_socket, buffer_res, 1024);
    printf("%s\n", buffer_res);
  
   
    close(client);
    return 0;
}