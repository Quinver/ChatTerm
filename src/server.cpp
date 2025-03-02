#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

int serverSocket = -1;

// Signal handler function to close the socket
void handleSignal(int sig) {
  if (serverSocket != -1) {
    std::cout << "Closing socket due to signal " << sig << std::endl;
    close(serverSocket);
  }
  exit(0); // Exit the program after handling the signal
}
void *handleClient(void *clientSocket) {
  int socket = *((int *)clientSocket);
  char buffer[1024] = {0};
  recv(socket, buffer, sizeof(buffer), 0);
  std::cout << "Message from client: " << buffer << std::endl;

  const char *message = "Hello from server!";
  send(socket, message, strlen(message), 0);

  close(socket);
  return nullptr;
}

int main() {
  signal(SIGINT, handleSignal);
  signal(SIGTERM, handleSignal);

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0) {
    std::cout << "Bind failed." << std::endl;
    return -1;
  }

  // Start listening for connections
  if (listen(serverSocket, 5) < 0) {
    std::cout << "Listen failed." << std::endl;
    return -1;
  }

  int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket < 0) {
    std::cout << "Accept failed." << std::endl;
    return -1;
  }
  while (true) {
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    if (clientSocket == -1) {
      std::cout << "Client connection failed" << std::endl;
      continue;
    }

    pthread_t thread;
    pthread_create(&thread, nullptr, handleClient, (void *)&clientSocket);
    pthread_detach(thread);
  }

  close(serverSocket);
  return 0;
}
