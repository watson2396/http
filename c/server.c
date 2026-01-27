#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library
#define PORT 6969
#define DEFAULT_PORT "27015"

// https://learn.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock
// https://learn.microsoft.com/en-us/windows/win32/winsock/complete-server-code
// Server
int main(int argc, char const* argv[])
{
    printf("Hello, World\n");
    int iResult;

    printf("initialising Winsock\n");
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (iResult != 0) 
    {
        printf("failed initialising Winsock, err: %d\n", iResult);
        return 1;
    }

    //https://learn.microsoft.com/en-us/windows/win32/winsock/creating-a-socket-for-the-server
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ListenSocket = INVALID_SOCKET;

    // Create a SOCKET for the server to listen for client connections
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    //https://learn.microsoft.com/en-us/windows/win32/winsock/listening-on-a-socket

    // wait for incoming request on socket

    WSACleanup();
    return 0;
}





