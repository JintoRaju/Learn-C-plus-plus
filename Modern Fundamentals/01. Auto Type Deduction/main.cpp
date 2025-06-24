#include <iostream>
#include <vector>
#include <string>
using namespace std;

//
// WHY DO WE NEED `auto`?
//
// Problem:
// Writing type names like `vector<string>::iterator` or `map<int, pair<int, string>>::const_iterator` is long and error-prone.
// In many cases, the type is obvious from the right-hand side of assignment.
//
// Solution:
// The `auto` keyword (introduced in C++11) allows the compiler to deduce the type for us from context.
// It makes code shorter, safer, and easier to maintain.
//

int main() {
    // ----------- C++11: Basic auto -----------
    auto i = 10;         // compiler deduces i as int
    auto d = 3.14;       // deduced as double
    auto name = "Jose";  // deduced as const char*

    cout << "i = " << i << ", d = " << d << ", name = " << name << endl;

    // ----------- C++11: Auto with containers -----------

    vector<int> numbers = {1, 2, 3, 4, 5};

    // Instead of writing: vector<int>::iterator it = numbers.begin();
    // We can write:
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << " <-- iterated using auto" << endl;

    // ----------- C++14: Auto in lambda function parameters -----------

    // C++14 introduced generic lambdas using auto as parameter types
    auto print = [](auto value) {
        cout << "Generic lambda print: " << value << endl;
    };

    print(123);       // int
    print(3.1415);    // double
    print("text");    // const char*

    // ----------- C++17: Structured bindings with auto -----------

    pair<int, string> item = {42, "Apple"};

    // C++17 introduced structured bindings with auto
    auto [code, label] = item;  // unpack pair into two variables

    cout << "Structured binding: code = " << code << ", label = " << label << endl;

    // ----------- C++20: Auto in template parameters (combined with concepts) -----------

    // In C++20, auto can be used as a generic template parameter (with optional concept constraints)
    auto add = [](auto a, auto b) {
        return a + b;
    };

    cout << "add(2, 3) = " << add(2, 3) << endl;
    cout << "add(2.5, 3.5) = " << add(2.5, 3.5) << endl;

    return 0;
}

/*
-----------------------------------------------------------
VERSION HISTORY – `auto` KEYWORD IN MODERN C++
-----------------------------------------------------------

C++98:
- `auto` existed, but meant "storage duration", not type deduction (rarely used).

C++11:
- Introduced real type inference with `auto`
- Allows variables to automatically deduce type from initializer

C++14:
- Allowed `auto` in lambda parameter lists (generic lambdas)
- Example: `[](auto x) { return x; }`

C++17:
- Structured bindings: unpack tuples/pairs using `auto [a, b] = something;`

C++20:
- Auto can be used in template parameters (e.g., `auto func(auto a)`)
- Works with concepts (`auto` with constraints) for clean generic programming

*/
