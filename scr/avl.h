#include <vector>
#include <iostream>
#include "tree_utils.h"
#ifndef AVL_H
#define AVL_H

using namespace TreeUtils;

namespace AVL{
    BinaryTree* create();
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroy(BinaryTree* tree);
    void deleteTreeRecursive(Node* root);
}    
#endif
    