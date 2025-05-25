#include <vector>
#include <iostream>
#include "tree_utils.h"
#ifndef BST_H
#define BST_H

namespace BST{
    BinaryTree* create();
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void deleteTree(BinaryTree* tree);
    void deleteTreeRecursive(Node* root);
}    
#endif
    