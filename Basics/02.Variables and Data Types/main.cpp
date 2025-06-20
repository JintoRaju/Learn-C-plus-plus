#include <iostream>     // For input and output using std::cout, std::endl
#include <string>       // For using std::string
#include <vector>
#include <map>
#include <tuple>        // For std::tuple (used with structured binding)
using namespace std;    // So we don't need to prefix std:: every time

int main() {
    // ------------------ BASIC DATA TYPES ------------------

    int age = 25;               // Integer type for whole numbers
    float temperature = 36.6f;  // Float type for decimal numbers (f suffix is required)
    double pi = 3.1415926535;   // Double type for more precise decimal values
    char grade = 'A';           // Character type (single quotes)
    bool isPassed = true;       // Boolean type (true or false)
    string name1 = "Jose";      // String type for text (requires #include <string>)

    cout << "Name: " << name1 << endl;
    cout << "Age: " << age << endl;
    cout << "Temperature: " << temperature << endl;
    cout << "Pi: " << pi << endl;
    cout << "Grade: " << grade << endl;
    cout << "Passed: " << isPassed << endl;

    // ------------------ CONSTANTS ------------------

    const float gravity = 9.8f;  // Constant value that cannot be changed
    cout << "Gravity: " << gravity << endl;

    // ------------------ TYPE MODIFIERS ------------------

    short smallValue = 32767;           // Uses less memory than int (range: -32768 to 32767)
    long long largeValue = 1234567890;  // Larger than long, introduced in C++11
    unsigned int positiveOnly = 100;    // Cannot store negative values

    cout << "Short: " << smallValue << endl;
    cout << "Long long: " << largeValue << endl;
    cout << "Unsigned: " << positiveOnly << endl;

    // ------------------ MULTIPLE DECLARATIONS ------------------

    int x1 = 10, y1 = 20, z = 30;  // Declare multiple variables of same type
    cout << "x1 + y1 + z = " << (x1 + y1 + z) << endl;

    // ------------------ AUTO TYPE DEDUCTION ------------------

    auto city = string("Chennai");  // Compiler infers type as string
    auto height = 5.9;              // Inferred as double
    auto flag = false;              // Inferred as bool

    cout << "City: " << city << ", Height: " << height << ", Flag: " << flag << endl;

    // C++11: auto introduced
    // C++14: relaxed some rules and added decltype(auto)
    // C++17: improved type deduction for templates
    // C++20: auto can be used in function parameters (requires trailing return type)

    // 'decltype' is used to declare a variable with the same type as another variable or expression.
    // It does NOT evaluate the expression. It only inspects its type.
    // Introduced in C++11.

    int a1 = 42;
    decltype(a1) b1 = 100;  // b1 has same type as a1 -> int
    cout << "b1 = " << b1 << endl;

    // ------------------ decltype WITH EXPRESSIONS ------------------

    int x2 = 10, y2 = 20;
    decltype(x2 + y2) sum = x2 + y2;  // sum is of type int
    cout << "sum = " << sum << endl;

    // ------------------ STRUCTURED BINDING (C++17) ------------------

    pair<int, string> userInfo = {1, "Jose"};
    auto [userId, userName] = userInfo;  // Structured binding (unpack tuple-like objects)

    cout << "ID: " << userId << ", User: " << userName << endl;

    // ------------------ VARIABLE INITIALIZATION STYLES ------------------

    int a2 = 5;           // Copy initialization
    int b2(10);           // Direct initialization
    int c{15};            // Uniform initialization (recommended in modern C++)

    cout << "a2 = " << a2 << ", b2 = " << b2 << ", c = " << c << endl;

    // C++11: uniform initialization (curly braces) introduced
    // Helps prevent narrowing conversions (e.g., float to int accidentally)

    // Uniform initialization avoids narrowing conversions
    // For example:
    // int x{3.14};   // Error: narrowing conversion from double to int
    // But this is allowed:
    int x3 = 3.14;      // Allowed: x3 will be 3, but this might be dangerous
    cout << "x3 = " << x3 << endl;

    // ------------------ INITIALIZING STRUCTS AND CLASSES ------------------

    struct Point {
        int x;
        int y;
    };

    Point p1 = {10, 20};  // Uniform initialization of struct
    cout << "Point p1: (" << p1.x << ", " << p1.y << ")" << endl;

    // ------------------ UNIFORM INITIALIZATION WITH VECTORS ------------------

    vector<int> numbers = {1, 2, 3, 4, 5};  // List initialization of vector
    cout << "Vector: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // ------------------ INITIALIZING MAPS ------------------

    map<string, int> marks = {
        {"Math", 90},
        {"Physics", 85},
        {"Chemistry", 88}
    };

    for (auto [subject, score] : marks) {
        cout << subject << ": " << score << endl;
    }

    // ------------------ C++17 STRUCTURED BINDING WITH TUPLE ------------------

    tuple<int, string, float> student = {1, "Jose", 8.5f};
    auto [studId, studName, cgpa] = student;
    cout << "ID: " << studId << ", Name: " << studName << ", CGPA: " << cgpa << endl;

    // ------------------ UNIFORM INITIALIZATION WITH ARRAYS ------------------

    int arr1[] = {10, 20, 30};      // old style array
    int arr2[3] {40, 50, 60};       // uniform initialization

    cout << "Array arr2: ";
    for (int val : arr2) {
        cout << val << " ";
    }
    cout << endl;

    // ------------------ NOTES ON VERSION DIFFERENCES ------------------

    // C++98: Initialization was inconsistent. Arrays used {}, objects used constructors or =.
    // C++11: Uniform initialization introduced using {} for all types
    // C++14: Allowed generalized lambda captures and relaxed some initialization rules
    // C++17: Introduced structured binding (used above with auto [a, b] = ...)
    // C++20: Brings support for constexpr virtual functions and new features, but no major changes to uniform init

    return 0;
}
