#include "../lib/NetworkUtils.h"
#include <iostream>
#include <cstring>  // For strlen, strcpy, etc.
#include <sys/socket.h>  // For socket operations
#include <unistd.h>  // For close()

// Method to send a message to the server
void NetworkUtils::sendMessage(const char* message, int socket) {
    send(socket, message, strlen(message), 0); // Send the message over the socket
}

// Method to receive a message from the server
void NetworkUtils::receiveMessage(int socket, char* buffer, size_t bufferSize) {
    recv(socket, buffer, bufferSize, 0); // Receive message into the buffer
}

