#include <iostream>
#include <string>
using namespace std;

//
// WHY DO WE NEED FUNCTION OVERLOADING?
//
// Often, we need to perform the same operation for different types of input.
// For example: printing an int, printing a double, or printing a string.
//
// Instead of writing different function names like printInt, printDouble, printString,
// we use the **same function name with different parameter types or counts**.
//
// This makes the code cleaner, more readable, and closer to human thinking.
//
// C++ supports this through "function overloading".
//

// ------------------ OVERLOADED FUNCTIONS ------------------

// Function 1: Takes two integers
int add(int a, int b) {
    return a + b;
}

// Function 2: Takes two doubles
double add(double a, double b) {
    return a + b;
}

// Function 3: Takes three integers
int add(int a, int b, int c) {
    return a + b + c;
}

// Function 4: Concatenates two strings
string add(string a, string b) {
    return a + b;
}

// Function 5: Mix of int and double
double add(int a, double b) {
    return a + b;
}

// ------------------ MAIN ------------------
int main() {
    cout << "add(3, 4) = " << add(3, 4) << endl;                     // calls int + int
    cout << "add(2.5, 3.1) = " << add(2.5, 3.1) << endl;             // calls double + double
    cout << "add(1, 2, 3) = " << add(1, 2, 3) << endl;               // calls int + int + int
    cout << "add(\"Hello\", \"World\") = " << add("Hello", "World") << endl; // calls string + string
    cout << "add(10, 2.5) = " << add(10, 2.5) << endl;               // calls int + double

    return 0;
}
