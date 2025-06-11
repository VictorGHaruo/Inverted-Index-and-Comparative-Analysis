#include <vector>
#include <iostream>
#include "tree_utils.h"
#ifndef RBT_H
#define RBT_H

using namespace TreeUtils;

namespace RBT{
    BinaryTree* create();
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroy(BinaryTree* tree);
    void deleteTreeRecursive(Node* root);
}    
#endif