#include <iostream>
#include <string>
using namespace std;

//
// WHY DO WE NEED CLASS TEMPLATES?
//
// Problem:
// Sometimes we write classes that work with specific data types, like `int`, `float`, or `string`.
// If we need the same class logic for different types, we might copy-paste and rewrite the same class.
// This creates duplication, which is hard to maintain.
//
// Solution:
// Class templates allow writing a **generic class** that works with **any data type**.
// The compiler automatically generates a version of the class for each type we use.
//

// ------------------ CLASS TEMPLATE ------------------

template <typename T>
class Box {
private:
    T value;

public:
    Box(T val) : value(val) {}

    void setValue(T val) {
        value = val;
    }

    T getValue() const {
        return value;
    }
};

// ------------------ CLASS TEMPLATE WITH TWO TYPES ------------------

template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(T1 a, T2 b) : first(a), second(b) {}

    void display() const {
        cout << "First: " << first << ", Second: " << second << endl;
    }
};

// ------------------ MAIN FUNCTION ------------------

int main() {
    Box<int> intBox(100);
    cout << "Box<int>: " << intBox.getValue() << endl;

    Box<string> strBox("Template");
    cout << "Box<string>: " << strBox.getValue() << endl;

    Pair<int, string> item(1, "Apple");
    item.display();

    Pair<double, bool> flags(3.14, true);
    flags.display();

    return 0;
}

/*
--------------------------------------
VERSION HISTORY - CLASS TEMPLATES
--------------------------------------

C++98:
- Introduced class templates using `template<typename T>` or `template<class T>`
- Syntax for template instantiation: ClassName<Type> obj;

C++11:
- Added features like `auto`, `nullptr`, and improved initialization
- Allowed more types for non-type template parameters (e.g., pointers, nullptr)

C++14:
- Simplified type deduction and allowed `auto` return type in methods
- Still no automatic deduction for class template arguments

C++17:
- Added class template argument deduction (CTAD) for some standard library templates
- Still not available for user-defined class templates unless manually defined

C++20:
- Concepts introduced to constrain template parameters (used with class templates)
- You can write: template<typename T> requires SomeConcept<T> class MyClass
- Enables safer, clearer error messages when using templates

*/
