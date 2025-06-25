#include <iostream>
#include <vector>
#include <cstring>      // For memset
#include <unistd.h>     // For close()
#include <fcntl.h>      // For fcntl()
#include <arpa/inet.h>  // For inet_pton
#include <sys/socket.h>
#include <sys/select.h> // For select()
#include <poll.h>       // For poll()
using namespace std;

/*
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O When handling many clients using one thread, blocking on one socket is a waste.
O `select()` and `poll()` let us:
   - Wait for multiple sockets to become "ready"
   - Avoid busy waiting
   - Efficiently manage I/O in scalable servers

This file:
O Creates a simple server using both select() and poll()
O Shows how to monitor multiple file descriptors
O Helps build scalable single-threaded I/O servers

================================================================================
TOPICS COVERED:
1. select() — older, portable, limited (1024 sockets)
2. poll() — better design, scalable (no fixed FD_SET size)
================================================================================
*/

// =============================================================================
// HELPERS
// =============================================================================
constexpr int PORT = 9092;
constexpr int BUFFER_SIZE = 1024;
constexpr int MAX_CLIENTS = 10;

// Set a socket to non-blocking
bool set_nonblocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) return false;
    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) >= 0;
}

// =============================================================================
// SERVER USING select()
// =============================================================================
void server_using_select() {
    cout << "[select] Starting server...\n";
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);
    set_nonblocking(server_fd);

    fd_set master_set, read_set;
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    int max_fd = server_fd;

    while (true) {
        read_set = master_set; // Copy
        if (select(max_fd + 1, &read_set, nullptr, nullptr, nullptr) < 0) {
            perror("select");
            break;
        }

        for (int fd = 0; fd <= max_fd; ++fd) {
            if (!FD_ISSET(fd, &read_set)) continue;

            if (fd == server_fd) {
                // New connection
                int client_fd = accept(server_fd, nullptr, nullptr);
                if (client_fd > 0) {
                    set_nonblocking(client_fd);
                    FD_SET(client_fd, &master_set);
                    max_fd = max(max_fd, client_fd);
                    cout << "[select] Client connected: FD " << client_fd << "\n";
                }
            } else {
                // Existing client
                char buf[BUFFER_SIZE]{};
                int bytes = recv(fd, buf, BUFFER_SIZE, 0);
                if (bytes <= 0) {
                    cout << "[select] Client disconnected: FD " << fd << "\n";
                    FD_CLR(fd, &master_set);
                    close(fd);
                } else {
                    cout << "[select] Echoing: " << buf << "\n";
                    send(fd, buf, bytes, 0);
                }
            }
        }
    }

    close(server_fd);
}

// =============================================================================
// SERVER USING poll()
// =============================================================================
void server_using_poll() {
    cout << "[poll] Starting server...\n";
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);
    set_nonblocking(server_fd);

    vector<pollfd> poll_fds;
    poll_fds.push_back({server_fd, POLLIN, 0});

    while (true) {
        int ready = poll(poll_fds.data(), poll_fds.size(), -1);
        if (ready < 0) {
            perror("poll");
            break;
        }

        for (size_t i = 0; i < poll_fds.size(); ++i) {
            if (!(poll_fds[i].revents & POLLIN)) continue;

            if (poll_fds[i].fd == server_fd) {
                // New connection
                int client_fd = accept(server_fd, nullptr, nullptr);
                if (client_fd > 0) {
                    set_nonblocking(client_fd);
                    poll_fds.push_back({client_fd, POLLIN, 0});
                    cout << "[poll] Client connected: FD " << client_fd << "\n";
                }
            } else {
                // Existing client
                char buf[BUFFER_SIZE]{};
                int bytes = recv(poll_fds[i].fd, buf, BUFFER_SIZE, 0);
                if (bytes <= 0) {
                    cout << "[poll] Client disconnected: FD " << poll_fds[i].fd << "\n";
                    close(poll_fds[i].fd);
                    poll_fds.erase(poll_fds.begin() + i);
                    --i;
                } else {
                    cout << "[poll] Echoing: " << buf << "\n";
                    send(poll_fds[i].fd, buf, bytes, 0);
                }
            }
        }
    }

    close(server_fd);
}

// =============================================================================
// MAIN — Choose implementation
// =============================================================================
int main(int argc, char* argv[]) {
    if (argc == 2) {
        if (string(argv[1]) == "select") {
            server_using_select();
        } else if (string(argv[1]) == "poll") {
            server_using_poll();
        } else {
            cout << "Invalid option\n";
        }
    } else {
        cout << "Usage: ./app select | poll\n";
    }

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
select():
- POSIX standard, supported everywhere
- Limited to FD_SETSIZE (typically 1024)

poll():
- Scalable, no FD limit
- Preferred for new apps when available

C++:
- These are C APIs, usable in C++11–C++20
- C++ has no standard I/O multiplexing library yet

================================================================================
BEST PRACTICES
================================================================================
- Use `select()` for small-scale or portable code
- Use `poll()` or `epoll()` for high-performance scalable servers
- Always use non-blocking sockets with select/poll
- Always check return values
- Don’t forget to remove disconnected FDs from the set/vector
*/
