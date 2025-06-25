#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

/*
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O In TCP, each client uses a dedicated connection.
O If one client blocks or takes long to respond, others get delayed.
O Multithreading allows:
   - Handling each client independently
   - Parallelism across CPU cores
   - Non-blocking behavior per connection (e.g., chat server, file server)

This file:
O Builds a basic multi-client TCP server
O Launches a new thread per client
O Demonstrates `std::thread` and socket lifetime

================================================================================
TOPICS COVERED:
1. Accepting multiple clients via `accept()`
2. Spawning `std::thread` for each client
3. Gracefully handling client disconnects
================================================================================
*/

// =============================================================================
// CONFIGURATION
// =============================================================================
constexpr int PORT = 9093;
constexpr int BUFFER_SIZE = 1024;

// =============================================================================
// THREAD FUNCTION FOR EACH CLIENT
// =============================================================================
void handle_client(int client_fd, int client_id) {
    char buffer[BUFFER_SIZE];
    cout << "[Thread " << client_id << "] Client handler started.\n";

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes = recv(client_fd, buffer, BUFFER_SIZE, 0);

        if (bytes <= 0) {
            cout << "[Thread " << client_id << "] Client disconnected.\n";
            break;
        }

        cout << "[Thread " << client_id << "] Received: " << buffer << "\n";
        send(client_fd, buffer, bytes, 0); // Echo back
    }

    close(client_fd);
}

// =============================================================================
// MAIN TCP SERVER FUNCTION
// =============================================================================
void multithreaded_tcp_server() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
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

    if (listen(server_fd, 10) < 0) {
        perror("listen() failed");
        close(server_fd);
        return;
    }

    cout << "[Server] Listening on port " << PORT << "...\n";

    int client_id = 0;
    vector<thread> threads;

    while (true) {
        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        int client_fd = accept(server_fd, (sockaddr*)&client_addr, &addrlen);

        if (client_fd < 0) {
            perror("accept() failed");
            continue;
        }

        ++client_id;
        cout << "[Server] Accepted client #" << client_id << "\n";

        threads.emplace_back(handle_client, client_fd, client_id);
        threads.back().detach(); // or join() if you want to wait
    }

    close(server_fd);
}

// =============================================================================
// MAIN
// =============================================================================
int main() {
    multithreaded_tcp_server();
    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
POSIX sockets:
- Still used in multithreaded servers for decades
- C APIs still dominate for low-level socket control

C++11 and Beyond:
- Introduced std::thread — clean cross-platform threading
- This program requires C++11 or higher

================================================================================
BEST PRACTICES
================================================================================
- Use `std::thread` to isolate client handling
- Use `detach()` if you're okay with threads running independently
- Use `join()` if you want to wait for each thread (e.g., in worker pools)
- Always `close()` the socket when done
- Protect shared resources with `std::mutex` if needed (not required here)
- Don't spawn infinite threads in real apps — use thread pool libraries for scale
*/
