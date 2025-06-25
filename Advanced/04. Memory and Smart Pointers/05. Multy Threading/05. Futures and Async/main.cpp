#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

/*
================================================================================
C++ CONCURRENCY: FUTURES AND ASYNC (C++11 and Beyond)
================================================================================
This file demonstrates:
- Using std::async to launch asynchronous tasks
- Retrieving results with std::future
- Using std::promise to manually fulfill futures
- Shared futures with std::shared_future
- Version notes and best practices
================================================================================
*/

// =====================================================================
// std::async + std::future: Launch task and retrieve result later
// =====================================================================
int compute_square(int x) {
    this_thread::sleep_for(chrono::milliseconds(200)); // simulate work
    return x * x;
}

void demonstrate_async_future() {
    future<int> result = async(launch::async, compute_square, 5);
    cout << "[Async] Doing other work while task runs...\n";
    cout << "[Async] Result: " << result.get() << "\n"; // blocks if not ready
}

// =====================================================================
// std::promise: Manual producer of value
// =====================================================================
void fulfill_promise(promise<string> prom) {
    this_thread::sleep_for(chrono::milliseconds(100));
    prom.set_value("Hello from worker!");
}

void demonstrate_promise_future() {
    promise<string> prom;
    future<string> fut = prom.get_future();
    thread t(fulfill_promise, move(prom));
    cout << "[Promise] Message: " << fut.get() << "\n";
    t.join();
}

// =====================================================================
// std::shared_future: Allows multiple readers of the same result
// =====================================================================
int delayed_answer() {
    this_thread::sleep_for(chrono::milliseconds(150));
    return 42;
}

void demonstrate_shared_future() {
    shared_future<int> shared = async(launch::async, delayed_answer);
    cout << "[SharedFuture] T1 sees: " << shared.get() << "\n";
    cout << "[SharedFuture] T2 sees: " << shared.get() << "\n";
}

int main() {
    demonstrate_async_future();
    demonstrate_promise_future();
    demonstrate_shared_future();
    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::future, std::promise, std::async, std::shared_future
- std::packaged_task also introduced for custom tasks

C++14–17:
- No direct changes in future/promise system

C++20:
- std::jthread added (auto-joining thread with stop token)

================================================================================
BEST PRACTICES
================================================================================
- Prefer std::async over manual thread + promise for simple tasks
- Avoid using std::launch::deferred unless lazy execution is desired
- Always call get() to ensure future is fulfilled (or use wait())
- std::promise useful for producer-consumer separation
- Use std::shared_future only when result is needed by multiple consumers
*/
