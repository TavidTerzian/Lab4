/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    char* ip = "10.0.2.15";
    char buffer[1024] = {0};
    char clientReply[1024] = {0};

/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_port = htons(5000);
    inet_pton(AF_INET, ip, &address.sin_addr);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    // keep the client connected until user wants to quit
    while(result == 0) {
        cout << "HERE" << endl;
        // read in buffer
        read(sockfd, buffer, 1024);
        // print buffer to client console
        cout << buffer << endl;
        // get client response
        scanf("%s", clientReply);
        // send client response
        send(sockfd, clientReply, strlen(clientReply), 0);
        char bigBuffer[3000] = {0};
        recv(sockfd, bigBuffer, 3000, 0);
        read(sockfd, bigBuffer, 3000);
        cout << "Response From Server" << endl;
        cout << bigBuffer << endl;
        if(clientReply[0] == '5') {
            break;
        }
        printf("char from server = %c\n", ch);
    }
    close(sockfd);
    exit(0);
}
