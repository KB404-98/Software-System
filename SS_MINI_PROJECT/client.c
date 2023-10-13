#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in serverAddress;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    printf("Socket created successfully..\n");

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Connection failed");
        close(client_socket);
        exit(1);
    }
    printf("Successfully connected to the server\n");

    char buffer[BUFFER_SIZE];
    while (1) {
        // Receive data from the server
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            perror("Error receiving data");
            break;
        }
        // Process and display received data
        printf("%s", buffer);

        // Send a response
        char message[BUFFER_SIZE];
        memset(message,0,sizeof(message));
        scanf("%s", message);  // Use scanf to get input from the user
        send(client_socket, message, strlen(message), 0);
    }

    // Close the socket
    close(client_socket);

    return 0;
}
