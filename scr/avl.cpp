#include <iostream>
#include <vector>
#include <string> 
#include <algorithm> 
#include "avl.h"    
#include "tree_utils.h" 
#include <chrono>
using namespace std;
using namespace AVL;
using namespace std::chrono;

namespace AVL {
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree();
        tree->root = nullptr;
        tree->NIL = nullptr; 
        return tree;
    }

    int getHeight(Node* n) {
        return n == nullptr ? -1 : n->height;
    }

    void computeHeight2(Node* node) {
        if (node == nullptr) {
            return; 
        }
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    int BalancingFactor(Node* node) {
        if (node == nullptr) {
            return 0; 
        }
        
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateLeft(Node* root) {
        Node* newRoot = root->right;
        Node* leftSubtree = newRoot->left;

        // First conect the newRoot on the root place
        if(root->parent == nullptr) {
            // root is the tree root
        } else if(root == root->parent->left) {
            root->parent->left = newRoot;
        } else {
            root->parent->right = newRoot;
        }
        newRoot->parent = root->parent;

        // Now rearrange the children
        newRoot->left = root;
        root->parent = newRoot;

        root->right = leftSubtree;
        if (leftSubtree != nullptr) {
            leftSubtree->parent = root;
        }

        computeHeight2(root);
        computeHeight2(newRoot);

        return newRoot;
    }

    Node* rotateRight(Node* root) {
        Node* newRoot = root->left;
        Node* rightSubtree = newRoot->right;

        // Firs conect the newroot on the root place
        if (root->parent == nullptr) {
        // root is the root tree
        } else if(root == root->parent->left) {
            root->parent->left = newRoot;
        } else {
            root->parent->right = newRoot;
        }
        newRoot->parent = root->parent;

        // Now rearrange the children
        newRoot->right = root;
        root->parent = newRoot;

        root->left = rightSubtree;
        if(rightSubtree != nullptr) {
            rightSubtree->parent = root;
        }

        computeHeight2(root);
        computeHeight2(newRoot);

        return newRoot;
    }

    Node* rotateRightLeft(Node* root) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }    

    Node* rotateLeftRight(Node* root) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    Node* balance(Node* node_to_balance) {
        
        if(node_to_balance == nullptr){
            return nullptr;
        }
        
        computeHeight2(node_to_balance);
        int fb = BalancingFactor(node_to_balance);

        //Left rotation
        if(fb > 1) {
            if(BalancingFactor(node_to_balance->left) >= 0) {
                return rotateRight(node_to_balance);
            } else {
                return rotateLeftRight(node_to_balance);
            }
        }
        else if (fb < -1) {
            if (BalancingFactor(node_to_balance->right) <= 0) {
                return rotateLeft(node_to_balance);
            } else {
                return rotateRightLeft(node_to_balance);
            }
        }

        return node_to_balance;
    }

    void rebalancePathToRoot(BinaryTree* tree, Node* starting_node) {
        Node* current_ancestor = starting_node; // Start from the parent of the inserted node

        while (current_ancestor != nullptr) {
            Node* original_ancestor_at_this_level = current_ancestor;
            Node* parent_of_current_ancestor = current_ancestor->parent;
            // balance() calls computeHeight internally and returns the new root of the subtree
            Node* new_subtree_root = balance(current_ancestor);
            // Reconnect the (possibly new) root of the subtree to its parent
            if (parent_of_current_ancestor == nullptr) {
                tree->root = new_subtree_root;
            } else {
                if (parent_of_current_ancestor->left == original_ancestor_at_this_level) {
                    parent_of_current_ancestor->left = new_subtree_root;
                } else {
                    parent_of_current_ancestor->right = new_subtree_root;
                }
            }
            current_ancestor = parent_of_current_ancestor; // Move to the next ancestor
        }
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto start = std::chrono::high_resolution_clock::now();
        SearchResult search_result = search(tree, word);

        if (search_result.found == 1) { 
            if (search_result.resultedNode != nullptr) {
                bool exists = false;
                for (int current_doc_id : search_result.resultedNode->documentIds) {
                    if (current_doc_id == documentId) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    search_result.resultedNode->documentIds.push_back(documentId);
                }
            }
        } else {
            std::vector<int> initial_doc_ids = {documentId};
            Node *new_node = createNode(word, initial_doc_ids, search_result.parent);

            if (search_result.parent == nullptr) { 
                tree->root = new_node;
            } else {
                if (word < search_result.parent->word) {
                    search_result.parent->left = new_node;
                } else {
                    search_result.parent->right = new_node;
                }
            }

            rebalancePathToRoot(tree, search_result.parent);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        std::chrono::duration<double, std::milli> duration_ms = duration; 
        double time = duration_ms.count();

        InsertResult result;
        result.numComparisons = search_result.numComparisons; 

        if (search_result.found == 0 && tree->root != nullptr) {
            result.numComparisons = search_result.numComparisons +1;
        } else {
            result.numComparisons = search_result.numComparisons;
        }

        result.executionTime = time;

        return result;
    }

    SearchResult search(BinaryTree* tree, const std::string& word){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult result;
        Node *current = tree->root;
        Node *parent = nullptr;
        int numComparisons = 1;

        if(current == nullptr){//Root is a nullptr
            result.parent = nullptr;
            result.found = 0;
            result.numComparisons = numComparisons;
            auto end = high_resolution_clock::now(); //Ends clock

            //Convert the auto-typed variable to double, representing milliseconds
            auto duration = end - start;
            chrono::duration<double, milli> duration_ms = duration;
            double time = duration_ms.count();

            result.executionTime = time;
            return result;
        }

        while(current != nullptr && current->word.compare(word) != 0) {
            numComparisons++;
            parent = current;
            if(current->word.compare(word) > 0) {//Current is "bigger" than word
                current = current->left;
            }
            else{ //Current is "smaller" than word
                current = current->right;
            }
        }
        auto end = high_resolution_clock::now(); //Ends clock

        //Convert the auto-typed to double, representing milliseconds
        auto duration = end - start;
        chrono::duration<double, milli> duration_ms = duration;
        double time = duration_ms.count();

        result.numComparisons = numComparisons;
        result.executionTime = time;
        result.resultedNode = current;
        result.parent = parent;

        if(current == nullptr){
            result.found = 0;
        }
        else{
            result.found = 1;
            result.documentIds = current->documentIds;
        }
        return result;
    }

    void deleteTree(BinaryTree* tree) {
        if (tree == nullptr) return; 
        deleteTreeRecursive(tree->root);
        delete tree;

    }

    void deleteTreeRecursive(Node* node) { 
        if (node == nullptr) {
            return;
        }


        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);

        delete node;
    }
}
