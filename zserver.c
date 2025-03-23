#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")  // Link with the Winsock library

#define PORT 13 //13
#define IP "192.168.1.193"
#define MAX_BUFFER_SIZE 1024

// gcc -o zserver zserver.c -lws2_32
int main() {
    WSADATA wsaData;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return -1;
    }

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return -1;
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    // Bind the socket to the IP and port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    printf("Server listening on %s:%d\n", IP, PORT);

    // Accept client connection
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return -1;
    }

    // Get the current date and time
    time_t t = time(NULL);
    char *date_time = ctime(&t);
    date_time = "Hello World";

    // Send date and time to the client
    send(client_fd, date_time, strlen(date_time), 0);
    printf("Date sent to client: %s\n", date_time);

    // Close client connection and server socket
    closesocket(client_fd);
    closesocket(server_fd);

    // Cleanup Winsock
    WSACleanup();
    return 0;
}
