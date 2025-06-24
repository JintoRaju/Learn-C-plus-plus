#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//
// WHY std::string?
//
// Problem:
// - C-style strings are null-terminated char arrays (`char[]` or `char*`)
// - Manual memory management, can't use operators like + or =
// - No easy length calculation or safe manipulation
//
// Solution:
// - std::string (C++98):
//     - Dynamic, resizeable, null-terminated string class
//     - Provides safety, convenience, and STL compatibility
//

void string_basics() {
    cout << "=== std::string Basics ===\n";

    string s1 = "hello";          // direct initialization
    string s2("world");           // constructor
    string s3 = s1 + " " + s2;    // concatenation

    cout << "Concatenated: " << s3 << endl;

    cout << "Size: " << s3.size() << ", Length: " << s3.length() << endl;
    cout << "First char: " << s3.front() << ", Last char: " << s3.back() << endl;
}

void string_modification() {
    cout << "\n=== Modifying Strings ===\n";

    string s = "Hello";

    s.push_back('!');
    s.append(" World");

    cout << "After append: " << s << endl;

    s.insert(5, ",");
    s.replace(0, 5, "Hi");
    s.erase(6, 5);  // erase "World"

    cout << "Modified string: " << s << endl;

    s.pop_back();
    cout << "After pop_back: " << s << endl;
}

void string_search_substr() {
    cout << "\n=== Searching and Substrings ===\n";

    string s = "the quick brown fox jumps";

    size_t pos = s.find("brown");
    if (pos != string::npos)
        cout << "'brown' found at position " << pos << endl;

    string sub = s.substr(4, 5);  // "quick"
    cout << "Substring: " << sub << endl;

    // Replace all ' ' with '-'
    replace(s.begin(), s.end(), ' ', '-');
    cout << "After replace: " << s << endl;
}

void string_comparison_and_input() {
    cout << "\n=== Comparison and Input ===\n";

    string a = "apple";
    string b = "banana";

    cout << (a < b ? "apple < banana" : "banana < apple") << endl;

    string user_input;
    cout << "Enter a line: ";
    getline(cin, user_input);  // reads spaces too

    cout << "You entered: " << user_input << endl;
}

int main() {
    string_basics();
    string_modification();
    string_search_substr();
    string_comparison_and_input();
    return 0;
}

/*
============================================================================
VERSION NOTES – std::string
============================================================================

C++98:
- Introduced std::string as part of STL
- Dynamic, null-terminated, operator overloads for +, =
- .c_str() to get raw char*

C++11:
- Move semantics → more efficient transfers (e.g., return by value)
- u16string, u32string (UTF support) introduced
- Raw string literals: R"(line1\nline2)"
- to_string(), stoi(), etc.

C++14:
- Minor improvements in allocator and performance

C++17:
- .data() guaranteed to be null-terminated (previously only .c_str())
- Avoids copies in certain expressions due to guaranteed copy elision

C++20:
- Compatible with constexpr in limited forms
- Full support in ranges and string_view usage

============================================================================
TINY BUT IMPORTANT DETAILS
============================================================================

- `std::string` always stores null-terminated string (safe for C interop)
- Use `.c_str()` to pass to C-style APIs
- Use `.data()` for buffer usage (null-terminated since C++17)
- Internally uses **Small String Optimization (SSO)**:
    - Short strings stored in-place, no heap allocation

- Iterator invalidation:
    - push_back / append may invalidate iterators
    - insert / erase always invalidate iterators after point of change

============================================================================
COMPARISON – std::string vs char[]
============================================================================

| Feature              | char[]            | std::string          |
|----------------------|-------------------|----------------------|
| Dynamic resizing     | ❌ Manual only     | ✅ Yes               |
| Operator +           | ❌ Not supported   | ✅ Yes               |
| Null-terminated      | ✅ Yes             | ✅ Yes               |
| Safe memory          | ❌ No              | ✅ RAII managed      |
| Length calculation   | O(n) (strlen)     | O(1) with .size()    |
| STL compatible       | ❌ No              | ✅ Fully compatible  |

============================================================================
CHEAT SHEET – std::string
============================================================================

Declaration:
    string s = "text";
    string s("text");
    string s(n, 'x');        // repeat char x n times

Appending:
    s += "hello";
    s.append("world");
    s.push_back('!');

Modifying:
    s.insert(pos, str);
    s.replace(pos, len, str);
    s.erase(pos, len);
    s.pop_back();

Searching:
    s.find("sub");
    s.substr(pos, len);
    s.rfind("last");

Comparisons:
    s1 == s2, s1 < s2, etc.

C interop:
    s.c_str();     // returns const char*
    s.data();      // same as c_str() since C++17

Input:
    cin >> s;               // word only
    getline(cin, s);        // full line

*/

