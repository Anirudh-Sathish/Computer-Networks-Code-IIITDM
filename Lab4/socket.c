/*Anirudh Sathish */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 7078
int main(int argc, char const* argv[])
{
    int server, new_socket, input;
    struct sockaddr_ig network_addres;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer_res[1024] = { 0 };
    char* msg = "Server says I am here";
  
    // Creating socket file descriptor
    if ((server = socket(AF_LOCAL, SOCK_STREAM, 0))
        == 0) {
        perror("Error ");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    network_address.sin_family = AF_LOCAL;
    network_address.sin_addr.s_addr = INADDR_ANY;
    network_address.sin_port = htons(PORT);
  
    // Attatching socket to port
    if (bind(server, (struct sockaddr*)&network_address,
             sizeof(network_address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server, 3) < 0) {
        perror("Listen enable");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server, (struct sockaddr*)&network_address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }
    input = read(new_socket, buffer_res 1024);
    printf("%s\n", buffer_res);
    send(new_socket, msg, strlen(msg), 0);
    printf("Message Sent by Server\n");
    
  // closing the connected socket
    close(new_socket);
  // closing the listening socket
    shutdown(server, SHUT_RDWR);
    return 0;
}