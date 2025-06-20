#include <iostream>
using namespace std;

//
// WHY DO WE NEED FUNCTIONS?
//
// Imagine repeating the same logic (like printing a welcome message, doing math, etc.) many times.
// Copy-pasting the same code is inefficient, error-prone, and hard to maintain.
//
// Functions help us:
// - Group reusable logic
// - Avoid repetition
// - Make code easier to read, test, and update
// - Divide complex problems into smaller tasks
//

// ------------------ BASIC FUNCTION ------------------
// A function that takes two integers and returns their sum.
int add(int a, int b) {
    return a + b;
}

// ------------------ FUNCTION WITH NO RETURN ------------------
// This function just prints a message. Return type is void.
void printGreeting() {
    cout << "Welcome to the Function Tutorial!" << endl;
}

// ------------------ FUNCTION WITH DEFAULT ARGUMENT ------------------
// Second parameter has a default value. If not passed, it uses 10.
int multiply(int x, int y = 10) {
    return x * y;
}

// ------------------ FUNCTION WITH auto RETURN TYPE (C++14+) ------------------
// Compiler infers the return type
auto divide(int a, int b) {
    return static_cast<double>(a) / b;  // ensures decimal result
}

// ------------------ FUNCTION RETURNING REFERENCE ------------------
// Allows the caller to modify the original variable
int globalVar = 100;

int& getGlobalRef() {
    return globalVar;
}

// ------------------ consteval FUNCTION (C++20) ------------------
// Must be evaluated at compile time
consteval int square(int x) {
    return x * x;
}

// ------------------ constexpr FUNCTION (C++11+) ------------------
// Can be evaluated at compile time or runtime
constexpr int cube(int x) {
    return x * x * x;
}

// ------------------ MAIN FUNCTION ------------------
int main() {
    printGreeting();  // Call to function with no return

    int sum = add(5, 7);  // Call to function with arguments
    cout << "Sum = " << sum << endl;

    int product1 = multiply(3);        // uses default y = 10
    int product2 = multiply(3, 4);     // overrides default
    cout << "Product1 = " << product1 << ", Product2 = " << product2 << endl;

    auto result = divide(10, 4);       // returns double
    cout << "Division = " << result << endl;

    getGlobalRef() = 500;              // modify globalVar through reference
    cout << "Modified globalVar = " << globalVar << endl;

    // Compile-time square using consteval
    constexpr int s = square(6);
    cout << "Square (compile-time only): " << s << endl;

    // Runtime cube using constexpr
    int x;
    cout << "Enter a number: ";
    cin >> x;
    cout << "Cube of " << x << " = " << cube(x) << endl;

    return 0;
}
