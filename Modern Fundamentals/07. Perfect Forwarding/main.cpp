#include <iostream>
#include <string>
#include <utility>  // for std::move, std::forward
using namespace std;

/*
================================================================================
MODERNCPP_PERFECTFORWARDING.CPP
================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O When writing **generic functions** (e.g., templates), we don’t always know
  whether the arguments passed are lvalues or rvalues.

O If we:
   - Pass an lvalue → should be passed as const-ref or ref
   - Pass an rvalue → should be moved

O `Perfect Forwarding` ensures arguments are **forwarded as-is**
   O i.e., preserves their value category (lvalue/rvalue)

Used in:
O Factory functions, wrapper APIs, STL containers (e.g., emplace_back)

================================================================================
TOPICS COVERED
================================================================================
1. Reference collapsing rules
2. Forwarding reference: T&& in a template
3. std::move vs std::forward
4. Forwarding in wrapper and factory functions
5. Best practices and version notes
================================================================================
*/

//------------------------------------------------------------------------------
// 1. Reference Collapsing Rules (C++11)
//------------------------------------------------------------------------------
// Only relevant in templates — T& && => T&
// ------------------------------
//   T     | Declared as | Result
// --------|-------------|--------
//   int   | T&          | int&
//   int   | T&&         | int&&
//   int&  | T&&         | int&
//   int&& | T&&         | int&&
//------------------------------------------------------------------------------
void inspect(int&)  { cout << "[inspect] LValue ref\n"; }
void inspect(int&&) { cout << "[inspect] RValue ref\n"; }

template<typename T>
void check_reference_type(T&& arg) {
    inspect(std::forward<T>(arg));
}

//------------------------------------------------------------------------------
// 2. Demonstrate std::move vs std::forward
//------------------------------------------------------------------------------
void process(string& s) {
    cout << "[process] LValue: " << s << "\n";
}

void process(string&& s) {
    cout << "[process] RValue (moved): " << s << "\n";
}

// Wrapper that forwards any string
template<typename T>
void wrapper(T&& arg) {
    cout << "[wrapper] Forwarding...\n";
    process(forward<T>(arg));  // perfect forwarding
}

// Incorrect version: forces move on everything
template<typename T>
void wrong_wrapper(T&& arg) {
    cout << "[wrong_wrapper] Always moves!\n";
    process(move(arg));  // BAD: destroys even lvalues
}

//------------------------------------------------------------------------------
// 3. Forwarding in a Factory Pattern
//------------------------------------------------------------------------------
struct Person {
    string name;
    Person(const string& n) : name(n) {
        cout << "[Person] Copy ctor for " << name << "\n";
    }
    Person(string&& n) : name(move(n)) {
        cout << "[Person] Move ctor for " << name << "\n";
    }
};

// Factory function
template<typename T>
Person make_person(T&& n) {
    return Person(forward<T>(n));
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------
int main() {
    cout << "=== Reference Type Deduction ===\n";
    int a = 10;
    check_reference_type(a);          // lvalue
    check_reference_type(99);         // rvalue

    cout << "\n=== Forwarding vs Moving ===\n";
    string str = "Jose";
    wrapper(str);         // lvalue → stays lvalue
    wrapper(string("AI")); // rvalue → passed as rvalue
    wrong_wrapper(str);    // wrongly moved lvalue!

    cout << "\n=== Factory Forwarding ===\n";
    Person p1 = make_person(str);          // lvalue → copy
    Person p2 = make_person(string("GPT")); // rvalue → move

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced rvalue references and std::move
- Introduced perfect forwarding using T&& (when T is a template parameter)
- std::forward<T>(arg) = forward *only if T is rvalue*

C++14/17/20:
- Improved type deduction
- C++20 enables combining perfect forwarding with concepts
  (e.g., template<typename T> requires ...)

================================================================================
BEST PRACTICES
================================================================================
O Use `T&&` only in template functions — otherwise it’s just an rvalue ref
O Always use `std::forward<T>(arg)` in template wrappers to preserve value category
O Never use `std::move(arg)` on a forwarding reference unless you're sure
O Use `std::move(arg)` only for concrete rvalue cases
O In factories, use perfect forwarding to avoid unnecessary copies
*/
