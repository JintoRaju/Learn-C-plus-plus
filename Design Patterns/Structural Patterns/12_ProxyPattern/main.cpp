#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*
================================================================================
DP_12_PROXY_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
O To control access to an object (e.g., permission, lazy loading, logging).
O Acts as a surrogate for another object — client thinks it's using the real one.
O Useful when real object is expensive to create, or we want to add security/logging.

O Real-World Use Cases:
- Virtual proxy: defer loading of large images/files until needed
- Protection proxy: restrict access (e.g., admin vs user)
- Smart reference: logging, caching, thread-safety
- File system: permission checks before access

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Proxy and RealSubject share the same interface
- Client interacts with the Proxy instead of RealSubject
- Proxy adds control, RealSubject does real work

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
O C++11: smart pointers, override
O C++14+: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Subject Interface
// -----------------------------------------------------------------------------
class Document {
public:
    virtual void display() const = 0;
    virtual ~Document() = default;
};

// -----------------------------------------------------------------------------
// Real Subject — does the real work
// -----------------------------------------------------------------------------
class RealDocument : public Document {
private:
    string filename;

    void loadFromDisk() const {
        cout << "[RealDocument] Loading '" << filename << "' from disk...\n";
    }

public:
    RealDocument(string name) : filename(move(name)) {
        loadFromDisk();  // costly operation at creation
    }

    void display() const override {
        cout << "[RealDocument] Displaying '" << filename << "'\n";
    }
};

// -----------------------------------------------------------------------------
// Proxy — controls access, adds lazy loading
// -----------------------------------------------------------------------------
class DocumentProxy : public Document {
private:
    string filename;
    mutable unique_ptr<RealDocument> realDoc;

public:
    DocumentProxy(string name) : filename(move(name)), realDoc(nullptr) {}

    void display() const override {
        if (!realDoc) {
            cout << "[Proxy] Creating RealDocument lazily...\n";
            realDoc = make_unique<RealDocument>(filename);
        }
        realDoc->display();
    }
};

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- unique_ptr, override, move semantics

C++14:
- make_unique

================================================================================
BEST PRACTICES
================================================================================
O Use Proxy to add access control, lazy loading, logging, or remote access
O Keep Proxy interface identical to real object
O Useful when RealSubject is heavy or security-sensitive
O Client remains unaware of whether it talks to Proxy or RealSubject

================================================================================
*/

int main() {
    unique_ptr<Document> doc = make_unique<DocumentProxy>("ProjectPlan.pdf");

    cout << "[Client] First access:\n";
    doc->display();  // lazy loading happens here

    cout << "\n[Client] Second access:\n";
    doc->display();  // already loaded, no need to reload

    return 0;
}
