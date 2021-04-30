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
#include <cstring>
#include <string>
#include <pthread.h>
#include <Python.h>
using namespace std; // so can use string 

void option_one(int fd);
void option_two(int fd);
void option_three(int fd);
void option_four(int fd);
void option_five(int fds);
void *clientHandler(void* arg);
double getTemperature(PyObject *pModule);
char message[] = "Hello World";

int main()
{
    //int* arg = new int;
    int arg;
    int server_sockfd;
    int client_sockfd;
    int new_sockfd; // file descriptor vars
    int server_len, client_len;
    // server and client addresses
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    pthread_t a_thread;
    // size of client address - must be socklen_t data type
    socklen_t client_address_size;
    char buffer[1024] = {0};    
    
/*  Remove any old socket and create an unnamed socket for the server.  */

    unlink("server_socket");
    // init socket: [AF_INET - IPv4 protocols, SOCK_STREAM - socket type, 0 (default val) - protocol type]
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char*) &server_address, sizeof(server_address)); 

/*  Name the socket.  */
    // assign socket addr fields to server addr
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(5000);
    server_len = sizeof(server_address);
    // bind server addr to socket

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    option_one(0);
/*  Create a connection queue and wait for clients.  */
    // second arg is backlog - max num of connections to allow on socket
    listen(server_sockfd, 5);
    while(1) {
        int id;
        printf("server waiting\n");

/*  Accept a connection.  */
        client_len = sizeof(client_address);
        client_address_size = sizeof(client_address);
        
        // server socket accepts client connection
        new_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_address_size);
        id = pthread_create(&a_thread, NULL, clientHandler, &new_sockfd);
	/*  We can now read/write to client on client_sockfd.  */
        // present optionsMenu to the client
	    //Thread variables
    }
}

void *clientHandler(void *arg)
{
	int newSock = *((int*)arg);
	char* optionsMenu = "Sense Hat Menu\n---------\n1. Get Temperature\n2. Get Pressure\n3. Get Humidity\n4. Set Message\n5. Exit\n";
	char clientMessage[1024] = {0};

	while(1){
        send(newSock, optionsMenu, strlen(optionsMenu), 0);
        // read input from client
		recv(newSock, clientMessage, 1024, 0);
		cout << "Client Response: ";
		cout << clientMessage << endl;
		
        switch(clientMessage[0]) {
            case '1': 
            {
                option_one(newSock);
            } break;
            case '2': 
            {
                option_two(newSock);
            } break;
            case '3': 
            {
                option_three(newSock);
            } break;
            case '4': 
            {
                option_four(newSock);
            } break;
            case '5': 
            {
                option_four(newSock);
            } break;
            default:
            {
                cerr << "Invalid input" << endl;
            } break;
        }
	}
}

void option_one(int fd) {
    Py_Initialize();
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
    PyObject *pName = PyUnicode_FromString("senseHatModules");
    if (pName == NULL) {
        PyErr_Print();
    }

    PyObject *pModule = PyImport_Import(pName);
    if (pModule == NULL) {
        PyErr_Print();
    }
    char* message1 = "The temp is dry and hot. Standard California.\n";
    string tempString = std::to_string(getTemperature(pModule));
    cout << tempString << endl;
    //har* message = new char[tempString.length() + 1];
    const char* message = tempString.c_str();
    cout << message << endl;
    cout << "The temp is dry and hot. Standard California.\n";
    sleep(1.5);
    Py_Finalize();
}

void option_two(int fd) {
    char* message1 = "Pressure is on, time is running out\n";
    send(fd, message1, strlen(message1), 0);
    cout << "Enterd Option 2\n";
    cout << "Pressure is on, time is running out" << endl;
    sleep(1.5);
    //pthread_exit(NULL);
}

void option_three(int fd) {
    char* message1 = "Dry as usual\n";
    send(fd, message1, strlen(message1), 0);
    cout << "Enterd Option 3\n";
    cout << "Dry as usual" << endl;
    sleep(1.5);
    //pthread_exit(NULL);
}

void option_four(int fd) {
    char* message1 = "PARTYYYY\n";
    send(fd, message1, strlen(message1), 0);
    cout << "Enterd Option 4\n";
    cout << "PARTYYYY" << endl;
    sleep(1.5);
    //pthread_exit(NULL);
}

void option_five(int fd) {
    char* message1 = "Exit is currently not working\n";
    send(fd, message1, strlen(message1), 0);
    cout << "Enterd Option 5\n";
    cout << "Exit is currently not working" << endl;
    sleep(1.5);
    //pthread_exit(NULL);
}

double getTemperature(PyObject *pModule)
{

    double temperature = 0.0;

    PyObject *pFunc = PyObject_GetAttrString(pModule, "getTemperature");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
	temperature = PyFloat_AsDouble(pValue);
	Py_DECREF(pValue);
    } else {
	PyErr_Print();
    }

    Py_DECREF(pFunc);

    return temperature;

}
