#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

/*
================================================================================
NETWORKING_07_THREADPOOL_SERVER.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Spawning a new thread per client doesn't scale — OS will choke with 1000+ threads
O We need a fixed number of threads (thread pool) that:
   - Wait for client connections (tasks)
   - Process tasks from a shared queue
O Used in real-world scalable servers like NGINX, MySQL, etc.

This file:
O Builds a basic TCP server with a fixed thread pool
O Uses a shared task queue with mutex and condition_variable

================================================================================
TOPICS COVERED:
1. Thread pool (workers + task queue)
2. TCP client connections as tasks
3. Handling echo service using pooled threads
================================================================================
*/

// =============================================================================
// CONFIG
// =============================================================================
constexpr int PORT = 9094;
constexpr int BUFFER_SIZE = 1024;
constexpr int THREAD_POOL_SIZE = 4;

// =============================================================================
// TASK QUEUE + THREAD POOL
// =============================================================================
queue<int> task_queue;               // Stores client sockets
mutex queue_mutex;
condition_variable cv;

// Thread function — worker waits for client sockets to appear in queue
void worker(int id) {
    while (true) {
        int client_fd = -1;

        // Scope: lock queue
        {
            unique_lock<mutex> lock(queue_mutex);
            cv.wait(lock, [] { return !task_queue.empty(); });

            client_fd = task_queue.front();
            task_queue.pop();
        }

        cout << "[Worker " << id << "] Handling client: FD " << client_fd << "\n";

        char buffer[BUFFER_SIZE];
        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            ssize_t bytes = recv(client_fd, buffer, BUFFER_SIZE, 0);
            if (bytes <= 0) break;
            send(client_fd, buffer, bytes, 0);  // Echo back
        }

        close(client_fd);
        cout << "[Worker " << id << "] Client done.\n";
    }
}

// =============================================================================
// MAIN SERVER FUNCTION
// =============================================================================
void threadpool_server() {
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

    if (listen(server_fd, 20) < 0) {
        perror("listen() failed");
        close(server_fd);
        return;
    }

    cout << "[Server] Listening on port " << PORT << "\n";

    // Start worker threads
    vector<thread> workers;
    for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
        workers.emplace_back(worker, i + 1);
        workers.back().detach(); // Let them run independently
    }

    // Accept loop — push incoming sockets to queue
    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("accept() failed");
            continue;
        }

        {
            lock_guard<mutex> lock(queue_mutex);
            task_queue.push(client_fd);
        }
        cv.notify_one(); // Wake up one waiting worker
    }

    close(server_fd);
}

// =============================================================================
// MAIN
// =============================================================================
int main() {
    threadpool_server();
    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- std::thread, std::mutex, std::condition_variable introduced

C++17:
- Structured bindings and scoped_lock (not used here yet)

C++20:
- Coroutines can be used to build async pools (advanced topic)

================================================================================
BEST PRACTICES
================================================================================
- Always protect shared queue with mutex + condition_variable
- Never hold lock while processing task (lock, pop, unlock, then process)
- Don’t spawn unbounded threads — use fixed-size pool
- Close sockets to avoid FD leaks
- Use thread-safe logging in production (this uses cout for simplicity)

================================================================================
WHY THREAD POOL IS BETTER THAN PER-THREAD MODEL
================================================================================
- Memory: 1000 threads use ~1GB stack vs 4 threads in pool
- Performance: OS scheduler overhead is minimized
- Scalability: Servers with 1000s of clients only need 4–32 threads
- Stability: Thread pools prevent accidental DoS by spawning too many threads
*/
