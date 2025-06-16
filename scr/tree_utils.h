#ifndef TREE_UTILS_H
#define TREE_UTILS_H

# include <iostream>
# include <vector>
#include <fstream>
# include <string>

namespace TreeUtils {

/**
 * @struct Node
 * @brief Structure to represent a node in a binary tree
*/
struct Node {
    std::string word;               // The indexed word
    std::vector<int> documentIds;   // List of document IDs containing this word
    Node* parent;                   // Pointer to parent node
    Node* left;                     // Pointer to left child
    Node* right;                    // Pointer to right child
    int height;                     // Node height (used in AVL)
    int isRed;                      // Color flag (used in RBT)
};

/**
 * @struct BinaryTree
 * @brief Structure to represent a binary tree
*/
struct BinaryTree {
    Node* root;                     // Pointer to the root node
    Node* NIL;                      // used in RBT
};

// To be documented
struct InsertResult {
    int numComparisons;
    double executionTime;
    std::string word;
    bool isNew;
    int maxHeight;
    int minHeight;
    // others possible variables
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
    // others possible variables
    
    //created for insert
    Node* resultedNode;
    Node* parent;
};

/**
 * @brief Creates a new tree node
 * 
 * @param word The word to be stored in the node
 * @param documentsId Vector of document IDs where the word appears
 * @param parent The parent of the node 
 * @return Node* 
*/
Node* createNode(std::string word, std::vector<int> documentsId, Node* parent);

/**
 * @brief Computes the depth of a node
 * 
 * @param node Pointer to the node whose depth is to be calculated
 * @return int Depth of the node (0 for root, -1 for nullptr node)
 */
int computeDepth(Node* node);

/**  
* @brief Gets the height of a node
*
* @param node Pointer to the node whose depth is to be calculated
* @return int Height of the node (-1 for nullptr node)
*/
int getHeight(Node* node);

/**
 * @brief Computes the height of a node
 * 
 * @param node Pointer to the node whose height is to be calculated
 */
void computeHeight(Node* node);

/**
 * @brief Prints the inverted index in a formatted list
 * @param tree Pointer to the binary tree containing the index
 * @details Displays each word with its corresponding document IDs.
 *          Format: "1. word: doc1, doc2, doc3"
 */
void printIndex(BinaryTree* tree);

/**
 * @brief Prints the tree structure in a visual hierarchical format
 * @param tree Pointer to the binary tree to be displayed
*/
void printTree(BinaryTree* tree);

/**
 * @brief Save the print of the tree structure in a visual hierarchical format
 * @param tree Pointer to the binary tree to be displayed
 * @param filename The path of .txt
*/
void savePrintTree(BinaryTree* tree, std::string filename);

/**
 * @brief This function returns the heigth of the shortest or of the longest path
 * @param node Pointer to the node (root) whose height's path is going to be calculated
 * @param type Can be "max" or "min", only!
 * @return The height of the path or -1 to wrong uses.
*/
int getMinOrMaxPath(Node* node, std::string type);

}

# endif