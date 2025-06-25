#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_09_COMPOSITE_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To treat individual objects and compositions (trees) of objects uniformly.
O It simplifies client code by letting it handle simple and complex objects the same way.

O Real-World Use Cases:
- GUI: Window → Panel → Button, Label, etc.
- File systems: Folder → Files, Subfolders
- Organization hierarchy: Manager → Employees, Teams

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Define a base component interface.
- Leaf classes implement basic behavior.
- Composite class holds children and implements recursive operations.

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, smart pointers, range-based for
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Component Interface
// -----------------------------------------------------------------------------
class Graphic {
public:
    virtual void draw() const = 0;
    virtual ~Graphic() = default;
};

// -----------------------------------------------------------------------------
// Leaf Node
// -----------------------------------------------------------------------------
class Circle : public Graphic {
public:
    void draw() const override {
        cout << "Drawing Circle\n";
    }
};

class Square : public Graphic {
public:
    void draw() const override {
        cout << "Drawing Square\n";
    }
};

// -----------------------------------------------------------------------------
// Composite Node
// -----------------------------------------------------------------------------
class GraphicGroup : public Graphic {
private:
    vector<unique_ptr<Graphic>> children;

public:
    void add(unique_ptr<Graphic> g) {
        children.push_back(move(g));
    }

    void draw() const override {
        cout << "Drawing Group:\n";
        for (const auto& child : children) {
            child->draw();
        }
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Smart pointers (unique_ptr), override keyword
- range-based for loop

C++14:
- make_unique for easier memory handling

================================================================================
BEST PRACTICES
================================================================================
O Use Composite to handle tree-like structures
O Don’t distinguish between leaf and composite in client code
O Add operations at Component level to apply recursively
O Watch out for recursive deletes/memory if not using smart pointers

================================================================================
*/

int main() {
    auto root = make_unique<GraphicGroup>();

    root->add(make_unique<Circle>());
    root->add(make_unique<Square>());

    auto subGroup = make_unique<GraphicGroup>();
    subGroup->add(make_unique<Circle>());
    subGroup->add(make_unique<Circle>());

    root->add(move(subGroup));

    root->draw();

    return 0;
}
