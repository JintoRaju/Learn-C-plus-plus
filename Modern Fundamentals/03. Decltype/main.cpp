#include <iostream>
#include <vector>
#include <string>
using namespace std;

//
// WHY DO WE NEED `decltype`?
//
// Problem:
// In generic or template-based code, or when working with complex expressions,
// we may want to declare a variable with **exactly the same type** as another expression,
// including references or const qualifiers.
//
// `auto` works, but it always removes reference and const unless explicitly added.
//
// Solution:
// `decltype` (C++11) deduces the **exact type** (including reference and const) of any expression.
//
// C++14 introduced `decltype(auto)` — combines `auto` and `decltype` rules.
// Very useful in functions where return type should exactly match an expression.
//

int main() {
    // ----------- C++11: decltype with variables -----------
    int a = 42;
    const int& b = a;

    decltype(a) x = a;        // int
    decltype(b) y = b;        // const int&

    x = 10;
    cout << "x = " << x << ", y = " << y << endl;

    // ----------- C++11: decltype with expressions -----------

    int i = 5;
    decltype(i + 2) sum = i + 2;  // i is int, so result is int
    cout << "sum = " << sum << endl;

    decltype((i)) refToI = i;  // (i) is an lvalue, so deduces int&
    refToI = 100;
    cout << "refToI = " << refToI << ", i = " << i << endl;

    // ----------- C++14: decltype(auto) in variable declarations -----------

    auto result1 = (i);              // `auto` drops reference → int
    decltype(auto) result2 = (i);    // `decltype(auto)` preserves reference → int&

    result2 = 200;
    cout << "result1 = " << result1 << ", result2 = " << result2 << ", i = " << i << endl;

    // ----------- C++14: decltype(auto) in return type -----------

    auto getValue_auto = []() -> auto {
        int val = 10;
        return (val);    // returned as int
    };

    auto getValue_decltype_auto = []() -> decltype(auto) {
        static int val = 20;
        return (val);    // returned as int&
    };

    int val1 = getValue_auto();              // makes a copy of 10
    int& val2 = getValue_decltype_auto();    // refers to static int

    val2 = 99;
    cout << "getValue_auto() = " << val1 << endl;
    cout << "getValue_decltype_auto() = " << getValue_decltype_auto() << endl;

    return 0;
}

/*
--------------------------------------------------------------
VERSION HISTORY – decltype and decltype(auto)
--------------------------------------------------------------

C++11:
- Introduced `decltype(expr)` to deduce the exact type of an expression
- Can capture `const`, `&`, rvalue/lvalue distinction

C++14:
- Introduced `decltype(auto)` to combine `auto`'s simplicity with `decltype`'s accuracy
- Common in function return types: auto f() -> decltype(auto) { return expr; }

C++17:
- Used more with structured bindings and generic lambdas

C++20:
- No direct change, but heavily used with concepts, coroutines, and ranges
- Allows precise template return types and value category preservation

*/
