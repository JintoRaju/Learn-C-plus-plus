#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

/*
================================================================================
C++ CONCURRENCY: CONDITION VARIABLES (C++11 and Beyond)
================================================================================
This file demonstrates:
- Why we need condition variables (problem motivation)
- Using std::condition_variable to wait/notify threads
- Producer-consumer problem
- Avoiding spurious wakeups
- Version notes and best practices
================================================================================
*/

// =====================================================================
// WHY CONDITION VARIABLES?
// =====================================================================
// Problem: Thread A must wait until thread B updates some shared state.
// Busy-waiting wastes CPU. Condition variable allows efficient sleeping + wakeup.

queue<int> data_queue;
mutex queue_mutex;
condition_variable data_condition;
bool done = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            lock_guard<mutex> lock(queue_mutex);
            data_queue.push(i);
            cout << "[Producer] Produced: " << i << "\n";
        }
        data_condition.notify_one(); // notify one waiting thread
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    {
        lock_guard<mutex> lock(queue_mutex);
        done = true;
    }
    data_condition.notify_all(); // notify consumer that we're done
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(queue_mutex);

        // Wait until data is available or done = true
        data_condition.wait(lock, [] {
            return !data_queue.empty() || done;
        });

        while (!data_queue.empty()) {
            int item = data_queue.front();
            data_queue.pop();
            cout << "[Consumer] Consumed: " << item << "\n";
        }

        if (done) break;
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced std::condition_variable, std::condition_variable_any
- Functions: wait(), notify_one(), notify_all()

C++20:
- Added notify_one(), notify_all() to std::atomic (not std::condition_variable)

================================================================================
BEST PRACTICES
================================================================================
- Always use wait(lock, predicate) form to avoid spurious wakeups
- Lock must be a std::unique_lock, not lock_guard
- Use notify_one() for single consumer, notify_all() if multiple
- Condition variable must be notified *after* releasing data into shared state
- Avoid holding the lock while doing heavy processing — keep critical sections short
*/
