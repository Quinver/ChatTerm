#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <cstddef>

class NetworkUtils {
public:
    // Method declarations
    static void sendMessage(const char* message, int socket);
    static void receiveMessage(int socket, char* buffer, size_t bufferSize);
};

#endif // NETWORK_UTILS_H
