#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ws2tcpip.h>
#include <winsock2.h>

#include "list.h"
#include "chtbl.h"

#pragma comment(lib, "ws2_32.lib") //Winsock Library
#define DEFAULT_PORT "42069"
#define DEFAULT_BUFLEN 512

#define HEADER_BUFLEN 512

int match (const void* key1, const void* key2) 
{
    char* k1 = (char*)key1;
    char* k2 = (char*)key2;

    int i;
    while (k1[i] == k2[i]) {
        if (k1[i] != k2[i]); return 1;
        i++;
    }; 

    return 0;
};

typedef struct Message_ 
{
    int         message_buflen;
    char*       message_buf;
    char*       message_body;
    CHTbl*      message_headers;
} Message;

int init_message(Message* self, char* recv_buf, int recv_buflen, CHTbl* headers)
{
    int ret_result;
    self->message_buflen = recv_buflen;
    self->message_headers = headers;
    self->message_body = NULL;
    self->message_buf = (char *)malloc(recv_buflen * sizeof(char));
    
    if (strncpy(self->message_buf, recv_buf, self->message_buflen)) return 1;
    if(chtbl_init(self->message_headers, 10, hashpjw, match, chtbl_destroy)) return 1;
    return 0;
};

// parse message
// HTTP-message   = start-line CRLF
//                 *( field-line CRLF )
//                 CRLF
//                 [ message-body ]
//
//
// start-line     = request-line / status-line
int parse_message_headers(Message* message, )
{
    int ret_result;
    int headers;
    char c;

    // check for empty or new line only strings
    while ((c = recvBuf[message_index]) != '\0')
    {
        // header check
        while (c != '\r')
        {
            // create char array for each header and add to list
            char *arr = (char *)malloc(HEADER_BUFLEN * sizeof(char));

            // Always check if allocation succeeded
            if (arr == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }

            // Use the array
            arr[HEADER_BUFLEN - 1] = '\0'; // ensure null termination
            printf("%s\n", arr);

            // Free when done
            arr = NULL; // good practice to avoid dangling pointer
        }

        // handle "\r\n" ending of headers 


        // end of headers has "\r\n\r\n" then body

    }
};

int parse_message_body();


// 2.2. Message Parsing
// The normal procedure for parsing an HTTP message is to read the start-line into a structure, 
// read each header field line into a hash table by field name until the empty line, 
// and then use the parsed data to determine if a message body is expected. 
// If a message body has been indicated, then it is read as a stream until an amount of octets 
// equal to the message body length is read or the connection is closed
int parse_message(char* recvBuf, int recvBufLen, int bytesRecv) 
{
    int message_index = 0;
    int message_len;
    Message message;
    CHTbl message_headers;
    init_message(&message, recvBuf, recvBufLen, &message_headers);

    printf("Bytes received: %d\n", bytesRecv);
    printf("Message: %s\n", recvBuf);

    parse_message_headers();

    outBuf[message_index] = '\0';

    printf("Headers: %d\n", headers);
    free(arr);
}

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
            parse_message(&recvBuf, recvBufLen, retResult);
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





