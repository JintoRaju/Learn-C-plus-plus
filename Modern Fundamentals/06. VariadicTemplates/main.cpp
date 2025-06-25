#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
using namespace std;

/*

================================================================================
WHY DO WE NEED THIS TOPIC?
--------------------------------------------------------------------------------
O To write generic code that works with **any number of types or arguments**
O Replaces the need to manually overload functions for 2, 3, 4, ... parameters
O Powers modern APIs like `std::tuple`, `std::format`, logging systems, etc.

Example use cases:
- Logging functions: log(msg1, msg2, msg3, ...)
- Type-safe containers that accept variadic types
- Perfect forwarding of arguments to constructors

================================================================================
TOPICS COVERED
================================================================================
1. Basic syntax: Variadic function templates
2. Recursive unpacking vs fold expressions (C++17)
3. Perfect forwarding with `std::forward` (C++11)
4. Base case handling
5. Variadic class templates
================================================================================
*/

//------------------------------------------------------------------------------
// 1. BASIC VARIADIC FUNCTION TEMPLATE
//------------------------------------------------------------------------------

void print_variadic() {
    cout << "[print_variadic] End of recursion\n";
}

// Recursive function to unpack parameters
template<typename T, typename... Rest>
void print_variadic(const T& first, const Rest&... rest) {
    cout << "[print_variadic] Arg: " << first << "\n";
    print_variadic(rest...); // Recursively process rest
}

/*
NOTES:
- `T` captures the first argument
- `Rest...` is a **parameter pack** that can hold 0 or more arguments
- `print_variadic(rest...)` unpacks and forwards remaining args
- Ends recursion when `Rest...` is empty
*/

//------------------------------------------------------------------------------
// 2. C++17 FOLD EXPRESSIONS (CLEANER WAY)
//------------------------------------------------------------------------------
template<typename... Args>
void print_fold(Args... args) {
    // Fold expression: applies << to each arg in order
    (cout << ... << args) << "\n";
}

//------------------------------------------------------------------------------
// 3. PERFECT FORWARDING WITH VARIADIC TEMPLATES
//------------------------------------------------------------------------------
template<typename... Args>
void call_me(Args&&... args) {
    cout << "[call_me] Forwarding to target...\n";
    forward_all(forward<Args>(args)...); // Perfectly forward args
}

void forward_all() {
    cout << "[forward_all] (no args)\n";
}

template<typename T, typename... Rest>
void forward_all(T&& arg, Rest&&... rest) {
    cout << "[forward_all] Got: " << arg << "\n";
    forward_all(forward<Rest>(rest)...);
}

/*
WHY PERFECT FORWARDING?
- Avoids unnecessary copies/moves
- Preserves lvalue/rvalue nature of arguments
*/

//------------------------------------------------------------------------------
// 4. VARIADIC CLASS TEMPLATE
//------------------------------------------------------------------------------
template<typename... Ts>
struct TypeHolder {
    static void show() {
        cout << "[TypeHolder] Holding " << sizeof...(Ts) << " types.\n";
    }
};

//------------------------------------------------------------------------------
// 5. TYPE INSPECTION USING `std::is_same` ON VARIADIC TYPES
//------------------------------------------------------------------------------
template<typename T, typename... Rest>
struct AllSame;

template<typename T>
struct AllSame<T> : true_type {}; // Base case: only one type

template<typename T, typename U, typename... Rest>
struct AllSame<T, U, Rest...> :
    conditional_t<is_same<T, U>::value, AllSame<T, Rest...>, false_type> {};

/*
Example:
AllSame<int, int, int>::value   => true
AllSame<int, float, int>::value => false
*/

int main() {
    cout << "=== Variadic Function (Recursion) ===\n";
    print_variadic("Apple", 42, 3.14, "Banana");

    cout << "\n=== Fold Expression (C++17) ===\n";
    print_fold("One ", 2, " Three ", 4.5);

    cout << "\n=== Perfect Forwarding ===\n";
    call_me("Hello", string("World"), 2025);

    cout << "\n=== Variadic Class ===\n";
    TypeHolder<int, double, string>::show();

    cout << "\n=== Type Check ===\n";
    cout << boolalpha;
    cout << "AllSame<int, int, int>: " << AllSame<int, int, int>::value << "\n";
    cout << "AllSame<int, float, int>: " << AllSame<int, float, int>::value << "\n";

    return 0;
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Introduced variadic templates
- Introduced std::forward, rvalue references
- Requires manual recursion to unpack arguments

C++14:
- Minor simplifications (e.g., auto return type deduction)

C++17:
- Introduced fold expressions: (op ... args), (args ... op), etc.
- Easier variadic logic without recursion

C++20:
- Concepts can restrict variadic packs (`requires` on Args...)
- Pack expansion in lambdas, `consteval` meta-programming, etc.

================================================================================
BEST PRACTICES
================================================================================
- Use `fold expressions` where possible for readability
- Always forward perfectly if passing parameters further
- For types: `sizeof...(T)` gives parameter count
- Avoid recursion unless needed — fold expressions are cleaner
*/
