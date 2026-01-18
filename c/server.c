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
    int result;

    printf("initialising Winsock\n");
    WSADATA wsaData;
    result = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (result != 0) 
    {
        printf("failed initialising Winsock, err: %d\n", result);
        return 1;
    }

    //https://learn.microsoft.com/en-us/windows/win32/winsock/creating-a-socket-for-the-server
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;result = NULL, *ptr = NULL, hints;

    // Resolve the local address and port to be used by the server
    result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (result != 0) {
        printf("getaddrinfo failed: %d\n", result);
        WSACleanup();
        return 1;
    }

    // connect to socket
    SOCKET ListenSocket = INVALID_SOCKET;

    // wait for incoming request on socket

    WSACleanup();
    return 0;
}





