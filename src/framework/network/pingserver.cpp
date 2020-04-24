#include "libtech/pingserver.h"

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_BUFLEN 512

bool initDone = false;
WSADATA wsaData;

void startpingserver()
{
    if(initDone == false)
    {
        int res = WSAStartup(MAKEWORD(2, 2), &wsaData);

        struct addrinfo *result = NULL, *ptr = NULL, hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the local address and port to be used by the server
        res = getaddrinfo(NULL, "3456", &hints, &result);
        if(res != 0)
        {
            printf("getaddrinfo failed: %d\n", res);
            WSACleanup();
        }

        SOCKET ListenSocket = INVALID_SOCKET;
        ListenSocket =
            socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if(ListenSocket == INVALID_SOCKET)
        {
            printf("Error at socket(): %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
        }

        res = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if(res == SOCKET_ERROR)
        {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
        }

        if(listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            printf("Listen failed with error: %ld\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
        }

        SOCKET ClientSocket;
        ClientSocket = INVALID_SOCKET;

        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if(ClientSocket == INVALID_SOCKET)
        {
            printf("accept failed: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
        }

        char recvbuf[DEFAULT_BUFLEN];
        int iResult, iSendResult;
        int recvbuflen = DEFAULT_BUFLEN;

        // Receive until the peer shuts down the connection
        do
        {
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if(iResult > 0)
            {
                printf("Bytes received: %d\n", iResult);

                // Echo the buffer back to the sender
                iSendResult = send(ClientSocket, recvbuf, iResult, 0);
                if(iSendResult == SOCKET_ERROR)
                {
                    printf("send failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
                printf("Bytes sent: %d\n", iSendResult);
            }
            else if(iResult == 0)
            {
                printf("Connection closing...\n");
            }
            else
            {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
            }

        } while(iResult > 0);

        initDone = true;

        closesocket(ClientSocket);
        WSACleanup();
    }
}

void stoppingserver() {}
#else
void startpingserver(){

};

void stoppingserver() {}

#endif
