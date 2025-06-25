#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
using namespace std;

/*
================================================================================
C++ CONCURRENCY: MEMORY MODEL & MEMORY ORDERING (C++11 and Beyond)
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
In concurrent programming, the **C++ memory model** defines how operations
on memory are seen by different threads. It answers:

- Can one thread's writes be reordered and seen differently by another?
- How do we safely share data between threads without locks?
- Why do race conditions happen even when we use atomics?

This topic is crucial to:
✔ Prevent subtle data races when using atomics
✔ Understand instruction reordering, visibility issues
✔ Write efficient low-level lock-free code safely

================================================================================
WHAT'S COVERED:
1. Sequential Consistency (default)
2. Relaxed Order (high-performance)
3. Acquire-Release Semantics
4. Version notes and best practices
================================================================================
*/

// =============================================================================
// 1. SEQUENTIAL CONSISTENCY (DEFAULT - memory_order_seq_cst)
// =============================================================================
// memory_order_seq_cst (default) provides a total global order.
// Every thread sees all operations in the same order.

atomic<int> x{0}, y{0};

void write_x_then_y() {
    x.store(1);          // write x first
    y.store(1);          // then y
}

void read_y_then_x() {
    while (y.load() != 1);          // wait until y is written
    if (x.load() == 0)              // is it possible to see y=1 and x=0?
        cout << "[SC] Reordering detected!\n";
}

// Explanation: With memory_order_seq_cst, reordering should not happen.
// But if relaxed memory orders are used, this result *is* possible.

// =============================================================================
// 2. RELAXED MEMORY ORDERING (memory_order_relaxed)
// =============================================================================
// Fastest but provides no synchronization guarantees.
// Useful when we don't care about ordering — just atomicity.

atomic<int> rx{0}, ry{0};

void relaxed_writer() {
    rx.store(1, memory_order_relaxed);
    ry.store(1, memory_order_relaxed);
}

void relaxed_reader() {
    while (ry.load(memory_order_relaxed) != 1); // wait until ry = 1
    if (rx.load(memory_order_relaxed) == 0)
        cout << "[Relaxed] Reordering observed!\n";
}

// Explanation: This is legal! Reordering is allowed under relaxed ordering.
// No visibility guarantees between threads unless explicitly stated.

// =============================================================================
// 3. ACQUIRE-RELEASE SEMANTICS
// =============================================================================
// Provides partial ordering — enough for synchronization.
// release => ensures all writes before it are visible to readers using acquire.

atomic<bool> flag{false};
int shared_data = 0;

void release_writer() {
    shared_data = 42;                             // ordinary write
    flag.store(true, memory_order_release);       // make visible to others
}

void acquire_reader() {
    while (!flag.load(memory_order_acquire));     // wait until visible
    cout << "[Acquire/Release] Shared data = " << shared_data << "\n";
}

// Explanation: acquire ensures that `shared_data = 42` is visible once
// flag == true. This is a classic lock-free sync pattern.

// =============================================================================
// MAIN DEMO
// =============================================================================

int main() {
    cout << "\n=== Sequential Consistency ===\n";
    thread t1(write_x_then_y);
    thread t2(read_y_then_x);
    t1.join();
    t2.join();

    cout << "\n=== Relaxed Ordering ===\n";
    thread t3(relaxed_writer);
    thread t4(relaxed_reader);
    t3.join();
    t4.join();

    cout << "\n=== Acquire-Release ===\n";
    thread t5(release_writer);
    thread t6(acquire_reader);
    t5.join();
    t6.join();

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::atomic<T>
- memory_order enum:
  • memory_order_relaxed
  • memory_order_consume (deprecated)
  • memory_order_acquire
  • memory_order_release
  • memory_order_acq_rel
  • memory_order_seq_cst (default)

C++20:
- Introduced atomic::wait/notify for blocking without mutex

================================================================================
BEST PRACTICES
================================================================================
- Prefer memory_order_seq_cst for simplicity unless proven bottleneck.
- Use memory_order_release on write + memory_order_acquire on read for sync.
- Relaxed is only safe when you don’t need ordering — use carefully.
- Mixing memory orders = hard to reason about => avoid unless expert.
- Use high-level sync (mutex/atomic + release-acquire) over raw relaxed logic.
*/
