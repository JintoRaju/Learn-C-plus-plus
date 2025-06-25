#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>
#include <chrono>
#include <execution> // For C++17 parallel algorithms
using namespace std;

/*
================================================================================
C++ CONCURRENCY: TASK-BASED CONCURRENCY (C++11–20)
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
Manually managing threads is error-prone:
  - Threads need to be joined manually
  - No way to return values easily
  - Exceptions in threads crash the program

Task-based concurrency solves this with:
✔ Automatic thread management via std::async / std::jthread
✔ Result retrieval via std::future and std::promise
✔ Built-in exception propagation
✔ Clean cancellation and coordination mechanisms

================================================================================
WHAT'S COVERED:
1. std::async + std::future
2. std::packaged_task
3. std::promise + std::future
4. shared_future
5. future_status (wait_for/wait_until)
6. Exception propagation in futures
7. std::jthread (C++20)
8. Deferred execution in async
9. Parallel STL (C++17)
================================================================================
*/

// =============================================================================
// 1. std::async + std::future
// =============================================================================
int compute(int a, int b) {
    this_thread::sleep_for(chrono::milliseconds(100));
    return a + b;
}

void demo_async_future() {
    future<int> result = async(launch::async, compute, 5, 10);
    cout << "[async] Waiting...\n";
    cout << "[async] Result = " << result.get() << "\n";  // blocks if not ready
}

// =============================================================================
// 2. std::packaged_task — manually wrap callable
// =============================================================================
int square(int x) { return x * x; }

void demo_packaged_task() {
    packaged_task<int(int)> task(square);
    future<int> result = task.get_future();
    thread t(move(task), 6);  // run in new thread
    t.join();
    cout << "[packaged_task] Result = " << result.get() << "\n";
}

// =============================================================================
// 3. std::promise + std::future
// =============================================================================
void set_promise_value(promise<string> p) {
    this_thread::sleep_for(chrono::milliseconds(50));
    p.set_value("Hello from promise!");
}

void demo_promise() {
    promise<string> p;
    future<string> f = p.get_future();
    thread t(set_promise_value, move(p));
    cout << "[promise] Value = " << f.get() << "\n";
    t.join();
}

// =============================================================================
// 4. std::shared_future — multiple reads from same future
// =============================================================================
int get_id() { return 1234; }

void demo_shared_future() {
    future<int> fut = async(get_id);
    shared_future<int> sf = fut.share();
    thread t1([sf] { cout << "[shared_future] T1 got: " << sf.get() << "\n"; });
    thread t2([sf] { cout << "[shared_future] T2 got: " << sf.get() << "\n"; });
    t1.join(); t2.join();
}

// =============================================================================
// 5. future_status with wait_for / wait_until
// =============================================================================
int long_task() {
    this_thread::sleep_for(chrono::milliseconds(150));
    return 42;
}

void demo_future_status() {
    future<int> f = async(long_task);
    if (f.wait_for(chrono::milliseconds(50)) == future_status::ready)
        cout << "[status] Got result: " << f.get() << "\n";
    else
        cout << "[status] Still waiting...\n";
    f.wait();  // block until ready
    cout << "[status] Finally: " << f.get() << "\n";
}

// =============================================================================
// 6. Exception propagation in future
// =============================================================================
int faulty() {
    throw runtime_error("Something went wrong!");
}

void demo_exception_in_future() {
    future<int> f = async(faulty);
    try {
        int val = f.get();  // will throw stored exception
    } catch (const exception& e) {
        cout << "[exception] Caught: " << e.what() << "\n";
    }
}

// =============================================================================
// 7. C++20: std::jthread — joins automatically
// =============================================================================
#if __cpp_lib_jthread >= 201911L
#include <stop_token>

void do_work(stop_token st) {
    while (!st.stop_requested()) {
        cout << "[jthread] Working...\n";
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << "[jthread] Stopped!\n";
}

void demo_jthread() {
    jthread jt(do_work);
    this_thread::sleep_for(chrono::milliseconds(200));
    // auto-stop occurs when jthread is destroyed
}
#endif

// =============================================================================
// 8. Deferred execution in std::async
// =============================================================================
void demo_deferred_async() {
    future<int> f = async(launch::deferred, [] {
        cout << "[deferred] Running on get()\n";
        return 99;
    });
    // nothing runs until get()
    cout << "[deferred] Result = " << f.get() << "\n";
}

// =============================================================================
// 9. Parallel STL (C++17)
void demo_parallel_stl() {
#if __cpp_lib_execution >= 201603L
    vector<int> v(1e6, 1);
    int sum = reduce(execution::par, v.begin(), v.end());
    cout << "[Parallel STL] Sum = " << sum << "\n";
#else
    cout << "[Parallel STL] Not supported on this compiler.\n";
#endif
}

// =============================================================================
// MAIN
// =============================================================================
int main() {
    cout << "\n=== std::async ===\n";                demo_async_future();
    cout << "\n=== packaged_task ===\n";             demo_packaged_task();
    cout << "\n=== std::promise ===\n";              demo_promise();
    cout << "\n=== shared_future ===\n";             demo_shared_future();
    cout << "\n=== future_status ===\n";             demo_future_status();
    cout << "\n=== exception in future ===\n";       demo_exception_in_future();
#if __cpp_lib_jthread >= 201911L
    cout << "\n=== jthread (C++20) ===\n";           demo_jthread();
#endif
    cout << "\n=== async (deferred) ===\n";          demo_deferred_async();
    cout << "\n=== parallel STL ===\n";              demo_parallel_stl();
    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced async, future, promise, packaged_task

C++14:
- Minor improvements, nothing major for tasks

C++17:
- Introduced std::execution + parallel STL algorithms
- std::shared_future improved

C++20:
- Introduced std::jthread (auto-joining, supports stop_token)

================================================================================
BEST PRACTICES
================================================================================
- Prefer std::async for simple fire-and-wait tasks
- Use std::promise when the producer runs manually in a thread
- Use std::shared_future when multiple readers need the same result
- Prefer jthread over thread if using C++20 (auto join + cancel support)
- Use parallel STL only if operations are pure (no side effects)
- Be cautious: future.get() blocks and can hide performance issues
- Catch exceptions thrown from futures properly
*/
