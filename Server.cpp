#include <iostream>
#include <WinSock2.h>

using namespace std;

int main()
{
    WSADATA wsaData;
    int wsaError;
    wsaError = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaError != 0)
    {
        cout << "Winsock dll not found!\n";
        WSACleanup();
    }
    else
    {
        cout << "Winsock dll found.\n";
        cout << "Status : " << wsaData.szSystemStatus << endl;
    }
    SOCKET serverSocket;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Invallid socket!\n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(55555);

    if (bind(serverSocket, reinterpret_cast<SOCKADDR *>(&address), sizeof(address)) == SOCKET_ERROR)
    {
        cout << "Bind failed!\n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Bind successful.\n";
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR)
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
    acceptSocket = accept(serverSocket, nullptr, nullptr);
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
    char receiveBuffer[200];
    int recievedByteCount = recv(acceptSocket, receiveBuffer, 200, 0);
    if (recievedByteCount < 0)
    {
        cout << "Server recv error: \n";
        cout << WSAGetLastError() << endl;
    }
    else
    {
        cout << "Received data: " << receiveBuffer << endl;
    }
    char buffer[200];
    cout << "Enter the message: ";
    cin.getline(buffer, 200);
    int sentByteCount = send(acceptSocket, buffer, 200, 0);
    if (sentByteCount == SOCKET_ERROR)
    {
        cout << "Server send error: \n";
        cout << WSAGetLastError() << endl;
    }
    else
    {
        cout << "Server: Sent " << sentByteCount << " bytes.\n";
    }

    return 0;
}