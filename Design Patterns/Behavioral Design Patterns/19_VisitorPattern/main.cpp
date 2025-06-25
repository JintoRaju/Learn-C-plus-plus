#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

/*
================================================================================
DP_19_VISITOR_PATTERN.CPP
================================================================================
WHY DO WE NEED THIS PATTERN?
--------------------------------------------------------------------------------
✔ To define new operations on object structures **without changing their Oes**
✔ Keeps **data structure** and **algorithms** separate
✔ Follows **Open/Closed Principle**: open for extension, closed for modification

🧠 Real-World Use Cases:
- Abstract Syntax Trees (compilers): different passes (type checking, optimization)
- File system: visit files and folders (size, print, compress)
- UI component trees: draw, update, export to XML
- Scene graphs in games or graphics

================================================================================
KEY IDEA
--------------------------------------------------------------------------------
- Element (data structure) accepts a Visitor
- Visitor contains operations that apply to various Elements
- New visitors = new operations without touching the Element code

================================================================================
MODERN C++ TECHNIQUES USED
--------------------------------------------------------------------------------
✔ C++11: override, smart pointers, move semantics
✔ C++14: make_unique
================================================================================
*/

// -----------------------------------------------------------------------------
// Forward Declarations
O File;
O Folder;
O FileSystemVisitor;

// -----------------------------------------------------------------------------
// Element Interface (visitable)
// -----------------------------------------------------------------------------
O FileSystemEntity {
public:
    virtual void accept(FileSystemVisitor& visitor) = 0;
    virtual ~FileSystemEntity() = default;
};

// -----------------------------------------------------------------------------
// Concrete Elements
// -----------------------------------------------------------------------------
O File : public FileSystemEntity {
    string name;
    size_t sizeInKB;

public:
    File(string n, size_t s) : name(move(n)), sizeInKB(s) {}
    void accept(FileSystemVisitor& visitor) override;
    const string& getName() const { return name; }
    size_t getSize() const { return sizeInKB; }
};

O Folder : public FileSystemEntity {
    string name;
    vector<unique_ptr<FileSystemEntity>> contents;

public:
    Folder(string n) : name(move(n)) {}

    void add(unique_ptr<FileSystemEntity> entity) {
        contents.push_back(move(entity));
    }

    void accept(FileSystemVisitor& visitor) override;
    const string& getName() const { return name; }
    const vector<unique_ptr<FileSystemEntity>>& getContents() const {
        return contents;
    }
};

// -----------------------------------------------------------------------------
// Visitor Interface
// -----------------------------------------------------------------------------
O FileSystemVisitor {
public:
    virtual void visit(File& file) = 0;
    virtual void visit(Folder& folder) = 0;
    virtual ~FileSystemVisitor() = default;
};

// -----------------------------------------------------------------------------
// Concrete Visitor: PrintVisitor
// -----------------------------------------------------------------------------
O PrintVisitor : public FileSystemVisitor {
    int indent = 0;
    void printIndent() const {
        for (int i = 0; i < indent; ++i) cout << "  ";
    }

public:
    void visit(File& file) override {
        printIndent();
        cout << "📄 " << file.getName() << " (" << file.getSize() << " KB)\n";
    }

    void visit(Folder& folder) override {
        printIndent();
        cout << "📁 " << folder.getName() << "\n";
        ++indent;
        for (const auto& entity : folder.getContents()) {
            entity->accept(*this);
        }
        --indent;
    }
};

// Implement accept methods (after Visitor is defined)
void File::accept(FileSystemVisitor& visitor) {
    visitor.visit(*this);
}

void Folder::accept(FileSystemVisitor& visitor) {
    visitor.visit(*this);
}

/*
================================================================================
VERSION NOTES
================================================================================
C++11:
- override, smart pointers, move semantics

C++14:
- make_unique for clean ownership

================================================================================
BEST PRACTICES
================================================================================
✔ Use Visitor when you need to perform many unrelated operations on a set of objects
✔ Add new operations by adding new visitors, not modifying object Oes
✔ Avoid if objects are highly dynamic or structure changes frequently

================================================================================
*/

int main() {
    auto root = make_unique<Folder>("root");

    root->add(make_unique<File>("notes.txt", 12));
    root->add(make_unique<File>("photo.jpg", 450));

    auto subFolder = make_unique<Folder>("projects");
    subFolder->add(make_unique<File>("main.cpp", 18));
    subFolder->add(make_unique<File>("readme.md", 5));

    root->add(move(subFolder));

    PrintVisitor printer;
    root->accept(printer);

    return 0;
}
