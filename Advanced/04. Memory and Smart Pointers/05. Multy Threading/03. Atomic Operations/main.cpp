#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

/*
================================================================================
C++ CONCURRENCY: ATOMIC OPERATIONS (C++11 and Beyond)
================================================================================
This file demonstrates:
- What are atomic operations and why they are needed
- Using std::atomic<T> for lock-free synchronization
- How atomic prevents data races
- Introduction to memory_order (default is sequential consistency)
- Difference between atomic and mutex
- Version notes and best practices
================================================================================
*/

// =====================================================================
// WHY ATOMIC? (Avoiding mutex overhead for simple counters)
// =====================================================================
// For small variables like integers, lock-free atomic operations are faster
// and less resource-heavy than mutexes.

int non_atomic_counter = 0;
void race_with_plain_int() {
    for (int i = 0; i < 10000; ++i)
        ++non_atomic_counter; // NOT thread-safe
}

void demonstrate_data_race_with_int() {
    non_atomic_counter = 0;
    thread t1(race_with_plain_int);
    thread t2(race_with_plain_int);
    t1.join();
    t2.join();
    cout << "[Non-Atomic] Final value (expected 20000): " << non_atomic_counter << "\n";
}

// =====================================================================
// USING std::atomic<int> — thread-safe increment without locks
// =====================================================================
atomic<int> atomic_counter{0};

void safe_atomic_increment() {
    for (int i = 0; i < 10000; ++i)
        ++atomic_counter; // thread-safe
}

void demonstrate_atomic_counter() {
    atomic_counter = 0;
    thread t1(safe_atomic_increment);
    thread t2(safe_atomic_increment);
    t1.join();
    t2.join();
    cout << "[Atomic] Final value: " << atomic_counter << "\n";
}

// =====================================================================
// ATOMIC FLAG (lowest-level lock-free flag)
// =====================================================================
atomic_flag lock_flag = ATOMIC_FLAG_INIT;
int protected_shared = 0;

void spinlock_example() {
    for (int i = 0; i < 1000; ++i) {
        // spin until we acquire lock (not ideal — high CPU)
        while (lock_flag.test_and_set(memory_order_acquire));
        ++protected_shared;
        lock_flag.clear(memory_order_release);
    }
}

void demonstrate_atomic_flag() {
    protected_shared = 0;
    lock_flag.clear(); // reset flag
    thread t1(spinlock_example);
    thread t2(spinlock_example);
    t1.join();
    t2.join();
    cout << "[AtomicFlag] Shared value: " << protected_shared << "\n";
}

int main() {
    demonstrate_data_race_with_int();
    demonstrate_atomic_counter();
    demonstrate_atomic_flag();
    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::atomic<T>, atomic_flag
- Functions: fetch_add, load, store, exchange, compare_exchange_weak/strong

C++14/C++17:
- No major changes in std::atomic

C++20:
- Added wait(), notify_one(), notify_all() to atomic

================================================================================
BEST PRACTICES
================================================================================
- Use std::atomic<T> for small, simple variables like int, bool, pointer
- Use memory_order_seq_cst unless you deeply understand memory ordering
- Prefer atomic for performance-sensitive counters instead of mutex
- Avoid atomic_flag spinlocks in real code — use mutex or proper primitives
- For complex data structures, mutex is safer than atomic
*/
