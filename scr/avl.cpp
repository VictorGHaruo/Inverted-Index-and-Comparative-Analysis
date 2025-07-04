#include <iostream>
#include <vector>
#include "avl.h"
#include "tree_utils.h"
#include <chrono>
using namespace std;
using namespace AVL;
using namespace std::chrono;

namespace AVL{
    BinaryTree* create(){
        BinaryTree* tree = new BinaryTree();
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }

    int BalancingFactor(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right) ;
    }

    Node* rotateLeft(Node* root) {
        if (root == nullptr || root->right == nullptr) {
            return root; // Cannot rotate
        }

        Node* newRoot = root->right;
        Node* leftSubtree = newRoot->left;
        Node* oldParent = root->parent;

        // Performs the rotation
        newRoot->left = root;
        root->parent = newRoot;

        root->right = leftSubtree;
        if (leftSubtree != nullptr) {
            leftSubtree->parent = root;
        }

        // Reconnects the rotated subtree to the rest of the tree
        newRoot->parent = oldParent;
        if (oldParent != nullptr) {
            if (oldParent->left == root) {
                oldParent->left = newRoot;
            } else {
                oldParent->right = newRoot;
            }
        }

        // Updates heights (order is important: child first, then parent)
        computeHeight(root);
        computeHeight(newRoot);
        return newRoot; // Returns the new root of the subtree
    }

    Node* rotateRight(Node* root) {
        if (root == nullptr || root->left == nullptr) {
            return root; // Cannot rotate
        }
        
        Node* newRoot = root->left;
        Node* rightSubtree = newRoot->right;
        Node* oldParent = root->parent;

        // Perfoms the rotation
        newRoot->right = root;
        root->parent = newRoot;

        root->left = rightSubtree;
        if (rightSubtree != nullptr) {
            rightSubtree->parent = root;
        }

        // Reconnects the rotated subtree to the rest of the tree
        newRoot->parent = oldParent;
        if (oldParent != nullptr) {
            if (oldParent->left == root) {
                oldParent->left = newRoot;
            } else {
                oldParent->right = newRoot;
            }
        }

        // Updates heights (order is important: child first, then parent)
        computeHeight(root);
        computeHeight(newRoot);
        return newRoot; // Return the new root of the subtree
    }

    Node* rotateRightLeft(Node* root) {
        Node* newRight = rotateRight(root->right);
        root->right = newRight;
        if (newRight != nullptr) {
            newRight->parent = root;
        }
        return rotateLeft(root);
    }

    Node* rotateLeftRight(Node* root) {
        Node* newLeft = rotateLeft(root->left);
        root->left = newLeft;
        if (newLeft != nullptr) {
            newLeft->parent = root;
        }
        return rotateRight(root);
    }

    // An important function to keep the tree balanced
    Node* balance(Node* node_to_balance) {
        
        if(node_to_balance == nullptr){
            return nullptr;
        }
        int fb = BalancingFactor(node_to_balance);
        // Left rotation
        if(fb > 1) {
            if(BalancingFactor(node_to_balance->left) >= 0) {
                return rotateRight(node_to_balance);
            } else {
                return rotateLeftRight(node_to_balance);
            }
        }
        // Right rotation
        else if (fb < -1) {
            if (BalancingFactor(node_to_balance->right) <= 0) {
                return rotateLeft(node_to_balance);
            } else {
                return rotateRightLeft(node_to_balance);
            }
        }

        return node_to_balance;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        auto start = high_resolution_clock::now(); // Starts clock
        SearchResult searchNode = search(tree, word);
        if(searchNode.found == 1){// The word is already in the tree
            
            // To avoid repeating document IDs when adding words
            int n = searchNode.resultedNode->documentIds.size();
            bool exists = false;
            // In the massive insert on main, it's just important the last ID (fewer operations)
            for (int i = n-1; i >= 0; i--){  
                if(searchNode.resultedNode->documentIds[i] == documentId){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                searchNode.resultedNode->documentIds.push_back(documentId);
            }
        }else{ // The word isn't in the tree
            vector<int> documentID = {documentId};
            Node *node = createNode(word, documentID, searchNode.parent);

            if(searchNode.parent == nullptr){ // The root is a nullptr
                tree->root = node;
            } 
            else if(word < searchNode.parent->word){ // Determine which side to place the word on
                searchNode.parent->left = node;
            }
            else {
                searchNode.parent->right = node;
            }

            // Balancing the tree
            Node* ancestral = searchNode.parent;    

            while (ancestral != nullptr){
                computeHeight(ancestral); // Updating the height of ancestor nodes
                if (abs(BalancingFactor(ancestral)) > 1){
                    searchNode.numComparisons++;
                    Node* parent = ancestral->parent;
                    Node* new_subtree_root = balance(ancestral);

                    if (parent == nullptr) 
                        tree->root = new_subtree_root;

                    break;
                }
                ancestral = ancestral->parent;
                searchNode.numComparisons++;
            }
        }
        auto end = high_resolution_clock::now(); // Ends clock
        // Convert the auto-typed variable to double, representing milliseconds
        auto duration = end - start;
        chrono::duration<double, milli> duration_ms = duration;
        double time = duration_ms.count();

        InsertResult result;

        result.word = word;
        if(searchNode.found==1){
            result.isNew = false;
        } else{
            result.isNew = true;
        }

        // +1 comes drom the comparson that determines which side the word goes
        result.numComparisons = searchNode.numComparisons + 1;
        result.executionTime = time;
        if(searchNode.found == 0){
            result.maxHeight = getHeight(tree->root); // Already campute this
            result.minHeight = getMinOrMaxPath(tree->root, false);
        } else{
            result.maxHeight = 0;
            result.minHeight = 0;            
        }

        return result;
    }

    SearchResult search(BinaryTree* tree, const std::string& word){
        auto start = high_resolution_clock::now(); // Starts clock
        SearchResult result;
        Node *current = tree->root;
        Node *parent = nullptr;
        int numComparisons = 1;

        if(current == nullptr){// Root is a nullptr
            result.parent = nullptr;
            result.found = 0;
            result.numComparisons = numComparisons;
            auto end = high_resolution_clock::now(); // Ends clock

            // Convert the auto-typed variable to double, representing milliseconds
            auto duration = end - start;
            chrono::duration<double, milli> duration_ms = duration;
            double time = duration_ms.count();

            result.executionTime = time;
            return result;
        }

        while(current != nullptr && current->word.compare(word) != 0) {
            numComparisons++;
            parent = current;
            if(current->word.compare(word) > 0) {// Current is "bigger" than word
                current = current->left;
            }
            else{// Current is "smaller" than word
                current = current->right;
            }
        }
        auto end = high_resolution_clock::now(); // Ends clock

        // Convert the auto-typed to double, representing milliseconds
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

    void destroy(BinaryTree* tree){
        deleteTreeRecursive(tree->root);
        delete tree;
        tree = nullptr;
    }

    void deleteTreeRecursive(Node* root) {
        if(root == nullptr){
            return;
        }

        // Delete nodes by DFS
        deleteTreeRecursive(root->left);
        deleteTreeRecursive(root->right);
        
        delete root;
    }
}