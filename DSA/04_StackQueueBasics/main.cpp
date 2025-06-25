#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/*
================================================================================
DSA_04_STACKQUEUEBASICS.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O Stacks and queues are linear data structures used in many real-world problems:
   O Stack: backtracking, undo, expression evaluation, recursion internals
   O Queue: job scheduling, buffers, BFS traversal

O STL gives us ready-to-use stack and queue containers.

================================================================================
TOPICS COVERED
================================================================================
1. Stack (LIFO)
   - Push, Pop, Top
2. Queue (FIFO)
   - Push, Pop, Front
3. Use-cases and time complexities
================================================================================
*/

//------------------------------------------------------------------------------
// 1. STACK — LAST IN, FIRST OUT (LIFO)
//------------------------------------------------------------------------------
void stackDemo() {
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);  // Top is 30

    cout << "[Stack] Popping elements (LIFO): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "\n";
}

//------------------------------------------------------------------------------
// 2. QUEUE — FIRST IN, FIRST OUT (FIFO)
//------------------------------------------------------------------------------
void queueDemo() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);  // Front is 10

    cout << "[Queue] Removing elements (FIFO): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n";
}

/*
================================================================================
VERSION NOTES
================================================================================
C++98:
- `std::stack`, `std::queue` introduced

C++11+:
- Use `emplace()` for faster in-place construction
- Use `auto` and range-based `for` with custom stack/queue wrappers

================================================================================
TIME COMPLEXITY
================================================================================
Stack:
  push()       ➜ O(1)
  pop()        ➜ O(1)
  top()        ➜ O(1)

Queue:
  push()       ➜ O(1)
  pop()        ➜ O(1)
  front()      ➜ O(1)

================================================================================
BEST PRACTICES
================================================================================
O Use stack when you need to reverse or backtrack operations
O Use queue for order-sensitive operations (like BFS)
O Don't use `.top()` or `.front()` without checking `.empty()`
O For performance, use `emplace()` where object construction is needed
*/

int main() {
    stackDemo();
    queueDemo();
    return 0;
}
