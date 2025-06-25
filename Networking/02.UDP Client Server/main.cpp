#include <iostream>
#include <cstring>      // For memset
#include <unistd.h>     // For close()
#include <arpa/inet.h>  // For inet_pton, htons
#include <sys/socket.h> // For socket APIs
using namespace std;

/*
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
UDP (User Datagram Protocol) is useful when:
 Speed is more important than reliability
 You need connectionless communication
 You’re building DNS, VoIP, real-time games, sensor networks, etc.

This program:
 Builds a simple echo server and client using UDP
 Demonstrates POSIX socket functions: socket(), bind(), sendto(), recvfrom()
 Explains how data is transmitted without a connection

================================================================================
TOPICS COVERED:
1. UDP server that listens for incoming messages and echoes them back
2. UDP client that sends a message and prints the echoed reply
================================================================================
*/

// =============================================================================
// CONFIGURATION
// =============================================================================
constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;
constexpr const char* LOCALHOST = "127.0.0.1";

// =============================================================================
// UDP SERVER
// =============================================================================
void udp_server() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // UDP socket
    if (sockfd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);               // Host to network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY;         // Listen on all interfaces

    if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind() failed");
        close(sockfd);
        return;
    }

    cout << "[UDP Server] Listening on port " << PORT << "...\n";

    char buffer[BUFFER_SIZE];
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                    (sockaddr*)&client_addr, &client_len);

        if (recv_len < 0) {
            perror("recvfrom() failed");
            continue;
        }

        cout << "[Server] Received: " << buffer << "\n";

        // Echo back
        sendto(sockfd, buffer, recv_len, 0,
               (sockaddr*)&client_addr, client_len);
    }

    close(sockfd); // Never reached in this infinite loop
}

// =============================================================================
// UDP CLIENT
// =============================================================================
void udp_client(const string& message) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, LOCALHOST, &server_addr.sin_addr);

    // Send message to server
    sendto(sockfd, message.c_str(), message.length(), 0,
           (sockaddr*)&server_addr, sizeof(server_addr));

    // Receive echoed message
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);
    ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                (sockaddr*)&server_addr, &addr_len);

    if (recv_len > 0) {
        buffer[recv_len] = '\0'; // Null-terminate
        cout << "[Client] Received from server: " << buffer << "\n";
    } else {
        perror("recvfrom() failed");
    }

    close(sockfd);
}

// =============================================================================
// MAIN — Choose client or server
// =============================================================================
int main(int argc, char* argv[]) {
    if (argc >= 2 && string(argv[1]) == "server") {
        udp_server();
    } else if (argc == 3 && string(argv[1]) == "client") {
        udp_client(argv[2]); // argv[2] = message
    } else {
        cout << "Usage:\n";
        cout << "  " << argv[0] << " server\n";
        cout << "  " << argv[0] << " client <message>\n";
    }

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
POSIX Sockets:
- APIs used: socket(), bind(), sendto(), recvfrom(), close()

C++ Standards:
- This code is portable C++03–C++20 (no stdlib changes here)
- No STL sockets — only POSIX

================================================================================
BEST PRACTICES
================================================================================
- Use UDP for small, fast, stateless communication
- Always check return values of sendto/recvfrom
- Be ready to handle packet loss or duplication in UDP (not handled here)
- Always zero out sockaddr_in before using
- Use `inet_pton` instead of `inet_addr` for IPv4/IPv6 support
- Use larger buffer size for bigger payloads (check MTU)
*/
