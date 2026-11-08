#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <iosfwd>
#include <string>
#include <vector>
using namespace std;

struct DepartmentNode {
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> children;

    DepartmentNode(const string& departmentName,
                   DepartmentNode* parentNode = nullptr);
};

class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();

    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    bool isEmpty() const;
    bool addDepartment(const string& departmentName, const string& parentName, string& errorMessage);

    DepartmentNode* getRoot() const;
    DepartmentNode* findDepartment(const string& name) const;

    void displayDepartmentSearch(const string& name, ostream& output) const;
    void displayHierarchy(ostream& output) const;
    void displayPreorder(ostream& output) const;
    void loadFromFile(const string& filename);

private:
    DepartmentNode* root;
    DepartmentNode* findDepartmentRecursive(DepartmentNode* node, const string& name) const;

    void destroySubtree(DepartmentNode* node);
    string trim(const string& value) const;
    string normalizeName(const string& value) const;
    vector<string> splitFields(const string& line);
    int calculateDepth(const DepartmentNode* node) const;
    void displayHierarchyRecursive(DepartmentNode* node, int depth, ostream& output) const;
    void preorderRecursive(DepartmentNode* node, vector<string>& result) const;
};
#endif
