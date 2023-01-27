#include <iostream>
#include <winsock.h>

using namespace std;

#define PORT 9909


struct sockaddr_in srv;
// this sockaddr struture contains the details about
// the port where we are listening, Ip address, 

  
int main()
{
    int nRect = 0;
    // Initialize the WSA variables 

    WSADATA ws;
    if(WSAStartup(MAKEWORD(2,2),&ws) < 0)
    {
        cout << "WAS failed to initialized\n";
        exit(EXIT_FAILURE);
    }
    else{
        cout << "WAS initialized\n";
    }

    // 1. Initialize the socket
    
    int nClientSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    
    /*
     we put 0 because to specify the protocol.
     0 means the connection will uses http protocol
     if we wanna change the protocol then write
     IIPROTO_[protocol]  
    */
    
    if(nClientSocket < 0 )
    {
        cout << "Socket not opened\n";
        WSACleanup();
        exit(EXIT_FAILURE);

    }
    else{
        cout << "\nSocket opened successfully\n";
    }

    // 2. Initialize the environment for sockaddr structure 

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1"); //we are assigning our own ip address to make it a server 
    //srv.sin_addr.s_addr = inet_addr([ip address]) to assign other ip address other than your IP addr 

    memset(&(srv.sin_zero),0,8);

    nRect = connect(nClientSocket, (struct sockaddr*) &srv, sizeof(srv));
    if(nRect < 0)
    {
        cout << "Connection Failed\n";
    }
    else
    {
        cout << "CONNECTED\n";
        char BUFFER[255] = {0};
        recv(nClientSocket, BUFFER, 255, 0);
        cout << endl << "Press Enter to see the received message\n";
        getchar();
        cout << BUFFER << endl;
    
        cout << "Now send your message to the server: ";
        while(1)
        {
            fgets(BUFFER,256,stdin);
            send(nClientSocket,BUFFER,256,0);
            cout << "\nPress enter to see the recieved response: ";
            getchar();
            recv(nClientSocket,BUFFER,256,0);
            cout << "Now send next message: ";
        }
    }

}