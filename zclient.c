#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link with the Winsock library

#define PORT 13 //13
#define IP "192.168.1.193"
#define MAX_BUFFER_SIZE 1024

// gcc -o zclient zclient.c -lws2_32
int main() {
    WSADATA wsaData;
    SOCKET client_fd;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return -1;
    }

    // Create a socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return -1;
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed.\n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    // Receive the date and time from the server
    ssize_t len = recv(client_fd, buffer, sizeof(buffer)-1, 0);
    if (len == SOCKET_ERROR) {
        printf("Receive failed.\n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    buffer[len] = '\0';  // Null-terminate the received string
    printf("Received date from server: %s\n", buffer);

    // Close the connection
    closesocket(client_fd);

    // Cleanup Winsock
    WSACleanup();
    return 0;
}
