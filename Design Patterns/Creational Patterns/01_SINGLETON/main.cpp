#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

/*
================================================================================
DP_01_SINGLETON.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O Sometimes, we need only ONE instance of a class shared across the system.
   O Examples: Logger, Configuration Manager, Thread Pool, DB Connection Pool

O Singleton ensures:
   - A class has only one instance
   - Provides a global access point to it

================================================================================
SIMPLE EXAMPLE — LOGGER SINGLETON
================================================================================
We'll create a Logger class that:
- Restricts instantiation (private constructor)
- Provides static access to the instance
- Supports thread-safe lazy initialization

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: Magic statics (thread-safe), deleted copy/assign
O C++14+: unique_ptr for memory management (if needed)
O C++17: Inline static variables (cleaner syntax)
O C++20: consteval, concepts — not directly needed here but style used
================================================================================
*/

class Logger {
private:
    Logger() {
        cout << "[Logger] Instance created\n";
    }

    // Deleted to avoid copies
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance; // Thread-safe since C++11
        return instance;
    }

    void log(const string& message) {
        cout << "[LOG]: " << message << "\n";
    }
};

/*
================================================================================
BEST PRACTICES
================================================================================
O Use local static in getInstance() for lazy loading + thread safety
O Avoid making everything static — break SRP if needed
O For unit tests, Singleton can be problematic — use dependency injection
O For global services (Logger, ConfigManager), Singleton is valid

================================================================================
COMMON PITFALLS
================================================================================
O Making constructor public → multiple instances
O Forgetting to delete copy/assignment
O Making everything static → kills testability/extensibility
O Overusing Singleton → global state misuse (use only when justified)

================================================================================
*/

int main() {
    Logger& logger1 = Logger::getInstance();
    logger1.log("Hello, Singleton!");

    Logger& logger2 = Logger::getInstance();
    logger2.log("Same instance reused!");

    // Output confirms only one instance is created
    return 0;
}
