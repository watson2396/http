#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>


#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library
#define PORT 6969

// https://learn.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock
// https://learn.microsoft.com/en-us/windows/win32/winsock/complete-server-code
// Server
int main(int argc, char const* argv[])
{
    printf("Hello, World");
    int result;

    SOCKET s;

    printf("initialising Winsock");
    WSADATA wsaData;
    result = WSAStartup(MAKEWORD(2, 0), &wsaData)
    if (result != 0) {
        printf("failed initialising Winsock, err: %d\n", result);
        return 1;
    }

    // connect to socket

    // wait for incoming request on socket

    WSACleanup();

    return 0;
}





