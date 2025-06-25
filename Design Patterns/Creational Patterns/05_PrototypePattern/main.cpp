#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_05_PROTOTYPE_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O When creating a new object is expensive (deep setup, resource loading)
O When we want to avoid subclass instantiation and clone from an existing template

O Use Cases:
- Cloning game characters/items with same base properties
- Caching UI components or documents
- Deep copy of graphs, trees, etc.

================================================================================
CORE IDEA
--------------------------------------------------------------------------------
- Define a common interface with a `clone()` method
- Each class implements its own cloning
- You duplicate objects without knowing their concrete types

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, unique_ptr, move semantics
O C++14: make_unique
O C++20: structured bindings, `auto&&` (not shown here)
================================================================================
*/

// -----------------------------------------------------------------------------
// Step 1: Prototype Interface
// -----------------------------------------------------------------------------
class Document {
public:
    virtual unique_ptr<Document> clone() const = 0;
    virtual void show() const = 0;
    virtual ~Document() = default;
};

// -----------------------------------------------------------------------------
// Step 2: Concrete Prototypes
// -----------------------------------------------------------------------------
class Resume : public Document {
    string name;
    string education;

public:
    Resume(string n, string edu) : name(move(n)), education(move(edu)) {}

    unique_ptr<Document> clone() const override {
        return make_unique<Resume>(*this);  // shallow copy is fine here
    }

    void show() const override {
        cout << "[Resume]\n  Name: " << name << "\n  Education: " << education << "\n";
    }
};

class Report : public Document {
    string title;
    string content;

public:
    Report(string t, string c) : title(move(t)), content(move(c)) {}

    unique_ptr<Document> clone() const override {
        return make_unique<Report>(*this); // copy constructor
    }

    void show() const override {
        cout << "[Report]\n  Title: " << title << "\n  Content: " << content << "\n";
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Added unique_ptr, override, move semantics

C++14:
- make_unique simplifies memory handling

C++20:
- clone() could return `auto` with constrained concepts (not shown)

================================================================================
BEST PRACTICES
================================================================================
O Always use smart pointers to avoid manual memory leaks
O Deep copy internal data if object holds raw pointers
O Use copy constructor or clone pattern for polymorphic duplication
O Consider prototype registry/cache if reusing templates repeatedly
================================================================================
*/

int main() {
    // Create prototype
    unique_ptr<Document> resumePrototype = make_unique<Resume>("Alice", "B.Tech CS");
    unique_ptr<Document> reportPrototype = make_unique<Report>("Q1 Summary", "Profits up 30%");

    // Clone from prototype
    auto resume1 = resumePrototype->clone();
    auto report1 = reportPrototype->clone();

    // Display
    resume1->show();
    report1->show();

    return 0;
}
