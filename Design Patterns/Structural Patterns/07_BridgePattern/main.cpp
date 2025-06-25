#include <iostream>
#include <memory>
using namespace std;

/*
================================================================================
DP_07_BRIDGE_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O When we want to separate abstraction from implementation.
O Allows you to vary abstraction and implementation independently.
O Solves the problem of class explosion caused by too many subclasses.

O Real-World Use Cases:
- GUI toolkit: Different buttons for Windows/Linux
- Graphics API: Draw shapes using OpenGL/DirectX
- Remote control: Same interface, different devices (TV, Radio)

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Split abstraction (high-level control) from implementation (low-level logic)
- Both hierarchies evolve independently

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: override, smart pointers
O C++14+: make_unique
O C++20: consteval/designated initializers (not needed here)
================================================================================
*/

// -----------------------------------------------------------------------------
// Implementation hierarchy (Device side)
// -----------------------------------------------------------------------------
class DrawingAPI {
public:
    virtual void drawCircle(float x, float y, float radius) const = 0;
    virtual ~DrawingAPI() = default;
};

class OpenGLRenderer : public DrawingAPI {
public:
    void drawCircle(float x, float y, float radius) const override {
        cout << "[OpenGL] Drawing Circle at (" << x << "," << y << ") with radius " << radius << "\n";
    }
};

class DirectXRenderer : public DrawingAPI {
public:
    void drawCircle(float x, float y, float radius) const override {
        cout << "[DirectX] Drawing Circle at (" << x << "," << y << ") with radius " << radius << "\n";
    }
};

// -----------------------------------------------------------------------------
// Abstraction hierarchy (Shape side)
// -----------------------------------------------------------------------------
class Shape {
protected:
    shared_ptr<DrawingAPI> drawingAPI;

public:
    Shape(shared_ptr<DrawingAPI> api) : drawingAPI(api) {}
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    float x, y, radius;

public:
    Circle(float x_, float y_, float r_, shared_ptr<DrawingAPI> api)
        : Shape(api), x(x_), y(y_), radius(r_) {}

    void draw() const override {
        drawingAPI->drawCircle(x, y, radius);
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Shared ownership via shared_ptr
- override and =default

C++14:
- make_shared / make_unique

================================================================================
BEST PRACTICES
================================================================================
O Use Bridge when both abstraction and implementation may change independently.
O Avoid deep inheritance trees — use composition instead.
O Promotes separation of concerns.
O Great for cross-platform or multi-rendering strategies.

================================================================================
*/

int main() {
    // Use OpenGL Renderer
    shared_ptr<DrawingAPI> opengl = make_shared<OpenGLRenderer>();
    Circle circle1(5, 10, 3, opengl);
    circle1.draw();

    // Use DirectX Renderer
    shared_ptr<DrawingAPI> directx = make_shared<DirectXRenderer>();
    Circle circle2(15, 20, 7, directx);
    circle2.draw();

    return 0;
}
