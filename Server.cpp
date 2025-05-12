#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

using namespace std;

int main()
{
    WSADATA wsaData; // WSADATA is a struct with details about implementing sockets
    int wsaError;
    wsaError = WSAStartup(MAKEWORD(2, 2), &wsaData); // WSAStartup innitializes winsock using version and &wsaData
    if (wsaError != 0)
    {
        cout << "Winsock dll not found!\n";
        WSACleanup(); // WSACleanup shuts down winsock and frees resources
    }
    else
    {
        cout << "Winsock dll found.\n";
        cout << "Status : " << wsaData.szSystemStatus << endl;
    }
    SOCKET serverSocket; // data type representing a socket
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // creates socket
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Invallid socket!\n";
        cout << WSAGetLastError() << endl; // returns winsock error code from last function
        WSACleanup();
    }
    else
    {
        cout << "Socket is ok.\n";
    }
    sockaddr_in address;                              // struct holding IP address and port
    address.sin_family = AF_INET;                     // address family. AF_INET for IPv4. AF_INET6 for IPv6
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // converts string to binary address. 127.0.0.1 is loop-back address. packet goes to router and it returns the packet
    address.sin_port = htons(55555);                  // host to network short. changes byte order. big endian

    if (bind(serverSocket, reinterpret_cast<SOCKADDR *>(&address), sizeof(address)) == SOCKET_ERROR) // binds address to socket. reinterpret_cast casts address into correct format
    {
        cout << "Bind failed!\n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Bind successful.\n";
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) // listen for connections. 1 is backlog
    {
        cout << "Failed to listen!\n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Listening for connection.\n";
    }
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, nullptr, nullptr); // accept connection. next two parameters mean we dont care about client address
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "accept failed: \n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "accept() is OK!\n";
    }
    char receiveBuffer[200];                                           // buffer for recieved data
    int recievedByteCount = recv(acceptSocket, receiveBuffer, 200, 0); // recieve data into buffer, max size, flags
    if (recievedByteCount < 0)
    {
        cout << "Server recv error: \n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Received data: " << receiveBuffer << endl;
    }
    char buffer[200];
    cout << "Enter the message: ";
    cin.getline(buffer, 200);
    int sentByteCount = send(acceptSocket, buffer, 200, 0); // send data from buffer, max size, flags
    if (sentByteCount == SOCKET_ERROR)
    {
        cout << "Server send error: \n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Server: Sent " << sentByteCount << " bytes.\n";
    }
    WSACleanup();

    return 0;
}