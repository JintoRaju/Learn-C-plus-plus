#include <iostream>
#include <stack>
#include <vector>   // optional: used to show custom underlying container
#include <deque>
using namespace std;

//
// WHY std::stack?
//
// Problem:
// - Need a simple LIFO (Last-In-First-Out) structure
// - std::vector and std::deque can be used manually, but repetitive boilerplate
//
// Solution:
// - std::stack is a **container adapter**
//     - Built on top of an underlying container
//     - Hides everything except: push(), pop(), top(), size(), empty()
//

void basic_stack_usage() {
    cout << "=== std::stack Basics ===\n";

    stack<int> stk;  // default underlying container = deque<int>

    stk.push(10);
    stk.push(20);
    stk.push(30);  // Stack now: top = 30

    cout << "Top element: " << stk.top() << endl;

    stk.pop(); // removes 30
    cout << "Top after pop: " << stk.top() << endl;

    cout << "Size: " << stk.size() << endl;
    cout << "Is empty? " << boolalpha << stk.empty() << endl;
}

void stack_with_vector() {
    cout << "\n=== std::stack with vector as base ===\n";

    // C++98+ allows changing the base container
    stack<int, vector<int>> stk;

    stk.push(5);
    stk.push(15);

    cout << "Top: " << stk.top() << endl;
    stk.pop();
    cout << "After pop, Top: " << stk.top() << endl;
}

void stack_edge_cases() {
    cout << "\n=== Edge Cases ===\n";

    stack<string> stk;

    stk.push("first");
    stk.push("second");

    // Copying entire stack
    stack<string> copied = stk;

    cout << "Copied top: " << copied.top() << endl;

    // Swapping
    stack<string> another;
    another.push("new");

    stk.swap(another);
    cout << "After swap, stk top: " << stk.top() << endl;
}

int main() {
    basic_stack_usage();
    stack_with_vector();
    stack_edge_cases();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::stack
============================================================================

C++98:
- Introduced as a container adapter
- Default base container: deque<T>
- Public functions: push(), pop(), top(), size(), empty()
- No iterators exposed

C++11:
- Move semantics support
- Emplace added: stk.emplace(val) → construct in-place (faster)

C++14:
- Minor allocator optimizations

C++17:
- constexpr improvements (limited)

C++20:
- Compatible with ranges (indirectly)
- More constexpr and move improvements

============================================================================
INTERNALS: How std::stack works
============================================================================

- std::stack is not a container; it is an adapter
- Internally wraps another container (like vector or deque)
- Default container is: deque<T>
    stack<int> stk;         // same as stack<int, deque<int>>
    stack<int, vector<int>> stk2;

- It disables access to iterators and element access like [i]

============================================================================
COMPARISON – stack vs vector vs deque
============================================================================

| Feature             | stack<T>          | vector<T>         | deque<T>         |
|---------------------|-------------------|-------------------|------------------|
| LIFO abstraction     |  Yes             |  No (manual)     |  No (manual)    |
| Access top()         |  Yes             |  Yes (back())    |  Yes (back())   |
| push/pop front/back  | push/pop only top | manual front/back | manual front/back|
| Random access        |  No              |  Yes             |  Yes            |
| Iterators            |  Not available   |  Yes             |  Yes            |

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `std::stack` has no iterators — not suitable for traversal
- Designed for pure LIFO use only
- Cannot access underlying container directly (unless using .swap or emplace tricks)
- Always remember: `.top()` does NOT remove the element — call `.pop()` to remove
- Stack is **copyable**, swappable, moveable since C++11

============================================================================
CHEAT SHEET – std::stack
============================================================================

Declaration:
    stack<T> stk;
    stack<T, vector<T>> stk2;

Insertion:
    stk.push(val);
    stk.emplace(args...);  // C++11+

Access:
    stk.top();             // returns reference to top element
    stk.size(); stk.empty();

Removal:
    stk.pop();             // removes top

Copy/Swap:
    stack<T> b = stk;
    stk.swap(other);

*/

