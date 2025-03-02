#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h> // For close()

int main() {
  // Create socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (clientSocket < 0) {
    perror("Socket creation failed");
    return 1;
  }
  // Define server address
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);                   // Server port
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

  // Connect to server
  if (connect(clientSocket, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) == -1) {
    std::cout << "Connection failed" << std::endl;
    close(clientSocket);

    return -1;
  }

  // Send message to server
  const char *message = "Hello, Server!";
  send(clientSocket, message, strlen(message), 0);

  // Close the socket
  close(clientSocket);

  return 0;
}
