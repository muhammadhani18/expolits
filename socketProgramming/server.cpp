#include <iostream>
#include <winsock.h>

using namespace std;

#define PORT 9909
void ProcessNewRequest(int nSocket);
void ProcessNewMessage(int nClientSocket);
int nArrClient[10]; // we will handle only 10 clients


struct sockaddr_in srv;
// this sockaddr struture contains the details about
// the port where we are listening, Ip address, 

int nMAXFd;
fd_set fr, fw, fe;
   /*
   a file descriptor is a kernel object which is opaque
   fe is the file descriptor. It consists of 2 elemets
   one is the number of file discriptors and an array of sockets 
   where we will keep the file descriptors 
   now the fr is the file descriptor from which we will read
   then the fw is the file dscriptor from which we will write 
   and the fe will handle the exceptions from the sockets

    */

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
    
    int nSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    
    /*
     we put 0 because to specify the protocol.
     0 means the connection will uses http protocol
     if we wanna change the protocol then write
     IIPROTO_[protocol]  
    */
    
    if(nSocket < 0 )
    {
        cout << "Socket not opened\n";
        WSACleanup();
        exit(EXIT_FAILURE);

    }
    else{
        cout << "\nSocker opened successfully\n";
    }

    // 2. Initialize the environment for sockaddr structure 

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1"); //we are assigning our own ip address to make it a server 
    //srv.sin_addr.s_addr = inet_addr([ip address]) to assign other ip address other than your IP addr 

    memset(&(srv.sin_zero),0,8);
   
    // About the blocking vs non blocking sockets
    // every socket by defualt is a blocking socket 
    u_long optval = 0; //optval = 0 means blocking and value other than 0 means non blocking  
    
    nRect = ioctlsocket(nSocket, FIONBIO, &optval); // to set a blocking or non blocking socket
    
    //ioctlsocket() is only reserved for windows. 
    if(nRect != 0)
    {
        cout << "\n ioctlsocket call failed\n";
    }

    //setsockopt
    // int nOptVal = 0 , nOptLen = sizeof(optval);
    // nRect = setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)nOptVal, nOptLen); // it allows more than one socket to use same port and Ip address
    // if(!nRect)
    // {
    //     cout << "\nThe setsockopt call successfull\n";
    // }
    // else{
    //     cout << "\nThe setsockopt call failed\n";
    //     WSACleanup();
    //     exit(EXIT_FAILURE);
    // }


    // 3. Bind the socket to the local port

    nRect = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
    // bind function needs the socket we created and the address of the 
    // structure we created

    if(nRect < 0 )
    {
        cout << "\nFail to bind to local port\n";
        exit(EXIT_FAILURE);
    }
    else{
        cout << "\nSuccessfully binded to local port\n";
    }

    // 4.Listen the request from the client

    nRect = listen(nSocket, 5); // this number tells us how many requests to listen at a time 
    if(nRect < 0)
    {
        cout << "\nFailed to start listen to local port\n";
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else{
        cout << "\nListening started\n"; 
    }


    // 5. Keep listening from the client for new requests
    
    // we can listen to 64 requests at once cuz fd_set allows that
    // int n=64;
    // for(int i=0; i<n; i++)
    // {
    //     FD_SET(n, &fr);
    //     //FD_SET is a macro to put sockets in fd_set array
    // }

    // cout << endl << fr.fd_count << endl;
    // //printing the socket descriptor
    // for(int i=0; i<n; i++)
    // {
    //     cout << fr.fd_array[i] << endl;
    // }
    
    struct timeval tv; // this will provide the timeout for the connection 
    tv.tv_sec = 1; //seconds
    tv.tv_usec = 0; // microseconds

    while(1){
        FD_ZERO(&fr);
        FD_ZERO(&fw);
        FD_ZERO(&fe);

        FD_SET(nSocket, &fr);
        FD_SET(nSocket, &fe);

        for(int i=0; i< 10; i++)
        {
            if(nArrClient[i] != 0)
            {
                FD_SET(nArrClient[i], &fr);
                FD_SET(nArrClient[i], &fe);
            }
        }

        nMAXFd  =  nSocket; // we are going to read new incoming connection on the previous made socket
        
        // the select socket descriptor will wait for
        // the free socket descriptors. How many are ready to 
        // write and how many are free to read.
        nRect = select(nMAXFd+1, &fr, &fw, &fe, &tv);
        // when we call the select() function and before it returns anything
        // it clears all the socket descriptors array so we need to set that again
        if(nRect > 0)
        {
            //Sockets ready for read and exception
            // when someone connects or communicates with a message over 
            // a dedicated connection.
            //after connection, you get one or more socket to communicate with client
            //you need to send and recv message over the network using that new socket
            cout << "\nData on Port....Proccessing...\n";
            //Process the request
            ProcessNewRequest(nSocket);
            
        }
        // else if( nRect ==0){
        //     //No connection or any communication request made or
        //     // no sockets descriptors are ready 
        //     cout << "\nNothing on Port... " << PORT << endl;
        // }
        else{
            cout << "FAILED...\n";
            // It failed and your application show some usefull message
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        Sleep(1000);
    }




    return 0;
}


void ProcessNewRequest(int nSocket)
{
    if(FD_ISSET(nSocket, &fr))
    {
        int nlen = sizeof(struct sockaddr);
        //New connection request
        int nClientSocket = accept(nSocket, NULL, &nlen); 
        if(nClientSocket > 0)
        {
            //Put it into the client fd_set
            int i;
            for(i=0; i<10; i++)
            {
                if(nArrClient[i] == 0)
                {
                    nArrClient[i] = nClientSocket;
                    send(nClientSocket, "Connection Established Successfully. \0", 255, 0);
                    break;
                }
            }
            if(i == 10)
            {
                cout << "No space for new connections\n";
            
            }
        
        }
    }
    else {
        for(int j=0; j < 10; j++)
        {
            if(FD_ISSET(nArrClient[j], &fr))
            {
                // Got the new message from the client
                // Just recv new message
                // just queue that for new worker of your new server to fulfill new request
                ProcessNewMessage(nArrClient[j]);
            }  
        }
    }            
}

void ProcessNewMessage(int nClientSocket)
{
    cout << "Processing new message for the client\n";
    char buffer[256+1] = {0,};
    int nRet = recv(nClientSocket, buffer,256,0);
    if(nRet < 0)
    {
        cout << "Something wrong happened...\n";
        closesocket(nClientSocket);
        for(int nIndex = 0; nIndex <10; nIndex++)
        {
            if(nArrClient[nIndex] == nClientSocket)
            {
                nArrClient[nIndex] = 0;
                break;
            }
        }
    } 
    else{
        cout << endl << "The message recieved from the client is: " << buffer << endl;
        send(nClientSocket, "\nProcessed your request", 24, 0);
        cout << "\n------------------------------------\n";
    }
}

