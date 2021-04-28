/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std; // so can use string 

int main()
{
    int server_sockfd, client_sockfd; // file descriptor vars
    int server_len, client_len;
    // server and client addresses
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    // size of client address - must be socklen_t data type
    socklen_t client_address_size;
    char buffer[1024] = {0};
    char clientMessage[1024] = {0};
    
    //string optionsMenu = "";
    //optionsMenu += "Sense Hat Menu\n";
    //optionsMenu += "---------\n";
    //optionsMenu += "1. Get Temperature\n";
    //optionsMenu += "2. Get Pressure\n";
    //optionsMenu += "3. Get Humidity\n";
    //optionsMenu += "4. Set Message\n";
    //optionsMenu += "5. Exit\n";
    
    char* optionsMenu = "Sense Hat Menu\n---------\n1. Get Temperature\n2. Get Pressure\n3. Get Humidity\n4. Set Message\n5. Exit\n";
    
/*  Remove any old socket and create an unnamed socket for the server.  */

    unlink("server_socket");
    // init socket: [AF_INET - IPv4 protocols, SOCK_STREAM - socket type, 0 (default val) - protocol type]
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket.  */
    // assign socket addr fields to server addr
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(5000);
    server_len = sizeof(server_address);
    // bind server addr to socket
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */
    // second arg is backlog - max num of connections to allow on socket
    listen(server_sockfd, 5);
    while(1) {
        char* ch;
        string chars;
        printf("server waiting\n");

/*  Accept a connection.  */
        client_len = sizeof(client_address);
        client_address_size = sizeof(client_address);
        
        // server socket accepts client connection
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_address_size);

/*  We can now read/write to client on client_sockfd.  */
        // present optionsMenu to the client
        send(client_sockfd, optionsMenu, strlen(optionsMenu), 0);
        // read input from client
        recv(client_sockfd, clientMessage, 1024, 0);
        cout << "Client Response: ";
        cout << clientMessage << endl;
	ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}
