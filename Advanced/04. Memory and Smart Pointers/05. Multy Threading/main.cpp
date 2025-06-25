#include <iostream>
#include <thread>               // std::thread
#include <mutex>                // std::mutex, std::lock_guard
#include <future>               // std::async, std::future
#include <chrono>               // std::chrono
#include <vector>               // For multiple threads
#include <condition_variable>   // Condition variable

using namespace std;

//
// C++ CONCURRENCY PRIMER (C++11–C++20)
// -------------------------------------
// GOAL: Understand how C++ supports multi-threading safely and efficiently
//
// Topics:
// 1. Why Concurrency?
// 2. std::thread basics
// 3. Joining vs Detaching
// 4. Race Conditions and Data Races
// 5. Mutex, lock_guard, unique_lock
// 6. std::async and std::future
// 7. condition_variable
// 8. Shared data with producer/consumer
// 9. Version evolution notes
//

// ======================================================================
// 1. WHY CONCURRENCY?
// ======================================================================
//
// Use Case: Long CPU or IO-bound operations that block main thread.
// Solution: Let them run in parallel threads to increase responsiveness.
//

void say_hello() {
    cout << "Hello from thread!\n";
}

// ======================================================================
// 2. std::thread BASICS (C++11)
// ======================================================================

void thread_basics() {
    cout << "\n[2] Thread basics:\n";
    thread t1(say_hello);  // create and run thread
    t1.join();             // main thread waits for t1 to finish
}

// ======================================================================
// 3. JOIN VS DETACH (C++11)
// ======================================================================

void detached_function() {
    cout << "Detached thread running...\n";
}

void join_vs_detach() {
    cout << "\n[3] Join vs Detach:\n";
    thread t2(detached_function);
    // t2.join();    // Waits (blocking)
    t2.detach();     // Frees thread to run independently
    // Note: If main exits early, detached thread may be killed
}

// ======================================================================
// 4. RACE CONDITIONS – Data races (BAD CODE)
//
// Two threads write to same variable without sync → undefined behavior
// ======================================================================

int counter = 0;

void unsafe_increment() {
    for (int i = 0; i < 10000; ++i) {
        ++counter; // Not thread-safe!
    }
}

void show_race_condition() {
    cout << "\n[4] Race Condition (unsafe counter):\n";
    counter = 0;

    thread t1(unsafe_increment);
    thread t2(unsafe_increment);

    t1.join();
    t2.join();

    cout << "Expected: 20000, Got: " << counter << "\n"; // Likely wrong!
}

// ======================================================================
// 5. MUTEX + LOCK_GUARD – Fixing data race
// ======================================================================

int safe_counter = 0;
mutex mtx;

void safe_increment() {
    for (int i = 0; i < 10000; ++i) {
        lock_guard<mutex> lock(mtx); // RAII lock
        ++safe_counter;
    }
}

void mutex_demo() {
    cout << "\n[5] Mutex with lock_guard (safe counter):\n";
    safe_counter = 0;

    thread t1(safe_increment);
    thread t2(safe_increment);

    t1.join();
    t2.join();

    cout << "Safe counter: " << safe_counter << "\n";
}

// ======================================================================
// 6. std::async and std::future (C++11)
// ======================================================================

int compute_square(int x) {
    this_thread::sleep_for(chrono::milliseconds(100));
    return x * x;
}

void async_demo() {
    cout << "\n[6] std::async and std::future:\n";

    future<int> fut = async(launch::async, compute_square, 10);
    cout << "Doing other work while async computes...\n";

    int result = fut.get(); // waits if not ready
    cout << "Result from async: " << result << "\n";
}

// ======================================================================
// 7. condition_variable (C++11)
// ======================================================================

mutex cond_mtx;
condition_variable cond_var;
bool ready = false;

void consumer() {
    unique_lock<mutex> lock(cond_mtx);
    cond_var.wait(lock, [] { return ready; }); // block until ready is true
    cout << "Consumer proceeding\n";
}

void producer() {
    this_thread::sleep_for(chrono::milliseconds(200));
    {
        lock_guard<mutex> lock(cond_mtx);
        ready = true;
        cout << "Producer done\n";
    }
    cond_var.notify_one(); // wake consumer
}

void condition_variable_demo() {
    cout << "\n[7] condition_variable demo:\n";

    ready = false;
    thread t1(consumer);
    thread t2(producer);

    t1.join();
    t2.join();
}

// ======================================================================
// 8. MULTIPLE THREADS – Parallel loop (thread pool logic)
// ======================================================================

void do_work(int id) {
    cout << "Thread " << id << " is working\n";
}

void launch_threads() {
    cout << "\n[8] Launch multiple threads:\n";
    vector<thread> workers;

    for (int i = 0; i < 4; ++i)
        workers.emplace_back(do_work, i);

    for (auto& t : workers)
        t.join();
}

// ======================================================================
int main() {
    thread_basics();
    join_vs_detach();
    show_race_condition();
    mutex_demo();
    async_demo();
    condition_variable_demo();
    launch_threads();
    return 0;
}

/*
============================================================================
VERSION NOTES
============================================================================

✅ C++11:
- std::thread, std::mutex, std::lock_guard
- std::async, std::future, std::promise
- std::condition_variable
- All concurrency in C++ starts here

✅ C++14:
- Improved exception safety and std::shared_timed_mutex
- Some enhancements in std::future

✅ C++17:
- std::shared_mutex, std::scoped_lock for multiple mutex locking

✅ C++20:
- atomic<T>::wait()/notify_one() (wait-free condition vars)
- Improved concurrency guarantees
- Coroutine support (co_await) also related to async models

============================================================================
COMMON PITFALLS AND TIPS
============================================================================

- NEVER read/write shared data without sync → data race!
- Use lock_guard for simple scope-based locking
- Use async for simple parallel tasks without thread management
- Always join or detach every thread you start
- Use condition_variable when threads need to "wait" for signals
- Prefer atomic<T> for simple counter variables over mutex

============================================================================
CHEAT SHEET – C++ CONCURRENCY TOOLS
============================================================================

| Tool                  | Purpose                        | Header             |
|-----------------------|--------------------------------|--------------------|
| std::thread           | Launch parallel threads        | <thread>           |
| std::mutex            | Lock shared data               | <mutex>            |
| std::lock_guard       | Scoped RAII lock               | <mutex>            |
| std::unique_lock      | Flexible lock/unlock           | <mutex>            |
| std::condition_variable | Thread waiting/signaling     | <condition_variable>|
| std::async/future     | Async task with result future  | <future>           |

*/
