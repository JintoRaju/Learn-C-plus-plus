#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

/*
================================================================================
C++ CONCURRENCY: THREAD SYNCHRONIZATION PATTERNS (C++11 and Beyond)
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
In real-world concurrent programs, multiple threads often need to coordinate:
  - One thread waits for another to finish a task.
  - Threads share bounded resources (like buffer slots).
  - All threads must meet at a common checkpoint (barrier) before continuing.

Thread synchronization patterns are essential to:
  - Avoid data races, deadlocks, and race conditions
  - Implement correct sequencing between threads
  - Make concurrent programs predictable and maintainable
================================================================================

WHAT'S COVERED:
1. Guarded Sections (mutex + condition_variable)
2. Bounded Buffer (Producer-Consumer with capacity)
3. Barrier Pattern (all threads wait for each other)
4. Version notes and best practices
================================================================================
*/

// =============================================================================
// 1. GUARDED SECTION
// =============================================================================
// One thread waits until a flag or shared state becomes valid (condition)

mutex guarded_mutex;
condition_variable guarded_cv;
bool resource_ready = false;

void guarded_producer() {
    this_thread::sleep_for(chrono::milliseconds(200)); // simulate work
    {
        lock_guard<mutex> lock(guarded_mutex);
        resource_ready = true;
        cout << "[Guarded] Resource produced.\n";
    }
    guarded_cv.notify_one();
}

void guarded_consumer() {
    unique_lock<mutex> lock(guarded_mutex);
    guarded_cv.wait(lock, [] { return resource_ready; });
    cout << "[Guarded] Resource consumed.\n";
}

// =============================================================================
// 2. BOUNDED BUFFER (PRODUCER-CONSUMER with limit)
// =============================================================================
// Thread-safe buffer access — block when full or empty.

const int MAX_BUFFER = 3;
int buffer[MAX_BUFFER];
int count = 0;
mutex buffer_mutex;
condition_variable buffer_not_full, buffer_not_empty;

void bounded_producer() {
    for (int i = 0; i < 5; ++i) {
        unique_lock<mutex> lock(buffer_mutex);
        buffer_not_full.wait(lock, [] { return count < MAX_BUFFER; });
        buffer[count++] = i;
        cout << "[Buffer] Produced: " << i << "\n";
        buffer_not_empty.notify_one();
    }
}

void bounded_consumer() {
    for (int i = 0; i < 5; ++i) {
        unique_lock<mutex> lock(buffer_mutex);
        buffer_not_empty.wait(lock, [] { return count > 0; });
        int item = buffer[--count];
        cout << "[Buffer] Consumed: " << item << "\n";
        buffer_not_full.notify_one();
    }
}

// =============================================================================
// 3. BARRIER PATTERN (simplified without std::barrier)
// =============================================================================
// Wait for all N threads to reach the barrier before proceeding.

mutex barrier_mutex;
condition_variable barrier_cv;
int barrier_count = 0;
const int NUM_THREADS = 3;

void barrier_worker(int id) {
    cout << "[Barrier] Thread " << id << " reached barrier.\n";
    {
        unique_lock<mutex> lock(barrier_mutex);
        barrier_count++;
        if (barrier_count == NUM_THREADS) {
            barrier_cv.notify_all();
        } else {
            barrier_cv.wait(lock, [] { return barrier_count == NUM_THREADS; });
        }
    }
    cout << "[Barrier] Thread " << id << " passed barrier.\n";
}

int main() {
    cout << "\n=== Guarded Section ===\n";
    thread t1(guarded_producer), t2(guarded_consumer);
    t1.join(); t2.join();

    cout << "\n=== Bounded Buffer ===\n";
    thread p(bounded_producer), c(bounded_consumer);
    p.join(); c.join();

    cout << "\n=== Barrier Pattern ===\n";
    thread b1(barrier_worker, 1);
    thread b2(barrier_worker, 2);
    thread b3(barrier_worker, 3);
    b1.join(); b2.join(); b3.join();

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::mutex, std::condition_variable

C++20:
- Introduced std::barrier and std::latch for true barrier use-cases

================================================================================
BEST PRACTICES
================================================================================
- Always use predicate inside condition_variable.wait(lock, pred)
- Never hold a lock longer than necessary — minimize critical section
- Use std::barrier (C++20) when all threads must wait at a common point
- Always call join() on threads unless using std::jthread (C++20)
*/
