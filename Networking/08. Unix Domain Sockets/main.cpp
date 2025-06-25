#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
using namespace std;

/*
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
✔ Sometimes, two processes on the same machine need to communicate.
✔ Using TCP/UDP loopback is slow and unnecessary.
✔ Unix Domain Sockets (UDS):
   - Use the filesystem as the address space (`/tmp/mysocket`)
   - Avoids IP overhead
   - Faster, secure, efficient for local-only communication

Used in:
✔ System daemons (e.g., Docker, X11, systemd)
✔ Fast IPC between apps
✔ Testing client/server without using a real network

================================================================================
TOPICS COVERED:
1. Creating a Unix domain socket server
2. Connecting with a client
3. Sending and receiving data
4. Using `AF_UNIX` and `SOCK_STREAM` for local TCP-like communication
================================================================================
*/

// =============================================================================
// SOCKET FILE NAME (must be filesystem path)
// =============================================================================
const char* SOCKET_PATH = "/tmp/mysocket_uds";

// =============================================================================
// SERVER FUNCTION
// =============================================================================
void uds_server() {
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket() failed");
        return;
    }

    // Remove old socket file if it exists
    unlink(SOCKET_PATH);

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

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

    cout << "[Server] Waiting for connection on " << SOCKET_PATH << "\n";

    int client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd < 0) {
        perror("accept() failed");
        close(server_fd);
        return;
    }

    char buffer[1024];
    ssize_t bytes = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        cout << "[Server] Received: " << buffer << "\n";

        string reply = "Hello from UDS server!";
        send(client_fd, reply.c_str(), reply.length(), 0);
    }

    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH); // Cleanup
}

// =============================================================================
// CLIENT FUNCTION
// =============================================================================
void uds_client(const string& msg) {
    int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (connect(client_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect() failed");
        close(client_fd);
        return;
    }

    send(client_fd, msg.c_str(), msg.length(), 0);

    char buffer[1024];
    ssize_t bytes = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        cout << "[Client] Reply: " << buffer << "\n";
    }

    close(client_fd);
}

// =============================================================================
// MAIN — Choose mode
// =============================================================================
int main(int argc, char* argv[]) {
    if (argc == 2 && string(argv[1]) == "server") {
        uds_server();
    } else if (argc == 3 && string(argv[1]) == "client") {
        uds_client(argv[2]);
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
POSIX:
- Unix Domain Sockets are a UNIX standard, available since early UNIX versions

C++:
- Works with any C++11/14/17/20 version (no changes required)

================================================================================
BEST PRACTICES
================================================================================
- Use UDS when both processes are on the same machine
- Always unlink old socket file before binding
- Permissions on socket files matter (can restrict access)
- Use SOCK_DGRAM for datagram-style UDS (like UDP)
- Use abstract namespace (starts with '\0') to avoid creating filesystem files
*/
