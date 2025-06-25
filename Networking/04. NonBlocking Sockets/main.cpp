#include <iostream>
#include <cstring>
#include <unistd.h>         // For close(), read()
#include <fcntl.h>          // For fcntl()
#include <arpa/inet.h>      // For inet_pton
#include <sys/socket.h>
using namespace std;

/*
================================================================================
NETWORKING_04_NONBLOCKING_SOCKETS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O By default, socket I/O is *blocking*
    - recv() blocks until data arrives
    - accept() blocks until a client connects

O But in many cases, we need to:
    - Avoid blocking the main thread
    - Handle multiple sockets concurrently (e.g., in GUI apps, servers)
    - Integrate with event loops (select/poll/epoll)

O Non-blocking sockets solve this by letting syscalls return immediately.

================================================================================
TOPICS COVERED:
1. How to set O_NONBLOCK using fcntl()
2. Behavior of recv() and accept() in non-blocking mode
3. What errors to expect and how to handle them
================================================================================
*/

// =============================================================================
// SET A SOCKET TO NON-BLOCKING MODE USING fcntl()
// =============================================================================
bool set_nonblocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) return false;

    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
        return false;

    return true;
}

// =============================================================================
// SIMPLE NON-BLOCKING TCP SERVER (1 client, no threading)
// =============================================================================
void nonblocking_tcp_server() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9091);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind() failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen() failed");
        close(server_fd);
        return;
    }

    if (!set_nonblocking(server_fd)) {
        perror("fcntl() failed");
        close(server_fd);
        return;
    }

    cout << "[Server] Waiting for client (non-blocking accept)...\n";

    int client_fd = -1;
    while (client_fd < 0) {
        client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                cout << "[Server] No client yet... retrying\n";
                usleep(500000); // sleep 0.5 sec
            } else {
                perror("accept() failed");
                close(server_fd);
                return;
            }
        }
    }

    cout << "[Server] Client connected!\n";

    if (!set_nonblocking(client_fd)) {
        perror("set_nonblocking(client_fd) failed");
        close(client_fd);
        close(server_fd);
        return;
    }

    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t n = recv(client_fd, buffer, sizeof(buffer), 0);

        if (n > 0) {
            cout << "[Server] Received: " << buffer << "\n";
            send(client_fd, buffer, n, 0); // Echo
        } else if (n == 0) {
            cout << "[Server] Client disconnected.\n";
            break;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                cout << "[Server] No data yet. Waiting...\n";
                usleep(500000);
            } else {
                perror("recv() failed");
                break;
            }
        }
    }

    close(client_fd);
    close(server_fd);
}

// =============================================================================
// TCP CLIENT (unchanged from previous)
// =============================================================================
void tcp_client(const string& message) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9091);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect() failed");
        close(sockfd);
        return;
    }

    send(sockfd, message.c_str(), message.size(), 0);
    char buffer[1024];
    ssize_t n = recv(sockfd, buffer, sizeof(buffer), 0);
    if (n > 0) {
        buffer[n] = '\0';
        cout << "[Client] Echo: " << buffer << "\n";
    }

    close(sockfd);
}

// =============================================================================
// MAIN — Choose client or server
// =============================================================================
int main(int argc, char* argv[]) {
    if (argc == 2 && string(argv[1]) == "server") {
        nonblocking_tcp_server();
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
fcntl (O_NONBLOCK):
- POSIX standard since early UNIX
- Still relevant in C++20 — no modern C++ wrapper in standard yet

C++ Status:
- No change in C++11/14/17/20 related to low-level sockets
- In C++23 and beyond, networking is being explored via std::net (experimental)

================================================================================
BEST PRACTICES
================================================================================
- Use non-blocking sockets when handling multiple connections without threads
- Always handle EAGAIN/EWOULDBLOCK — they mean "no data yet"
- Use select(), poll(), or epoll() for efficient readiness tracking (up next)
- Don’t mix blocking and non-blocking I/O on the same socket
- Combine with std::thread or coroutine libraries for scalable servers
*/
