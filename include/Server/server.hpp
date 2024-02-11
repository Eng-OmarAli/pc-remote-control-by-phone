#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

class server{
    public:
        server();   
        void start_communication();
        ~server(); 
    private:
        int serverSocket;
        sockaddr_in serverAddress;
        sockaddr_in clientAddress;
        socklen_t clientAddressLen;
        int clientSocket;       
        pid_t childpid;             // Child process id
        int clientCounter = 0;
        int bytesReceived;
        char buffer[1024] = { 0 };

        void handle_data(int clientSocket);
};

#endif