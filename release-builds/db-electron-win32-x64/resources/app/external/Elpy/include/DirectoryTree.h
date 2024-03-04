#ifndef DIRECTORYTREE_H
#define DIRECTORYTREE_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

struct TreeNode
{
    std::string name;
    std::vector<TreeNode *> children;

    TreeNode(const std::string &name) : name(name) {}
};

class DirectoryTree
{
private:
    TreeNode *root;

    void buildTree(TreeNode *node, const fs::path &path);
    void printTree(const TreeNode *node, int level = 0) const;

public:
    DirectoryTree(const std::string &rootDir);
    ~DirectoryTree();

    void build();
    void print() const;

    DirectoryTree(const DirectoryTree &) = delete;
    DirectoryTree &operator=(const DirectoryTree &) = delete;

    void deleteTree(TreeNode *node);
};

#endif
