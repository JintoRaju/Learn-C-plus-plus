#include <iostream>
#include <queue>
#include <vector>
#include <functional> // for std::greater
using namespace std;

//
// WHY std::priority_queue?
//
// Problem:
// - std::queue processes items in FIFO order (no priority)
// - Sometimes, we need to always access the **largest** (or smallest) element
//
// Solution:
// - std::priority_queue is a container adapter that uses **heap** structure
//     - By default: MAX-HEAP (largest on top)
//     - Uses `vector<T>` + `make_heap()` internally
//

void max_heap_demo() {
    cout << "=== std::priority_queue (Max-Heap by default) ===\n";

    priority_queue<int> pq;

    pq.push(10);
    pq.push(30);
    pq.push(20); // Heap: top = 30

    cout << "Top: " << pq.top() << endl;

    pq.pop();  // removes 30
    cout << "After pop, Top: " << pq.top() << endl;

    cout << "Size: " << pq.size() << ", Empty? " << boolalpha << pq.empty() << endl;
}

void min_heap_demo() {
    cout << "\n=== Min-Heap using greater<T> ===\n";

    // Min-heap: pass greater<T> as 3rd argument
    priority_queue<int, vector<int>, greater<int>> minpq;

    minpq.push(10);
    minpq.push(30);
    minpq.push(20); // Top = 10

    while (!minpq.empty()) {
        cout << minpq.top() << " ";
        minpq.pop();
    }
    cout << endl;
}

struct Task {
    int priority;
    string name;

    // Default: higher priority → comes first
    bool operator<(const Task& other) const {
        return priority < other.priority; // reversed: high first
    }
};

void object_priority_queue() {
    cout << "\n=== Custom Struct in Priority Queue ===\n";

    priority_queue<Task> taskQueue;

    taskQueue.push({3, "Low"});
    taskQueue.push({10, "High"});
    taskQueue.push({5, "Medium"});

    while (!taskQueue.empty()) {
        auto t = taskQueue.top();
        cout << "Task: " << t.name << " (priority " << t.priority << ")\n";
        taskQueue.pop();
    }
}

int main() {
    max_heap_demo();
    min_heap_demo();
    object_priority_queue();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::priority_queue
============================================================================

C++98:
- Introduced as part of STL
- Works as a container adapter using `vector<T>` by default
- Max-heap (highest element first)
- Exposes: push(), pop(), top(), empty(), size()

C++11:
- Move semantics supported
- Emplace added: pq.emplace(...)

C++14:
- Minor allocator enhancements

C++17:
- Enhanced constexpr usability

C++20:
- Usable in constexpr where applicable
- Can be wrapped with ranges for controlled iteration

============================================================================
INTERNALS – How std::priority_queue works
============================================================================

- Built on top of `std::vector<T>` and heap operations (`make_heap`, `push_heap`, `pop_heap`)
- By default:
    priority_queue<T>  == max-heap
    priority_queue<T, vector<T>, greater<T>> == min-heap

Signature:
    template<
        class T,
        class Container = std::vector<T>,
        class Compare = std::less<typename Container::value_type>
    > class priority_queue;

============================================================================
COMPARISON – priority_queue vs queue vs set
============================================================================

| Feature               | priority_queue    | queue<T>         | set<T>            |
|-----------------------|-------------------|------------------|-------------------|
| Ordered?              |  by priority     |  FIFO          |  (sorted)       |
| Access top/front?     |  top()           |  front()       |  *begin()       |
| Duplicate values      |  Allowed         |  Allowed       |  No             |
| Random access         |  Not allowed     |  Not allowed   |  Limited        |
| Iteration supported?  |  No              |  No            |  Yes            |

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Max-heap by default (`std::less<T>` used internally)
- Min-heap needs: `priority_queue<T, vector<T>, greater<T>>`
- Copying/moving works well with C++11+
- Iteration NOT supported — must pop to access
- `.top()` reads highest priority element (does not remove it)
- `.pop()` removes top but does NOT return it
- Use `emplace()` (C++11) for in-place construction

============================================================================
CHEAT SHEET – std::priority_queue
============================================================================

Declaration:
    priority_queue<int> pq;  // max-heap
    priority_queue<int, vector<int>, greater<int>> minpq;

Operations:
    pq.push(x);
    pq.emplace(args...);   // C++11
    pq.top();
    pq.pop();
    pq.size(); pq.empty();

Custom types:
    struct Task { ... };
    bool operator<(const Task&);  // reverse logic for higher = more priority

*/

