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
double getPressure(PyObject *pModule);
double getHumidity(PyObject *pModule);
void sendMessage(PyObject *pModule, const char* message);

int main(int argc, char * argv[])
{
    if(argc != 3){
        printf("Error: Please provide an IP and Port\n");
        exit(EXIT_FAILURE);
    }

    Py_Initialize();

    int arg;
    char* argIpAddress = argv[1];
    const char* serverIpAddress = argIpAddress;
    int argPort = atoi(argv[2]);
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
    //server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = (unsigned short)htons(argPort);
    inet_pton(AF_INET, argIpAddress, &server_address.sin_addr);
    server_len = sizeof(server_address);
    // bind server addr to socket

    int n_bind = bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    if(n_bind < 0) {
        cerr << "Err with binding\n";
    }
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
        if(new_sockfd < 0)
            break;
        id = pthread_create(&a_thread, NULL, clientHandler, &new_sockfd);
	/*  We can now read/write to client on client_sockfd.  */
        // present optionsMenu to the client
	    //Thread variables
    }
    Py_Finalize();
}

void *clientHandler(void *arg)
{
	int newSock = *((int*)arg);
	char* optionsMenu = "Sense Hat Menu\n---------\n1. Get Temperature\n2. Get Pressure\n3. Get Humidity\n4. Set Message\n5. Exit\n";
	char clientMessage[1024] = {0};

	while(1){
        send(newSock, optionsMenu, strlen(optionsMenu), 0);
        // read input from client
        char exampleRes = '1';
        int sizeBuff = sizeof(exampleRes);
		int n_recv = recv(newSock, clientMessage, 1024, 0);
        if(n_recv != sizeBuff) {
            break;
        }
		cout << "Client Response: ";
		cout << clientMessage << endl;
		bool end = false;
        
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
                end = true;
                option_five(newSock);
            } break;
            default:
            {
                cerr << "Invalid input" << endl;
            } break;
        }
        if(end)
            break;
	}
}

void option_one(int fd) {
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
    string tempString = "Temperature: " + std::to_string(getTemperature(pModule));
    const char* message = tempString.c_str();
    char* mod_message = strdup(message);
    if(send(fd, mod_message, strlen(mod_message), 0) < 0) {
        cerr << "Error in sending to client option 1" << endl;
       printf("Value of errno: %d\n", errno);
    }
    sleep(1.5);
}

void option_two(int fd) {
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
    string tempString = "Pressure: " + std::to_string(getPressure(pModule));
    const char* message = tempString.c_str();
    char* mod_message = strdup(message);
    if(send(fd, mod_message, strlen(mod_message), 0) < 0) {
        cerr << "Error in sending to client" << endl;
       printf("Value of errno: %d\n", errno);
    }
    sleep(1.5);
}

void option_three(int fd) {
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
    string tempString = "Humidity: " + std::to_string(getHumidity(pModule));
    const char* message = tempString.c_str();
    char* mod_message = strdup(message);
    if(send(fd, mod_message, strlen(mod_message), 0) < 0) {
        cerr << "Error in sending to client" << endl;
       printf("Value of errno: %d\n", errno);
    }
    sleep(1.5);
}

void option_four(int fd) {
    char bigBuffer[3000] = {0};
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
    const char* title = "Enter your message.";
    send(fd, title, strlen(title), 0);
    read(fd, bigBuffer, 3000);
    cout << "Debug: Message from client = " << bigBuffer << endl;
    sendMessage(pModule, bigBuffer);
    sleep(1.5);
}

void option_five(int fd) {
    const char* title = "Terminated Program. Goodbye.\n";
    send(fd, title, strlen(title), 0);
    sleep(1.5);
    pthread_exit(NULL);
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

double getPressure(PyObject *pModule)
{

    double pressure = 0.0;

    PyObject *pFunc = PyObject_GetAttrString(pModule, "getPressure");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
	pressure = PyFloat_AsDouble(pValue);
	Py_DECREF(pValue);
    } else {
	PyErr_Print();
    }

    Py_DECREF(pFunc);

    return pressure;

}

double getHumidity(PyObject *pModule)
{

    double humidity = 0.0;

    PyObject *pFunc = PyObject_GetAttrString(pModule, "getHumidity");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
	humidity = PyFloat_AsDouble(pValue);
	Py_DECREF(pValue);
    } else {
	PyErr_Print();
    }

    Py_DECREF(pFunc);

    return humidity;

}
void sendMessage(PyObject *pModule, const char* message)
{
    double worked;
    PyObject *pFunc = PyObject_GetAttrString(pModule, "sendMsg");
    // attr - temp static argument to pass to Python sendMessage
    PyObject *stringObjectArg = PyBytes_FromStringAndSize(message, sizeof(message) * 2);
    if (pFunc && PyCallable_Check(pFunc)) {
        // pass the Python object as a 2nd argument
        PyObject *pValue = PyObject_CallObject(pFunc, stringObjectArg);
        worked = PyFloat_AsDouble(pValue);
        if(worked = 1){
            cout << "Sense show message called\nMessage was: " << message << endl;
        }
    } 
    else {
        PyErr_Print();
    }

    Py_DECREF(pFunc);


}
