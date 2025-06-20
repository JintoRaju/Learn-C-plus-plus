#include <iostream>
#include <string>
using namespace std;

//
// WHY DO WE NEED FUNCTION TEMPLATES?
//
// Problem:
// Suppose we want to write a function that adds two values.
// We can write one for int, one for double, one for string, etc.
// But writing separate versions for every type leads to code duplication.
//
// Solution:
// Templates allow us to write a **single generic function** that works for any data type.
// The compiler generates the correct version automatically based on the argument types.
//

// ------------------ BASIC FUNCTION TEMPLATE ------------------
// T is a placeholder for any type (int, double, string, etc.)

template <typename T>
T add(T a, T b) {
    return a + b;
}

// ------------------ TEMPLATE WITH TWO DIFFERENT TYPES ------------------

template <typename T1, typename T2>
auto multiply(T1 a, T2 b) {
    return a * b;
}

// ------------------ TEMPLATE WITH NON-TYPE ARGUMENT (C++11+) ------------------
// This allows passing a constant value to a template

template <typename T, int N>
T scale(T value) {
    return value * N;
}

// ------------------ MAIN FUNCTION ------------------

int main() {
    // Function template called with integers
    int intSum = add(3, 4);
    cout << "add(3, 4) = " << intSum << endl;

    // Called with doubles
    double doubleSum = add(1.5, 2.7);
    cout << "add(1.5, 2.7) = " << doubleSum << endl;

    // Called with strings
    string strSum = add(string("Hello "), string("World"));
    cout << "add(\"Hello \", \"World\") = " << strSum << endl;

    // Multiply using different types
    auto result1 = multiply(5, 2.5);   // int * double
    auto result2 = multiply(3.5, 2);   // double * int
    cout << "multiply(5, 2.5) = " << result1 << endl;
    cout << "multiply(3.5, 2) = " << result2 << endl;

    // Use non-type template argument (C++11+)
    int scaled = scale<int, 4>(10);   // 10 * 4
    cout << "scale<int, 4>(10) = " << scaled << endl;

    return 0;
}
