#include <iostream>
#include <memory>     // For smart pointers
#include <string>
#include <vector>

using namespace std;

//
// C++ MEMORY AND SMART POINTERS – FULL DEEP DIVE
// ----------------------------------------------
// Goal: Understand raw vs smart memory handling in Modern C++
// Structure:
//   1. Raw pointer problems (motivation)
//   2. unique_ptr (exclusive ownership)
//   3. shared_ptr (shared ownership)
//   4. weak_ptr (non-owning reference)
//   5. make_unique / make_shared (safe allocation)
//   6. Custom deleters
//   7. Circular reference problem and fix
// All code includes inline reasoning and version evolution.
//

// Simple tracing class
struct Logger {
    string tag;
    Logger(string t) : tag(std::move(t)) {
        cout << "Constructed: " << tag << "\n";
    }
    ~Logger() {
        cout << "Destructed : " << tag << "\n";
    }
};

// 1. RAW POINTER PROBLEM
void raw_pointer_problem() {
    cout << "\n[1] Raw pointer leak and exception-safety issue:\n";

    Logger* obj = new Logger("RawPointer");
    // memory leak risk: if you return early, throw, or forget delete

    delete obj; // must manually release
}

// 2. UNIQUE_PTR – C++11
void unique_ptr_demo() {
    cout << "\n[2] unique_ptr – exclusive ownership (C++11):\n";

    unique_ptr<Logger> uptr1 = make_unique<Logger>("Unique_1");

    // unique_ptr ensures that only one owner exists
    // unique_ptr<Logger> uptr2 = uptr1; // ERROR: copy not allowed

    unique_ptr<Logger> uptr2 = move(uptr1); // ownership transferred

    if (!uptr1) cout << "uptr1 is now null after move\n";

    // automatic deletion when uptr2 goes out of scope
}

// 3. SHARED_PTR – C++11
void shared_ptr_demo() {
    cout << "\n[3] shared_ptr – shared ownership (C++11):\n";

    shared_ptr<Logger> sp1 = make_shared<Logger>("Shared_1");

    {
        shared_ptr<Logger> sp2 = sp1; // increases ref count
        cout << "Use count (sp1): " << sp1.use_count() << "\n";
    } // sp2 out of scope

    cout << "Use count after sp2 dies: " << sp1.use_count() << "\n";
}

// 4. WEAK_PTR – C++11
void weak_ptr_demo() {
    cout << "\n[4] weak_ptr – observer without ownership (C++11):\n";

    shared_ptr<Logger> sp = make_shared<Logger>("Shared_2");
    weak_ptr<Logger> wp = sp; // no ownership, no use_count increase

    cout << "Use count (before reset): " << sp.use_count() << "\n";
    sp.reset(); // manually destroy shared object

    if (wp.expired())
        cout << "weak_ptr expired after shared_ptr reset\n";
    else
        cout << "Still alive\n";
}

// 5. make_unique and make_shared – C++14+
void factory_methods_demo() {
    cout << "\n[5] make_unique / make_shared (C++14+):\n";

    auto up = make_unique<Logger>("make_unique()");
    auto sp = make_shared<Logger>("make_shared()");

    cout << "shared_ptr use count: " << sp.use_count() << "\n";
}

// 6. CUSTOM DELETER – C++11
void custom_deleter_demo() {
    cout << "\n[6] unique_ptr with custom deleter (C++11):\n";

    auto del = [](Logger* l) {
        cout << "Custom deleting: " << l->tag << "\n";
        delete l;
    };

    unique_ptr<Logger, decltype(del)> uptr(new Logger("CustomDel"), del);
}

// 7. CIRCULAR REFERENCE – The shared_ptr Trap
struct Node {
    string label;
    shared_ptr<Node> next;
    weak_ptr<Node> prev; // prevents circular ownership

    Node(string l) : label(std::move(l)) {
        cout << "Created Node(" << label << ")\n";
    }
    ~Node() {
        cout << "Destroyed Node(" << label << ")\n";
    }
};

void circular_reference_demo() {
    cout << "\n[7] Circular reference fix using weak_ptr:\n";

    auto a = make_shared<Node>("A");
    auto b = make_shared<Node>("B");

    a->next = b;
    b->prev = a; // weak_ptr avoids strong ownership cycle

    cout << "Use count A: " << a.use_count() << ", B: " << b.use_count() << "\n";
    // No leak occurs: objects properly destructed at end
}

int main() {
    raw_pointer_problem();
    unique_ptr_demo();
    shared_ptr_demo();
    weak_ptr_demo();
    factory_methods_demo();
    custom_deleter_demo();
    circular_reference_demo();
    return 0;
}

/*
============================================================================
VERSION NOTES
============================================================================

 C++11:
- Introduced unique_ptr, shared_ptr, weak_ptr
- `std::move()` required for transferring unique_ptr ownership
- `shared_ptr` uses internal control block with reference counting
- Custom deleters supported via template arg

 C++14:
- Introduced `make_unique<T>()`
- `make_shared<T>()` was in C++11 but refined further

 C++17:
- Added support for `shared_ptr<T[]>`
- Better support for polymorphic delete via custom deleters

 C++20:
- Added atomic operations on shared_ptr
- Better constexpr and allocator support in some smart ptr APIs

============================================================================
SUMMARY – C++ MEMORY CHEAT SHEET
============================================================================

| Pointer Type      | Ownership         | Copyable | Use Case                         |
|-------------------|-------------------|----------|----------------------------------|
| Raw pointer       | Manual            | Yes      | Legacy / performance only        |
| unique_ptr<T>     | Exclusive         | No       | One owner, no sharing            |
| shared_ptr<T>     | Shared (ref count)| Yes      | Multiple owners (plugins, events)|
| weak_ptr<T>       | Observer only     | Yes      | Avoid circular refs / caching    |

Key Methods:
- `make_unique<T>()`  → safest way to allocate
- `make_shared<T>()`  → optimized for performance
- `.reset()` → manually release ownership
- `.use_count()` → track active shared_ptr references
- `.expired()` / `.lock()` → weak_ptr safety

Pitfalls to Avoid:
- Do not mix raw + smart pointers
- Avoid shared_ptr cycles without weak_ptr
- Do not pass raw pointers to multiple smart_ptrs
- Prefer factory functions over manual `new`

*/
