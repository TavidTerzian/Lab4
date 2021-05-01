# Lab4

## Collaboration project between Tavid Terzian and Tarek El-Hajjaoui.

## Description of Program:
  -This is a C creates a TCP Server that creates a socket in which 5 clients can connect to
  - Once connected, the clients are presented with options menu
  - They have 5 options: 1 - get temperature of sense hat, 2 - get pressure of sense hat, 3 - get humidity of sense hat, 4 - send message to sense hat, 5 - exit socket connection
  - The program usees which allows C++ to interface with Python code that does the desired functionality mentioned above
  - Console arguments [ip address, port number]
  
## Instructions to run the program:
  -Compile the Server with g++ using this specific command:
  g++ senseHatServer.cpp ipAddressArg portNumberArg -o Server -I /usr/include/python2.7/ $(/usr/bin/python2.7-config --ldflags) -w
  where ipAddressArg amd portNumberArg is the desired ip address and port number to be used for the socket connection
  - Run the Server 
  - Compile the client with g++ using this command:
  g++ SenseHatClient.cpp -o Client -I /usr/include/python2.7/ $(/usr/bin/python2.7-config --ldflags) -w
  
## Sources:
  - C Bind: https://man7.org/linux/man-pages/man2/bind.2.html
  - C Accept: https://man7.org/linux/man-pages/man2/accept.2.html
  - C Send: https://man7.org/linux/man-pages/man2/send.2.html
  - C Recv: https://man7.org/linux/man-pages/man2/recv.2.html
  - C c_str: https://www.cplusplus.com/reference/string/string/c_str/
  - C strdup: https://man7.org/linux/man-pages/man3/strdup.3.html
  - Python2.7 Object Protocol for C/C++: https://docs.python.org/2.7/c-api/object.html
  - Linux Man page: https://linux.die.net/man/3/syslog  
  - GNU: https://www.gnu.org/software/libc/manual/html_node/Syslog-Example.html
  
 ## Relevant Source Files:
  - senseHatServer.cpp
  - SenseHatClient.cpp
  - senseHatModules.py
  - senseHatModules.pyc
  - *Please ignore other files
  
