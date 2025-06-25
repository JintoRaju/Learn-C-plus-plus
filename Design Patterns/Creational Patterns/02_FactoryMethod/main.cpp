#include <iostream>
#include <memory>
using namespace std;

/*
================================================================================
DP_02_FACTORY_METHOD.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O When object creation logic should be abstracted away from the user
O Avoids tight coupling with specific classes
O Allows extending new object types without modifying existing code

USE CASE EXAMPLES:
O GUI library with different buttons for Windows/Linux/Mac
O Game engine where EnemyFactory spawns different types of enemies
O Shape/Document parsers, Notification system (SMS/Email)

================================================================================
CORE IDEA
--------------------------------------------------------------------------------
- Define a common interface (e.g., Shape)
- Let subclasses decide which class to instantiate
- Use virtual method `create()` to hide creation logic

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, unique_ptr
O C++14: make_unique
O C++17: if-init, structured bindings (optional)
================================================================================
*/

// -----------------------------------------------------------------------------
// Step 1: Product Interface
// -----------------------------------------------------------------------------
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// -----------------------------------------------------------------------------
// Step 2: Concrete Products
// -----------------------------------------------------------------------------
class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Circle\n";
    }
};

class Square : public Shape {
public:
    void draw() const override {
        cout << "Drawing Square\n";
    }
};

// -----------------------------------------------------------------------------
// Step 3: Creator Interface — The Factory Base
// -----------------------------------------------------------------------------
class ShapeFactory {
public:
    virtual unique_ptr<Shape> createShape() const = 0;
    virtual ~ShapeFactory() = default;
};

// -----------------------------------------------------------------------------
// Step 4: Concrete Factories
// -----------------------------------------------------------------------------
class CircleFactory : public ShapeFactory {
public:
    unique_ptr<Shape> createShape() const override {
        return make_unique<Circle>();
    }
};

class SquareFactory : public ShapeFactory {
public:
    unique_ptr<Shape> createShape() const override {
        return make_unique<Square>();
    }
};

/*
================================================================================
BEST PRACTICES
================================================================================
O Use interfaces and virtual methods for abstraction
O Use `unique_ptr` for ownership and safety
O Avoid raw `new` — prefer `make_unique` / `make_shared`
O Extend with new product types without changing existing factory users

================================================================================
C++ VERSION NOTES
================================================================================
C++11:
- override keyword
- unique_ptr for smart ownership

C++14:
- make_unique for cleaner construction

C++20:
- With concepts, factory signatures can be restricted (not shown here)

================================================================================
*/

int main() {
    unique_ptr<ShapeFactory> factory;

    factory = make_unique<CircleFactory>();
    auto shape1 = factory->createShape();
    shape1->draw();

    factory = make_unique<SquareFactory>();
    auto shape2 = factory->createShape();
    shape2->draw();

    return 0;
}
