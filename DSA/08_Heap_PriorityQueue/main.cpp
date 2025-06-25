#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
================================================================================
DSA_08_HEAP_PRIORITYQUEUE.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Heaps are binary trees stored in arrays with the heap property:
   O Max-Heap: parent ≥ children (used for priority scheduling)
   O Min-Heap: parent ≤ children (used in Dijkstra, Huffman Coding)

O C++ STL provides:
   O priority_queue (by default a Max-Heap)
   O Custom comparators to build Min-Heap

================================================================================
TOPICS COVERED
================================================================================
1. Using std::priority_queue as Max-Heap
2. Min-Heap using custom comparator
3. Build heap from array
4. Heap operations: push(), pop(), top()
================================================================================
*/

//------------------------------------------------------------------------------
// 1. MAX HEAP (DEFAULT PRIORITY_QUEUE)
//------------------------------------------------------------------------------
void maxHeapDemo() {
    priority_queue<int> pq;

    pq.push(50);
    pq.push(30);
    pq.push(20);
    pq.push(60);

    cout << "[Max-Heap] Elements in priority order: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";
}

//------------------------------------------------------------------------------
// 2. MIN HEAP (CUSTOM COMPARATOR)
//------------------------------------------------------------------------------
void minHeapDemo() {
    priority_queue<int, vector<int>, greater<int>> pq;

    pq.push(50);
    pq.push(30);
    pq.push(20);
    pq.push(60);

    cout << "[Min-Heap] Elements in ascending order: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";
}

//------------------------------------------------------------------------------
// 3. CUSTOM COMPARATOR FOR STRUCT (TASK SCHEDULER EXAMPLE)
//------------------------------------------------------------------------------
struct Task {
    int priority;
    string name;

    Task(int p, string n) : priority(p), name(n) {}
};

struct CompareTasks {
    bool operator()(const Task& a, const Task& b) {
        return a.priority > b.priority; // min-heap
    }
};

void taskScheduler() {
    priority_queue<Task, vector<Task>, CompareTasks> pq;

    pq.emplace(3, "Email");
    pq.emplace(1, "Meeting");
    pq.emplace(2, "Code Review");

    cout << "[Task Scheduler Priority Order]:\n";
    while (!pq.empty()) {
        cout << "  • " << pq.top().name << " (Priority " << pq.top().priority << ")\n";
        pq.pop();
    }
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Added `emplace()` for efficient in-place construction
- Lambdas as custom comparators (not used here but supported)

C++17+:
- Structured bindings with priority_queue.top()
- std::make_heap, std::pop_heap, std::push_heap also available

================================================================================
TIME COMPLEXITY
================================================================================
Heap Operations:
- push()   ➜ O(log n)
- pop()    ➜ O(log n)
- top()    ➜ O(1)

================================================================================
BEST PRACTICES
================================================================================
O Use `greater<T>` for Min-Heap
O Use `emplace()` over `push()` for performance
O For custom types, define comparator as a struct or lambda
O STL `priority_queue` is backed by a vector using a binary heap
*/

int main() {
    maxHeapDemo();
    minHeapDemo();
    taskScheduler();
    return 0;
}
