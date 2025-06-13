#include <vector>
#include <iostream>
#include "tree_utils.h"
#ifndef BST_H
#define BST_H

/**
 * @namespace TreeUtils
 * @brief A set of useful functions for manipulating Tree data structures 
 */
using namespace TreeUtils;

/**
 * @namespace AVL
 * @brief A set of useful functions for manipulating an BST tree type
 */
namespace BST{

    /**
     * @brief A function for creating a Binary tree, taking care of the pointers
     * @return A pointer to Binary Tree root
     */
    BinaryTree* create();

    /**
     * @brief A function for insert node in the Binary tree. Taking care with the binary structure
     * @param BinaryTree Pointer to the BinaryTree to be displayed
     * @param word The word to be searched for and possibly added to the Binary Tree
     * @param documentId The Id that identify which document the word is in
     * @details There are important differences in insertion compared to other types of Trees (AVL, RBT)
     * @return A structure of type InsertResult, with parameters like: found, documentIds, executionTime, numComparisons. 
     * There are too Pointers like: resultedNode, parent
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief A function for search a word in Binary Tree
     * @param BinaryTree Pointer to the BinaryTree to be displayed
     * @param word The word to be searched 
     * @details There aren't difference between this function with the function in AVL and RBT
     * @return A structure of type InsertResult, with parameters like: found, documentIds, executionTime, numComparisons.
     * There are too Pointers like: resultedNode, parent
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief A function to destroy the BinaryTree. Uses the recursive logic of the deleteTreeRecursive function
     * @param BinaryTree Pointer to the BinaryTree to be displayed
     */
    void destroy(BinaryTree* tree);

    /**
     * @brief A function to destroy a Tree. Uses the recursive logic for delete the right and left side (DFS)
     * @param root Pointer to the Node, a node in the BinaryTree to be delete
     */
    void deleteTreeRecursive(Node* root);
}    
#endif
    