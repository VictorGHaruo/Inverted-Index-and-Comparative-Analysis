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
        if(node) {
            return (node->left->height) - (node->right->height);
        } else { 
            return 0;
        }
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

        computeHeight(root);
        computeHeight(newRoot);

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

        computeHeight(root);
        computeHeight(newRoot);

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

    Node* balance(Node* root) {
        int fb = BalancingFactor(root);

        //Left rotation
        if(fb < 1 && BalancingFactor(root->right) <= 0) {
            root = rotateLeft(root);
        //Right rotation
        } else if(fb > 1 && BalancingFactor(root->left) >= 0) {
            root = rotateRight(root);
        } else if(fb > 1 && BalancingFactor(root->left) < 0) {
            root = rotateLeftRight(root);
        } else if(fb < 1 && BalancingFactor(root->right) > 0) {
            root = rotateRightLeft(root);
        }

        return root;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult searchNode = search(tree, word);

        if(searchNode.found == 1){//The word is already in the tree
            
            //To avoid repeating document IDs when adding words
            int n = searchNode.resultedNode->documentIds.size();
            bool exists = false;
            for (int i = 0; i < n; i++){
                if(searchNode.resultedNode->documentIds[i] == documentId){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                searchNode.resultedNode->documentIds.push_back(documentId);
            }
        }
        else{ //The word isn't in the tree
            vector<int> documentID = {documentID};
            Node *node = createNode(word, documentID, searchNode.parent);

            if(searchNode.parent == nullptr){ //The root is a nullptr
                tree->root = node;
            } 
            else if(word < searchNode.parent->word){ // Determine which side to place the word on
                tree->root->left = node;
            }
            else {
                searchNode.parent->right = node;
            }
        }
        auto end = high_resolution_clock::now(); //Ends clock

        //Convert the auto-typed variable to double, representing milliseconds
        auto duration = end - start;
        chrono::duration<double, milli> duration_ms = duration;
        double time = duration_ms.count();

        InsertResult result;

        // + 1 comes drom the comparson that determines which side the word goes
        result.numComparisons = searchNode.numComparisons + 1;
        result.executionTime = time;

        tree->root = balance(tree->root);

        return result;
    }


    SearchResult search(BinaryTree* tree, const std::string& word){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult result;
        Node *current = tree->root;
        Node *parent = nullptr;
        int numComparisons = 1;

        if(current = nullptr){//Root is a nullptr
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

        if(current = nullptr){
            result.found = 0;
        }
        else{
            result.found = 1;
            result.documentIds = current->documentIds;
        }
        return result;
    }

    void deleteTree(BinaryTree* tree){
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