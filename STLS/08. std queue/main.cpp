#include <iostream>
#include <queue>
#include <deque>
#include <list>     // optional for custom underlying container
using namespace std;

//
// WHY std::queue?
//
// Problem:
// - Need a First-In-First-Out (FIFO) data structure
// - Manually implementing it with vector/deque is error-prone and verbose
//
// Solution:
// - std::queue is a container adapter:
//     - Provides FIFO semantics
//     - Exposes: push(), pop(), front(), back(), size(), empty()
//     - Internally uses deque<T> by default
//

void basic_queue_usage() {
    cout << "=== std::queue Basics ===\n";

    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);  // queue: 10 (front), 20, 30 (back)

    cout << "Front: " << q.front() << ", Back: " << q.back() << endl;

    q.pop();  // removes 10
    cout << "After pop, Front: " << q.front() << endl;

    cout << "Size: " << q.size() << ", Empty? " << boolalpha << q.empty() << endl;
}

void queue_with_list() {
    cout << "\n=== std::queue with list as base ===\n";

    // Use list<T> as underlying container instead of deque
    queue<int, list<int>> q;

    q.push(5);
    q.push(15);

    cout << "Front: " << q.front() << ", Back: " << q.back() << endl;
    q.pop();
    cout << "After pop, Front: " << q.front() << endl;
}

void queue_edge_cases() {
    cout << "\n=== Copy, Swap, Edge Cases ===\n";

    queue<string> q1;
    q1.push("first");
    q1.push("second");

    queue<string> q2 = q1;  // deep copy

    cout << "Copied front: " << q2.front() << endl;

    queue<string> temp;
    temp.push("new");

    q1.swap(temp);
    cout << "After swap, q1 front: " << q1.front() << endl;
}

int main() {
    basic_queue_usage();
    queue_with_list();
    queue_edge_cases();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::queue
============================================================================

C++98:
- Introduced as a container adapter
- Default base: deque<T>
- Exposes limited interface: push, pop, front, back, size, empty

C++11:
- Move semantics support
- emplace() → construct elements in-place

C++14:
- Minor allocator optimizations

C++17:
- Improved constexpr usage internally

C++20:
- Compatible with constexpr contexts (indirectly)
- Can be used with ranges (via wrapper)

============================================================================
HOW std::queue WORKS INTERNALLY
============================================================================

- It is an **adapter**, not a container
- Internally wraps another container (default = deque<T>)
- Provides queue semantics (FIFO):
    - push()   → adds at back
    - pop()    → removes from front
    - front()  → access first element
    - back()   → access last element

You can specify custom base:
    queue<int, list<int>> q;

============================================================================
COMPARISON – queue vs stack vs deque
============================================================================

| Feature              | queue<T>          | stack<T>           | deque<T>         |
|----------------------|-------------------|--------------------|------------------|
| FIFO                 | ✅ Yes             | ❌ No               | manual           |
| LIFO                 | ❌ No              | ✅ Yes              | manual           |
| Access front/back    | ✅ Both            | ✅ top()            | ✅ Both          |
| Random access        | ❌ No              | ❌ No               | ✅ Yes           |
| Underlying container | deque<T> (default)| deque<T> (default) | itself           |
| Iterators exposed?   | ❌ No              | ❌ No               | ✅ Yes           |

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- Cannot iterate over queue — iterators are not exposed
- Cannot directly access elements in the middle (no operator[], no iterators)
- Always use `.front()` to read, `.pop()` to remove
- Underlying container must support: push_back(), pop_front(), front(), back()

============================================================================
CHEAT SHEET – std::queue
============================================================================

Declaration:
    queue<T> q;
    queue<T, list<T>> q2;

Insertion:
    q.push(val);          // adds at back
    q.emplace(args...);   // C++11+, in-place construction

Access:
    q.front();            // first element
    q.back();             // last element
    q.size(), q.empty();

Removal:
    q.pop();              // removes from front

Copy/Swap:
    queue<T> q2 = q;
    q.swap(q2);

*/

