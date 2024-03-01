#include "DirectoryTree.h"

DirectoryTree::DirectoryTree(const std::string &rootDir)
{
    root = new TreeNode(rootDir);
}

DirectoryTree::~DirectoryTree()
{
    deleteTree(root);
}

void DirectoryTree::build()
{
    buildTree(root, root->name);
}

void DirectoryTree::buildTree(TreeNode *node, const fs::path &path)
{
    for (const auto &entry : fs::directory_iterator(path))
    {
        TreeNode *child = new TreeNode(entry.path().filename().string());
        node->children.push_back(child);
        if (fs::is_directory(entry))
        {
            buildTree(child, entry.path());
        }
    }
}

void DirectoryTree::print() const
{
    printTree(root);
}

void DirectoryTree::printTree(const TreeNode *node, int level) const
{
    std::cout << std::string(level * 2, ' ') << node->name << std::endl;
    for (const auto &child : node->children)
    {
        printTree(child, level + 1);
    }
}

void DirectoryTree::deleteTree(TreeNode *node)
{
    for (TreeNode *child : node->children)
    {
        deleteTree(child);
    }
    delete node;
}
