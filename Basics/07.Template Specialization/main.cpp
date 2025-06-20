#include <iostream>
#include <string>
using namespace std;

//
// WHY DO WE NEED TEMPLATE SPECIALIZATION?
//
// Problem:
// A class template works for all types, but sometimes we need **different logic for a specific type**.
// For example, we may want to print "true/false" for `bool` instead of 1/0.
//
// Solution:
// Template specialization lets us override the generic template's behavior **for one or more specific types**.
// This avoids if-else or type-checking code inside the template.
//
// Two types:
// 1. Full specialization — completely replaces the template for a specific type
// 2. Partial specialization — modifies the behavior for a subset of template parameters
//

// ------------------ GENERIC CLASS TEMPLATE ------------------

template <typename T>
class Printer {
public:
    void print(T value) {
        cout << "Value: " << value << endl;
    }
};

// ------------------ FULL SPECIALIZATION FOR bool ------------------

template <>
class Printer<bool> {
public:
    void print(bool value) {
        cout << "Value: " << (value ? "true" : "false") << endl;
    }
};

// ------------------ PARTIAL SPECIALIZATION ------------------

template <typename T>
class PairPrinter {
public:
    void print(T a, T b) {
        cout << "Pair: " << a << " and " << b << endl;
    }
};

// Partial specialization: both parameters are const char*
template <>
class PairPrinter<const char*> {
public:
    void print(const char* a, const char* b) {
        cout << "CString Pair: \"" << a << "\" and \"" << b << "\"" << endl;
    }
};

// ------------------ MAIN FUNCTION ------------------

int main() {
    Printer<int> intPrinter;
    intPrinter.print(42);  // uses generic template

    Printer<string> strPrinter;
    strPrinter.print("Hello");  // uses generic template

    Printer<bool> boolPrinter;
    boolPrinter.print(true);  // uses specialized version

    PairPrinter<int> pair1;
    pair1.print(10, 20);  // generic

    PairPrinter<const char*> pair2;
    pair2.print("First", "Second");  // specialized

    return 0;
}

/*
------------------------------------------
VERSION HISTORY - TEMPLATE SPECIALIZATION
------------------------------------------

C++98:
- Introduced support for full and partial specialization
- Full specialization: template<> class ClassName<Type> { ... }
- Partial specialization: template<typename T> class ClassName<T*> { ... }

C++11:
- Allowed `nullptr`, variadic templates, and better default arguments
- Made specialization easier with variadic types

C++14:
- No direct changes to specialization, but improved compiler inference and diagnostics

C++17:
- Structured bindings and class template argument deduction (CTAD) helped combine with templates

C++20:
- Concepts can be used with specializations to restrict which types are allowed
- Example: template<typename T> requires Integral<T> class MyPrinter;

*/
