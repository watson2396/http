#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "message.h"

#pragma comment(lib, "ws2_32.lib") //Winsock Library
#define DEFAULT_PORT "42069"


int recv_messages(SOCKET* ClientSocket) 
{
    int retResult;
    int sendResult;
    char recvBuf[DEFAULT_BUFLEN];
    int recvBufLen = DEFAULT_BUFLEN;

    char outBuf[DEFAULT_BUFLEN];
    int outBufLen = DEFAULT_BUFLEN;

    printf("start listening to port\n");
    do {

        retResult = recv(ClientSocket, recvBuf, recvBufLen, 0);
        if (retResult > 0) 
        {
            // Echo the buffer back to the sender
            sendResult = send(ClientSocket, recvBuf, retResult, 0);

            if (sendResult == SOCKET_ERROR) {
                printf("send failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            Message* message = message_create();
            if (message_parse(&message, &recvBuf, retResult) != 0) {printf("shit went sideways somewhere; skipping message"); continue;};

            printf("Bytes sent: %d\n", sendResult);
        } 
        else if (retResult == 0) 
        {
            printf("Connection closing...\n");
        } 
        else 
        {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return -1;
        }

    } while (retResult > 0);
}

int main(int argc, char const* argv[])
{
    printf("Hello, World\n");
    WSADATA wsaData;
    int retResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *addrResult = NULL;
    struct addrinfo hints;


    retResult = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (retResult != 0) 
    {
        printf("failed initialising Winsock, err: %d\n", retResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    retResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &addrResult);
    if (retResult != 0) 
    {
        printf("getaddrinfo failed: %d\n", retResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections
    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) 
    {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    retResult = bind( ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (retResult == SOCKET_ERROR) 
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(addrResult);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(addrResult);

    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) 
    {
        printf( "Listen failed with error: %d\n", WSAGetLastError() );
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    if (recv_messages(&ClientSocket) != 0) 
    {
        return 1;
    }

    // shutdown the send half of the connection since no more data will be sent
    retResult = shutdown(ClientSocket, SD_SEND);
    if (retResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    WSACleanup();
    return 0;
}





