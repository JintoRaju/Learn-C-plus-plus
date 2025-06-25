#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

/*
================================================================================
C++ CONCURRENCY: std::thread BASICS (C++11)
================================================================================
This file explains:
- Why std::thread is needed
- How to launch, join, and detach threads
- What joinable() means
- Best practices and common mistakes
- Version-specific notes
*/

// =====================================================================
// WHY std::thread?
// =====================================================================
// Suppose you have a function that takes time (e.g., logging, downloading).
// Running it on the main thread would block your program's responsiveness.
// std::thread allows us to run such tasks concurrently.

void simulate_task(const string& name, int delay_ms) {
    cout << "[" << name << "] Started on thread ID: " << this_thread::get_id() << "\n";
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
    cout << "[" << name << "] Finished.\n";
}

// =====================================================================
// MAIN DEMO
// =====================================================================
int main() {
    cout << "[Main] Main thread ID: " << this_thread::get_id() << "\n";

    // Launch a thread to run a task
    thread t1(simulate_task, "Task-1", 500);

    // Check if thread is joinable (i.e., valid and not yet joined or detached)
    if (t1.joinable()) {
        cout << "[Main] Joining t1...\n";
        t1.join(); // Wait for thread to finish (blocking)
    }

    // Detach example: background task
    thread t2(simulate_task, "Detached-Task", 300);
    t2.detach(); // Run independently; must finish before main exits

    // Main thread continues
    cout << "[Main] Main thread continues to run.\n";

    this_thread::sleep_for(chrono::milliseconds(400)); // Wait for detached to finish

    // Bad practice: Do not forget to join or detach a thread
    // thread t3(simulate_task, "Forgotten", 100);
    // t3 goes out of scope without join/detach → std::terminate()

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::thread
- join(), detach(), joinable(), get_id() added

C++14 to C++20:
- No changes to std::thread directly
- Modern C++ emphasizes RAII + scoped_thread or thread pools instead

================================================================================
BEST PRACTICES
================================================================================
- Always call join() or detach() on a thread before it goes out of scope
- Use join() when you need result or must wait
- Use detach() for fire-and-forget or background operations
- Prefer thread-safe abstractions like std::async when applicable
- Always check thread.joinable() before calling join()
*/
