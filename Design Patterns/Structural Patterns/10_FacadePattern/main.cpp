#include <iostream>
#include <string>
using namespace std;

/*
================================================================================
DP_10_FACADE_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To hide complexity from the client and provide a unified interface.
O Simplifies interaction with a complex subsystem.
O Reduces coupling between client and subsystem.

O Real-World Use Cases:
- Media player: one button to play, internally opens file, decodes, syncs audio
- Computer startup: press power → CPU, memory, disk, and OS boot
- Banking: simple API → validate, deduct, notify, update logs

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- A facade class delegates tasks to several components behind the scenes.
- The client only deals with the facade, not the internal system.

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: constructor delegation, defaulted destructors
O C++14/17: Nothing fancy here, but you could enhance the facade interface
================================================================================
*/

// -----------------------------------------------------------------------------
// Subsystems (Complex Internals)
// -----------------------------------------------------------------------------
class CPU {
public:
    void freeze() { cout << "[CPU] Freezing CPU\n"; }
    void jump(long position) { cout << "[CPU] Jumping to address " << position << "\n"; }
    void execute() { cout << "[CPU] Executing instructions\n"; }
};

class Memory {
public:
    void load(long position, const string& data) {
        cout << "[Memory] Loading '" << data << "' into address " << position << "\n";
    }
};

class HardDrive {
public:
    string read(long lba, int size) {
        cout << "[HardDrive] Reading data from sector " << lba << "\n";
        return "OS_BOOT_CODE";
    }
};

// -----------------------------------------------------------------------------
// Facade
// -----------------------------------------------------------------------------
class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    HardDrive hd;

public:
    void start() {
        cout << "[Facade] Starting computer...\n";
        cpu.freeze();
        string bootCode = hd.read(0, 512);
        memory.load(0, bootCode);
        cpu.jump(0);
        cpu.execute();
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- Delegated functions, scoped construction
- No smart pointers needed in this pattern typically

================================================================================
BEST PRACTICES
================================================================================
O Use Facade to provide a clean and simple API to complex systems
O Clients should NOT access subsystem objects directly if avoidable
O Facade promotes low coupling and high cohesion
O It does not prevent access to subsystem if needed — just simplifies

================================================================================
*/

int main() {
    ComputerFacade myComputer;
    myComputer.start();
    return 0;
}
