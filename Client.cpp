#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

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
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Invallid socket!\n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Socket is ok.\n";
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(55555);
    if (connect(clientSocket, reinterpret_cast<SOCKADDR *>(&address), sizeof(address)) == SOCKET_ERROR) // connect to server with given address and port
    {
        cout << "Client: connect() - Failed to connect: \n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Client: Connect() is OK!\n";
        cout << "Client: Can start sending and receiving data...\n";
    }
    char buffer[200];
    cout << "Enter the message: ";
    cin.getline(buffer, 200);
    int sbyteCount = send(clientSocket, buffer, 200, 0);
    if (sbyteCount == SOCKET_ERROR)
    {
        cout << "Client send error: \n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Client: Sent " << sbyteCount << " bytes.\n";
    }
    char receiveBuffer[200];
    int rbyteCount = recv(clientSocket, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
        cout << "Client recv error: \n";
        cout << WSAGetLastError() << endl;
        WSACleanup();
    }
    else
    {
        cout << "Client: Received data: " << receiveBuffer << endl;
    }
    WSACleanup();

    return 0;
}