#include <iostream>
#include <string>
#include <memory>
using namespace std;

/*
================================================================================
DP_04_BUILDER_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O When an object has:
   O Many optional fields
   O Complex construction steps
   O Different configurations from the same data

O Example Use Cases:
- Constructing documents, reports, queries
- Creating different types of cars, robots, or burgers
- Fluent interfaces (e.g., method chaining)

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
Separate construction of an object from its representation
So the same construction process can create different products

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: `unique_ptr`, constructor delegation
O C++14+: `make_unique`
O C++20: `consteval`, named arguments, designated initializers (not covered here)

================================================================================
*/

// -----------------------------------------------------------------------------
// Product: Car
// -----------------------------------------------------------------------------
class Car {
public:
    string engine;
    string transmission;
    string color;

    void show() const {
        cout << "Car built with:\n";
        cout << "  Engine: " << engine << "\n";
        cout << "  Transmission: " << transmission << "\n";
        cout << "  Color: " << color << "\n";
    }
};

// -----------------------------------------------------------------------------
// Abstract Builder
// -----------------------------------------------------------------------------
class CarBuilder {
public:
    virtual CarBuilder& setEngine(const string& type) = 0;
    virtual CarBuilder& setTransmission(const string& type) = 0;
    virtual CarBuilder& setColor(const string& color) = 0;
    virtual unique_ptr<Car> build() = 0;
    virtual ~CarBuilder() = default;
};

// -----------------------------------------------------------------------------
// Concrete Builder (Fluent Interface)
// -----------------------------------------------------------------------------
class SportsCarBuilder : public CarBuilder {
private:
    unique_ptr<Car> car;

public:
    SportsCarBuilder() {
        car = make_unique<Car>();
    }

    CarBuilder& setEngine(const string& type) override {
        car->engine = type;
        return *this;
    }

    CarBuilder& setTransmission(const string& type) override {
        car->transmission = type;
        return *this;
    }

    CarBuilder& setColor(const string& color) override {
        car->color = color;
        return *this;
    }

    unique_ptr<Car> build() override {
        return move(car);
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Added `unique_ptr`, constructor delegation
- Move semantics (std::move)

C++14:
- make_unique used for memory safety

C++20:
- Could use designated initializers (C++20 structs with public fields)
================================================================================
BEST PRACTICES
================================================================================
O Use Builder when constructor has too many optional params
O Fluent interfaces make code more readable and self-documenting
O Decouple the construction logic from representation
O Helps with unit testing by mocking builders
================================================================================
*/

int main() {
    SportsCarBuilder builder;

    unique_ptr<Car> car = builder
        .setEngine("V8 Twin Turbo")
        .setTransmission("7-Speed Dual-Clutch")
        .setColor("Red")
        .build();

    car->show();

    return 0;
}
