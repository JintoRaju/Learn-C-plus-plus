#include <iostream>
#include <cstring>      // For memset
#include <unistd.h>     // For close()
#include <arpa/inet.h>  // For inet_pton, htons
#include <sys/socket.h> // For socket APIs
using namespace std;

/*
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
 TCP (Transmission Control Protocol) is reliable and ordered
 Used in web servers, SSH, FTP, HTTPS — almost everything critical
 Unlike UDP, TCP ensures data is delivered intact and in order

This program demonstrates:
 TCP server that accepts incoming connections and echoes back messages
 TCP client that connects, sends message, and waits for response

================================================================================
TOPICS COVERED:
1. Server side: socket(), bind(), listen(), accept(), send(), recv()
2. Client side: socket(), connect(), send(), recv()
3. Connection-oriented behavior
================================================================================
*/

// =============================================================================
// CONFIGURATION
// =============================================================================
constexpr int PORT = 9090;
constexpr int BUFFER_SIZE = 1024;
constexpr const char* LOCALHOST = "127.0.0.1";

// =============================================================================
// TCP SERVER
// =============================================================================
void tcp_server() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);  // TCP socket
    if (server_fd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind() failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 5) < 0) {  // Up to 5 pending connections
        perror("listen() failed");
        close(server_fd);
        return;
    }

    cout << "[TCP Server] Listening on port " << PORT << "...\n";

    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept() failed");
        close(server_fd);
        return;
    }

    cout << "[Server] Client connected.\n";

    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) break;

        cout << "[Server] Received: " << buffer << "\n";

        send(client_fd, buffer, bytes_received, 0); // Echo back
    }

    close(client_fd);
    close(server_fd);
}

// =============================================================================
// TCP CLIENT
// =============================================================================
void tcp_client(const string& message) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, LOCALHOST, &server_addr.sin_addr);

    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect() failed");
        close(sockfd);
        return;
    }

    send(sockfd, message.c_str(), message.length(), 0);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        cout << "[Client] Received from server: " << buffer << "\n";
    }

    close(sockfd);
}

// =============================================================================
// MAIN — Choose client or server
// =============================================================================
int main(int argc, char* argv[]) {
    if (argc >= 2 && string(argv[1]) == "server") {
        tcp_server();
    } else if (argc == 3 && string(argv[1]) == "client") {
        tcp_client(argv[2]);
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
- TCP uses SOCK_STREAM instead of SOCK_DGRAM (UDP)
- Accepts connections using listen() + accept()

C++ Standards:
- This is valid from C++03 through C++20
- No std sockets yet — we're using Linux system calls

================================================================================
KEY DIFFERENCES VS UDP
================================================================================
- TCP is connection-oriented, blocking: server must accept()
- recv() returns 0 when the client closes connection
- TCP ensures reliability, but adds latency
- UDP is faster but less reliable — no ordering or retransmission

================================================================================
BEST PRACTICES
================================================================================
- Always check return values of socket functions
- Handle partial sends/receives in production code (not shown here)
- Use threads or non-blocking I/O to handle multiple clients
- Prefer std::string or std::vector over raw buffers when possible
- Always close sockets to avoid descriptor leaks
*/
