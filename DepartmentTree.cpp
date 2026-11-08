#include "DepartmentTree.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

DepartmentNode::DepartmentNode(const string& departmentName, DepartmentNode* parentNode) : name(departmentName), parent(parentNode) {}

DepartmentTree::DepartmentTree() : root(nullptr) {}

DepartmentTree::~DepartmentTree() {
    destroySubtree(root);
    root = nullptr;
}

void DepartmentTree::destroySubtree(DepartmentNode* node) {
    if (node == nullptr) return;
    for (DepartmentNode* child : node->children) destroySubtree(child);
    delete node;
}

bool DepartmentTree::isEmpty() const {
    return root == nullptr;
}

DepartmentNode* DepartmentTree::getRoot() const {
    return root;
}

string DepartmentTree::trim(const string& value) const {
    size_t first = 0;
    while (first < value.size() && isspace(static_cast<unsigned char>(value[first]))) ++first;

    size_t last = value.size();
    while (last > first && isspace(static_cast<unsigned char>(value[last - 1]))) --last;

    return value.substr(first, last - first);
}

string DepartmentTree::normalizeName(const string& value) const {
    string normalized = trim(value);
    for (char& character : normalized) {
        character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
    }
    return normalized;
}

vector<string> DepartmentTree::splitFields(const string& line) {
    vector<string> fields;
    stringstream stream(line);
    string field;

    while (getline(stream, field, '|')) fields.push_back(trim(field));
    if (!line.empty() && line.back() == '|') fields.push_back("");
    return fields;
}

DepartmentNode* DepartmentTree::findDepartmentRecursive(
    DepartmentNode* node, const string& name) const {
    if (node == nullptr) return nullptr;
    if (normalizeName(node->name) == normalizeName(name)) return node;

    for (DepartmentNode* child : node->children) {
        DepartmentNode* result = findDepartmentRecursive(child, name);
        if (result != nullptr) return result;
    }
    return nullptr;
}

DepartmentNode* DepartmentTree::findDepartment(const string& name) const {
    return findDepartmentRecursive(root, trim(name));
}

bool DepartmentTree::addDepartment(const string& departmentName, const string& parentName, string& errorMessage) {
    const string cleanName = trim(departmentName);
    const string cleanParent = trim(parentName);

    if (cleanName.empty()) {
        errorMessage = "Department name can't be blank.";
        return false;
    }
    if (findDepartment(cleanName) != nullptr) {
        errorMessage = "A department with that name already exists.";
        return false;
    }

    if (root == nullptr) {
        if (!cleanParent.empty() && normalizeName(cleanParent) != "NONE") {
            errorMessage = "The first department has to be the root and use NONE as its parent.";
            return false;
        }
        root = new DepartmentNode(cleanName);
        errorMessage.clear();
        return true;
    }

    if (cleanParent.empty() || normalizeName(cleanParent) == "NONE") {
        errorMessage = "A parent department is needed because the tree isn't empty.";
        return false;
    }

    DepartmentNode* parentNode = findDepartment(cleanParent);
    if (parentNode == nullptr) {
        errorMessage = "Parent department not found: " + cleanParent;
        return false;
    }

    DepartmentNode* newNode = new DepartmentNode(cleanName, parentNode);
    parentNode->children.push_back(newNode);
    errorMessage.clear();
    return true;
}

int DepartmentTree::calculateDepth(const DepartmentNode* node) const {
    int depth = 0;
    while (node != nullptr && node->parent != nullptr) {
        ++depth;
        node = node->parent;
    }
    return depth;
}

void DepartmentTree::displayDepartmentSearch(const string& name, ostream& output) const {
    const string cleanName = trim(name);
    if (cleanName.empty()) {
        output << "Department name can't be blank.\n";
        return;
    }

    DepartmentNode* department = findDepartment(cleanName);
    if (department == nullptr) {
        output << "Department not found: " << cleanName << '\n';
        return;
    }

    output << "Department: " << department->name << '\n';
    if (department->parent == nullptr) output << "Parent: None\n";
    else output << "Parent: " << department->parent->name << '\n';

    output << "Direct children: " << department->children.size() << '\n';
    output << "Depth: " << calculateDepth(department) << '\n';
}

void DepartmentTree::displayHierarchyRecursive(DepartmentNode* node, int depth, ostream& output) const {
    if (node == nullptr) return;
    for (int i = 0; i < depth; ++i) output << "    ";
    output << node->name << '\n';

    for (DepartmentNode* child : node->children) {
        displayHierarchyRecursive(child, depth + 1, output);
    }
}

void DepartmentTree::displayHierarchy(ostream& output) const {
    if (root == nullptr) {
        output << "No departments are loade.\n";
        return;
    }
    displayHierarchyRecursive(root, 0, output);
}

void DepartmentTree::preorderRecursive(
    DepartmentNode* node, vector<string>& result) const {
    if (node == nullptr) return;
    result.push_back(node->name);
    for (DepartmentNode* child : node->children) preorderRecursive(child, result);
}

void DepartmentTree::displayPreorder(ostream& output) const {
    if (root == nullptr) {
        output << "No departments are loaded.\n";
        return;
    }

    vector<string> result;
    preorderRecursive(root, result);
    output << "Preorder: ";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) output << " -> ";
        output << result[i];
    }
    output << '\n';
}

void DepartmentTree::loadFromFile(const string& filename) {
    destroySubtree(root);
    root = nullptr;

    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Error: couldn't open " << filename << ".\n";
        cout << filename << ": 0 accepted, 0 rejected\n";
        return;
    }

    int accepted = 0, rejected = 0, lineNumber = 0;
    string line;

    while (getline(input, line)) {
        ++lineNumber;
        if (!line.empty() && line.back() == '\r') line.pop_back();

        const string cleanLine = trim(line);
        if (cleanLine.empty() || cleanLine[0] == '#') continue;

        const vector<string> fields = splitFields(cleanLine);
        string reason;

        if (fields.size() != 2) {
            reason = "expected two fields (DepartmentName|ParentName)";
        } else if (fields[0].empty() || fields[1].empty()) {
            reason = "department name and parent name can't be empty";
        } else if (root == nullptr && normalizeName(fields[1]) != "NONE") {
            reason = "the first accepted department has to use NONE as its parent";
        } else if (root != nullptr && normalizeName(fields[1]) == "NONE") {
            reason = "only the root department can have parent NONE";
        } else if (findDepartment(fields[0]) != nullptr) {
            reason = "duplicate department name: " + fields[0];
        } else if (root != nullptr && findDepartment(fields[1]) == nullptr) {
            reason = "unknown parent department: " + fields[1];
        }

        if (!reason.empty()) {
            ++rejected;
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": " << reason << ".\n";
            continue;
        }

        string errorMessage;
        if (addDepartment(fields[0], fields[1], errorMessage)) {
            ++accepted;
        } else {
            ++rejected;
            cout << "Warning: " << filename << ", line " << lineNumber
                 << ": " << errorMessage << '\n';
        }
    }

    cout << filename << ": " << accepted << " accepted, "
         << rejected << " rejected\n";
}
