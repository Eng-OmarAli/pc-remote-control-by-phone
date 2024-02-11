#include "server.hpp"
#include "config.hpp"

#include "../Commands/commands.hpp"

server::server(){
    // creating socket 
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 

    // specifying the address 
    //sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(PORT); 
    inet_pton(AF_INET, IP, &serverAddress.sin_addr);
        
    // binding socket. 
    bind(serverSocket,
        (sockaddr*)&serverAddress, 
        sizeof(serverAddress)); 

    // listening to the assigned socket 
    listen(serverSocket, SOMAXCONN);
    }
    /* This function accepts connections from clients then run commands*/
    void server::start_communication(){
        while (1) {
        // accepting connection request 
        clientAddressLen = sizeof(clientAddress);
        clientSocket = accept(serverSocket,
                             (sockaddr*)&clientAddress,
                              &clientAddressLen); 
        
        // Error handling
        if (clientSocket < 0) {
            cout << "Error accepting connection" << endl;
            continue;
        }

        // Print information of connected client 
        cout << "Server accepted connection from " << inet_ntoa(clientAddress.sin_addr) << endl;
        // Print number of connected clients
        cout << "Number of connected clients: " << ++clientCounter << endl;

        // Make a child process by fork() and check if a child process is created successfully
        childpid = fork();
        if (childpid < 0) {
            cerr << "Error: while forking process" << endl;
            close(clientSocket);
            continue;
        } else if (childpid == 0) { // Child process
            close(serverSocket); // Close server socket in child process since its no longer needed to for accepting connections
            handle_data(clientSocket); // Process messages from clients
            exit(0);
        } else { // Parent process
            close(clientSocket); // Close client socket in parent process
        }
    }   
        // Close server socket
        close(serverSocket);
    }
    void server::handle_data(int clientSocket){

        while (true)
        {
            memset(buffer, 0, sizeof(buffer)); 
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if( bytesReceived == -1){
                cout << "Error: can't receive data."<< endl;
                cout << "Program terminated.";
            }
            if( bytesReceived == 0){
                cout << "No incoming data."<< endl;
                cout << "connection terminated."<< endl;
            }
            // Run commands from the client
            if ( !strcmp(buffer , "run vscode") ){
                system(VSCODE);
                cout<<"Running Visual Studio Code"<<endl;
            }
            else if (!strcmp(buffer , "run vlc") ){
                system(VLC);
                cout<<"Running VLC"<<endl;    
            }
            else if (!strcmp(buffer , "run terminal") ){
                system(TERMINAL);
                cout<<"Running terminal"<<endl;    
            }      
            else if (!strcmp(buffer , "run firefox") ){
                system(FIREFOX);
                cout<<"Running firefox browser"<<endl;    
            }
            else if (!strcmp(buffer , "run wireshark") ){
                system(WIRESHARK);
                cout<<"Running wireshark application"<<endl;    
            }
            else if (!strcmp(buffer , "run tilix") ){
                system(TILIX);
                cout<<"Running tilix terminal"<<endl;    
            }
            else if (!strcmp(buffer , "+") ){
                system(VOLUME_UP);
                cout<<"Raised sound volume by 10%"<<endl;    
            }
            else if (!strcmp(buffer , "-") ){
                system(VOLUME_DOWN);
                cout<<"Lowered sound volume by 10%"<<endl;    
            }
            else if (!strcmp(buffer , "mute") ){
                system(VOLUME_MUTE);
                cout<<"Muted system"<<endl;    
            }
            else if (!strcmp(buffer , "max volume") ){
                system(VOLUME_MAX);
                cout<<"Max volume reached system"<<endl;    
            }
            else{
                cout<<"Error: wrong input from user"<< endl;
            }       
        }
        // Close the client socket
        close(clientSocket);
    }
    
    // Destructor to release resources if needed
    server::~server() {
    // Close the socket if it was opened
    if (serverSocket >= 0) {
        close(serverSocket);
    }
}

