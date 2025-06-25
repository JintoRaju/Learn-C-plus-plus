#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

/*
================================================================================
C++ CONCURRENCY: std::mutex, lock_guard, unique_lock, and scoped_lock
================================================================================
This file explains:
- Why we need std::mutex
- What is a data race
- How to use std::mutex with lock_guard
- When to prefer unique_lock over lock_guard
- How std::scoped_lock simplifies locking multiple mutexes (C++17)
- Thread-safe counter examples
- Version notes and best practices
*/

// =====================================================================
// WHY std::mutex?
// =====================================================================
// A data race occurs when multiple threads read/write shared data
// without synchronization. This leads to undefined behavior.

int unsafe_counter = 0; // shared global variable (NOT thread-safe)

void race_increment() {
    for (int i = 0; i < 10000; ++i)
        ++unsafe_counter; // data race: multiple writers
}

void show_data_race() {
    unsafe_counter = 0;
    thread t1(race_increment);
    thread t2(race_increment);
    t1.join();
    t2.join();
    cout << "[Race] Final value (expected 20000): " << unsafe_counter << "\n";
}

// =====================================================================
// USING std::mutex WITH lock_guard (Scoped Lock)
// =====================================================================
int safe_counter = 0;
mutex counter_mutex;

void safe_increment() {
    for (int i = 0; i < 10000; ++i) {
        lock_guard<mutex> lock(counter_mutex); // RAII scoped lock
        ++safe_counter;
    }
}

void show_mutex_solution() {
    safe_counter = 0;
    thread t1(safe_increment);
    thread t2(safe_increment);
    t1.join();
    t2.join();
    cout << "[Safe] Final value: " << safe_counter << "\n";
}

// =====================================================================
// USING std::unique_lock – More flexible than lock_guard
// =====================================================================
// Useful when:
// - You want to defer locking
// - You want to unlock early
// - You need to pass the lock to condition_variable
// - You want try-lock
// lock_guard is simpler and faster for most cases.

int flex_counter = 0;
mutex flex_mutex;

void flexible_locking() {
    for (int i = 0; i < 10000; ++i) {
        unique_lock<mutex> ulock(flex_mutex); // behaves like lock_guard by default
        ++flex_counter;

        if (i % 2000 == 0) {
            ulock.unlock(); // explicit unlock if needed
            this_thread::sleep_for(chrono::milliseconds(1));
            ulock.lock();   // can re-lock later
        }
    }
}

void show_unique_lock() {
    cout << "\n[3] Using std::unique_lock for flexible locking:\n";
    flex_counter = 0;
    thread t1(flexible_locking);
    thread t2(flexible_locking);
    t1.join();
    t2.join();
    cout << "[UniqueLock] Final value: " << flex_counter << "\n";
}

// =====================================================================
// USING std::scoped_lock – For locking multiple mutexes safely (C++17)
// =====================================================================
// Avoids deadlocks when locking more than one mutex.
// std::lock() also works, but scoped_lock is cleaner and exception-safe.

int shared_resource_1 = 0;
int shared_resource_2 = 0;
mutex mutex1, mutex2;

void access_both_resources() {
    for (int i = 0; i < 1000; ++i) {
        scoped_lock lock(mutex1, mutex2); // locks both atomically
        ++shared_resource_1;
        ++shared_resource_2;
    }
}

void show_scoped_lock() {
    cout << "\n[4] Using std::scoped_lock to safely lock multiple mutexes:\n";
    shared_resource_1 = 0;
    shared_resource_2 = 0;
    thread t1(access_both_resources);
    thread t2(access_both_resources);
    t1.join();
    t2.join();
    cout << "[scoped_lock] Resource 1: " << shared_resource_1 << ", Resource 2: " << shared_resource_2 << "\n";
}

int main() {
    cout << "[1] Demonstrating data race without mutex:\n";
    show_data_race();

    cout << "\n[2] Fixing with std::mutex and lock_guard:\n";
    show_mutex_solution();

    show_unique_lock();
    show_scoped_lock();

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::mutex, std::lock_guard, std::unique_lock

C++14:
- No change to mutex APIs

C++17:
- std::scoped_lock introduced for multiple mutex locking
- Replaces std::lock() + lock_guard combo

================================================================================
BEST PRACTICES
================================================================================
- Use lock_guard for simple RAII locking
- Use unique_lock when you need to:
    • defer lock
    • unlock and re-lock
    • pass lock to condition_variable
- Use scoped_lock when locking multiple mutexes (safe and deadlock-free)
- Keep critical sections short
- Use atomic<T> when simple lock-free counters are sufficient
*/
