#ifndef TREE_UTILS_H
#define TREE_UTILS_H

# include <iostream>
# include <vector>
# include <string>


struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // used in AVL
    int isRed;     // used in RBT
};

struct BinaryTree {
    Node* root;
    Node* NIL;  // used in RBT
};

struct InsertResult {
    int numComparisons;
    double executionTime;
    // others possible variables
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
    // others possible variables
    
    //created for BST
    Node* resultedNode;
    Node* parent;
};

Node* createNode(std::string word, std::vector<int> documentsId, Node* parent);

BinaryTree* createTree(Node* root);

int computeDepth(Node* node);

int computeHeight(Node* node);

void printIndex(BinaryTree* tree);

// Auxiliary function
void printIndexAux(Node* root, int &counter);

void printTree(BinaryTree* tree);

// Auxiliary function
void printTreeAux(Node* root, int counter, bool isLast);

// Auxiliary function
void printVector(const std::vector<int> vec);

# endif