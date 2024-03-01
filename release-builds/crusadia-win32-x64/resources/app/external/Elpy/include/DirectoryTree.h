#ifndef DIRECTORYTREE_H
#define DIRECTORYTREE_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

// Namespace alias for convenience
namespace fs = std::filesystem;

// Node structure to represent each directory and file
struct TreeNode
{
    std::string name;                 // Directory or file name
    std::vector<TreeNode *> children; // Children of the directory (subdirectories and files)

    // Constructor
    TreeNode(const std::string &name) : name(name) {}
};

class DirectoryTree
{
private:
    TreeNode *root; // Root of the tree, representing the base directory

    // Helper methods
    void buildTree(TreeNode *node, const fs::path &path);
    void printTree(const TreeNode *node, int level = 0) const;

public:
    DirectoryTree(const std::string &rootDir);
    ~DirectoryTree();

    void build();
    void print() const;

    // Disallow copy and assignment
    DirectoryTree(const DirectoryTree &) = delete;
    DirectoryTree &operator=(const DirectoryTree &) = delete;

    // Helper method to delete tree recursively
    void deleteTree(TreeNode *node);
};

#endif // DIRECTORYTREE_H
