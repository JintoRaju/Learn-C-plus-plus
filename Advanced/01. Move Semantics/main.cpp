#include <iostream>
#include <string>
#include <vector>
using namespace std;

//
// WHY DO WE NEED MOVE SEMANTICS?
//
// Problem:
// Copying large objects (like strings, vectors, custom classes) is expensive
// because it involves deep memory duplication.
//
// Solution:
// C++11 introduced **move semantics** to avoid unnecessary copies.
// - Instead of copying data, we can *move* ownership of resources
// - It's fast: only pointers or internal data are transferred, no duplication
//
// Tools:
// - `&&` rvalue reference: represents a temporary object that can be moved from
// - `std::move()`: tells compiler it's safe to move
//

class Data {
public:
    string name;
    vector<int> values;

    // Constructor
    Data(string n, vector<int> v) : name(move(n)), values(move(v)) {
        cout << "Constructor\n";
    }

    // Copy Constructor (C++11)
    Data(const Data& other) : name(other.name), values(other.values) {
        cout << "Copy Constructor\n";
    }

    // Move Constructor (C++11)
    Data(Data&& other) noexcept : name(move(other.name)), values(move(other.values)) {
        cout << "Move Constructor\n";
    }

    // Copy Assignment (C++11)
    Data& operator=(const Data& other) {
        name = other.name;
        values = other.values;
        cout << "Copy Assignment\n";
        return *this;
    }

    // Move Assignment (C++11)
    Data& operator=(Data&& other) noexcept {
        name = move(other.name);
        values = move(other.values);
        cout << "Move Assignment\n";
        return *this;
    }

    void print() const {
        cout << "Data[name=" << name << ", values=";
        for (int v : values) cout << v << " ";
        cout << "]\n";
    }
};

int main() {
    // ----------- Regular construction -----------
    Data d1("one", {1, 2, 3}); // calls constructor

    // ----------- Copy construction -----------
    Data d2 = d1;              // calls copy constructor

    // ----------- Move construction (C++11) -----------
    Data d3 = move(d1);        // calls move constructor

    // d1 is now in a valid but unspecified state (safe to destroy, not to use)

    // ----------- Copy assignment -----------
    Data d4("four", {4, 5, 6});
    d4 = d2;                   // calls copy assignment

    // ----------- Move assignment -----------
    Data d5("temp", {99});
    d5 = move(d4);             // calls move assignment

    // ----------- Printing final states -----------
    d2.print();
    d3.print();
    d4.print();
    d5.print();

    return 0;
}

/*
---------------------------------------------------------------
VERSION HISTORY – MOVE SEMANTICS AND std::move
---------------------------------------------------------------

C++98:
- Only copy constructors and copy assignment
- No distinction between temporary (rvalue) and regular (lvalue) objects

C++11:
- Introduced rvalue references (`T&&`)
- Added:
    - Move constructor: `T(T&&)`
    - Move assignment operator: `T& operator=(T&&)`
- `std::move(expr)` marks an object as rvalue so it can be moved from

C++14:
- Move semantics more widely adopted, used with `auto` and return value optimization (RVO)

C++17:
- Return value optimization (RVO) made mandatory in many cases (no copy or move required)

C++20:
- Concepts and ranges use move semantics under the hood
- Improved constexpr + move support

*/

/*
./main.exe
Constructor
Copy Constructor
Move Constructor
Constructor
Copy Assignment
Constructor
Move Assignment
Data[name=one, values=1 2 3 ]
Data[name=one, values=1 2 3 ]
Data[name=, values=]
Data[name=one, values=1 2 3 ]
*/