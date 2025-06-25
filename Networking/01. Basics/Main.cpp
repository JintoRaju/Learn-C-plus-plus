#include <iostream>

/*
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
Modern applications often need to:
- Communicate across machines (e.g., web browsers, games, databases)
- Send and receive data over networks (e.g., HTTP, chat servers)
- Build client-server applications (e.g., FTP, SSH)

To do this efficiently, we must understand the **fundamentals of networking**:
O How machines communicate using IP & Ports
O What a socket is, and why it's needed
O TCP vs UDP — tradeoffs and use cases
O How to write networking code using POSIX sockets (on Linux)

================================================================================
TOPICS COVERED IN THIS FILE:
1. What is a network?
2. IP address, port, and endpoint
3. Client-server model
4. Sockets and socket API (POSIX)
5. TCP vs UDP differences
6. How a basic socket call looks
================================================================================
*/

// =============================================================================
// 1. WHAT IS A NETWORK?
// =============================================================================
// A network allows machines (nodes) to communicate with each other
// over a shared medium (e.g., LAN, WiFi, internet).
// The Internet is a huge network of interconnected computers.

// =============================================================================
// 2. IP ADDRESS AND PORT
// =============================================================================
// - IP Address: Identifies a device on a network (like a phone number)
//     e.g., 192.168.1.12 or 127.0.0.1 (localhost)
// - Port: Identifies an application/service on that device
//     e.g., 80 (HTTP), 22 (SSH), 443 (HTTPS)
// So: IP + Port = endpoint (like a full address: house + apartment number)

// =============================================================================
// 3. CLIENT-SERVER MODEL
// =============================================================================
// Server:
// - Listens on a port (binds to a socket)
// - Accepts incoming connections
// - Processes and responds to client requests
//
// Client:
// - Connects to a server’s IP and port
// - Sends request, waits for response

// =============================================================================
// 4. SOCKETS — THE GATEWAY TO NETWORK
// =============================================================================
// A socket is an endpoint for communication
// Think of it as a file descriptor, but for networks

// POSIX Socket API (on Linux):
// ------------------------------------------
// socket()        => create a socket
// bind()          => associate socket with port (server side)
// connect()       => connect to server (client side)
// listen()        => mark socket as passive (server side)
// accept()        => accept incoming connection (server side)
// send()/recv()   => send or receive data (TCP)
// sendto()/recvfrom() => for UDP (connectionless)
// close()         => close the socket

// =============================================================================
// 5. TCP VS UDP
// =============================================================================
//
// TCP (Transmission Control Protocol):
// - Connection-oriented
// - Reliable (guarantees order, delivery, no duplication)
// - Slower due to overhead
// - Used in: web (HTTP), file transfer (FTP), SSH
//
// UDP (User Datagram Protocol):
// - Connectionless
// - Unreliable (no guarantee of delivery/order)
// - Very fast, minimal overhead
// - Used in: real-time games, VoIP, DNS

// =============================================================================
// 6. HOW A BASIC SOCKET CALL LOOKS (TCP CLIENT)
// =============================================================================
/*
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int sockfd = socket(AF_INET, SOCK_STREAM, 0);   // Create TCP socket

sockaddr_in serverAddr{};
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(8080);
inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

connect(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr));  // connect to server

send(sockfd, "Hello", 5, 0);                    // send data
recv(sockfd, buffer, sizeof(buffer), 0);       // receive data

close(sockfd);
*/
// We'll write this full program in the next file.


int main() {
    std::cout << "This file explains core networking concepts.\n";
    std::cout << "Next, we'll begin with a real UDP client/server using POSIX sockets.\n";
    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
POSIX Sockets:
- Introduced in BSD Unix in early 1980s
- Standardized API for networking in Linux/C++

C++:
- No native socket API in C++ standard as of C++20
- We use C system calls: <sys/socket.h>, <netinet/in.h>, etc.

================================================================================
WHAT'S NEXT?
================================================================================
In Networking_02_UDP_Client_Server.cpp, we'll:
- Write a real UDP echo client & server using POSIX sockets
- Understand socket(), bind(), sendto(), recvfrom()

From there, we’ll go to TCP, non-blocking, select/poll, SSL/TLS, etc.
*/
