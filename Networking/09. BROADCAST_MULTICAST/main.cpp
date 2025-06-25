#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

/*
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
✔ Normally, UDP messages go to a specific host
✔ What if we want to:
   - Send a message to all devices in a subnet? → ✅ Broadcast
   - Send to a group of subscribers only? → ✅ Multicast

This file:
✔ Shows how to send a **UDP broadcast** (255.255.255.255 or subnet-level)
✔ Explains the idea of multicast (basic concept & address range)

================================================================================
TOPICS COVERED:
1. Enabling broadcast on UDP socket
2. Sending broadcast message to 255.255.255.255 or subnet broadcast (e.g., 192.168.1.255)
3. Multicast address ranges and differences from broadcast
================================================================================
*/

constexpr int PORT = 9096;
constexpr int BUFFER_SIZE = 1024;

// =============================================================================
// BROADCAST SENDER FUNCTION
// =============================================================================
void send_broadcast(const string& msg) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket() failed");
        return;
    }

    // Enable socket option for broadcast
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt() failed");
        close(sockfd);
        return;
    }

    sockaddr_in broadcast_addr{};
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "255.255.255.255", &broadcast_addr.sin_addr); // OR your subnet like 192.168.1.255

    sendto(sockfd, msg.c_str(), msg.length(), 0,
           (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));

    cout << "[Broadcast Sender] Sent: " << msg << "\n";

    close(sockfd);
}

// =============================================================================
// BROADCAST RECEIVER FUNCTION
// =============================================================================
void receive_broadcast() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket() failed");
        return;
    }

    sockaddr_in recv_addr{};
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (sockaddr*)&recv_addr, sizeof(recv_addr)) < 0) {
        perror("bind() failed");
        close(sockfd);
        return;
    }

    cout << "[Broadcast Receiver] Listening on port " << PORT << "...\n";

    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, nullptr, nullptr);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            cout << "[Broadcast Receiver] Received: " << buffer << "\n";
        }
    }

    close(sockfd);
}

// =============================================================================
// MAIN
// =============================================================================
int main(int argc, char* argv[]) {
    if (argc == 2 && string(argv[1]) == "recv") {
        receive_broadcast();
    } else if (argc == 3 && string(argv[1]) == "send") {
        send_broadcast(argv[2]);
    } else {
        cout << "Usage:\n";
        cout << "  " << argv[0] << " recv\n";
        cout << "  " << argv[0] << " send <message>\n";
    }

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
POSIX:
- Broadcast via UDP available in all Linux versions
- SO_BROADCAST required to enable broadcast on the socket

================================================================================
MULTICAST NOTES (Concept Only Here)
================================================================================
Multicast:
- Sends to a multicast group IP (224.0.0.0 to 239.255.255.255)
- Used in IPTV, video conferencing, routing protocols (e.g., OSPF)
- Requires IGMP (Internet Group Management Protocol)
- Usually requires router configuration

Broadcast vs Multicast:
- Broadcast = all devices in subnet
- Multicast = only subscribed devices in group
- Multicast is more efficient at scale, but needs more setup

================================================================================
BEST PRACTICES
================================================================================
- Use broadcast for discovery (e.g., printers, games)
- Don’t flood the network — use sparingly
- Consider multicast or unicast for scale
- Always enable SO_BROADCAST before using 255.255.255.255
- You can use subnet-level broadcast (e.g., 192.168.1.255)

*/
