#include <iostream>
#include <vector>
#include "rbt.h"
#include "tree_utils.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

namespace RBT {

    BinaryTree* create(){
        BinaryTree* tree = new BinaryTree();
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }

    // Replace a node u with a node v in the tree
    void transplant(BinaryTree* tree, Node* u, Node* v) {
        if (u->parent == nullptr) {
            tree->root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void rotateLeft(BinaryTree* tree, Node* x) {

        Node* y = x->right; 
        
        // Left subtree of y becomes right child of x
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        
        // y takes x's position in the tree
        transplant(tree, x, y);
        
        // x becomes left child of y
        y->left = x;
        x->parent = y;
    }

    void rotateRight(BinaryTree* tree, Node* x) {

        Node* y = x->left; 
        
        // right subtree of y becomes left child of x
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        
        // y takes x's position in the tree 
        transplant(tree, x, y);
        
        // x becomes right child of y
        y->right = x;
        x->parent = y;

    }

    // Adjust the insert to RBT
    int fixInsert(BinaryTree* tree, Node* z){
        int comp = 1;
        if (z == nullptr || z->parent == nullptr) {
            if (tree->root != nullptr) {
                tree->root->isRed = 0;
            }
            return comp;
        }

        while (z->parent != nullptr && z->parent->isRed){
            comp++;
            // Cases in the left
            if (z->parent == z->parent->parent->left){
                Node* y = z->parent->parent->right; // Uncle

                // Case 1: Uncle is red - recolor
                if (y != nullptr && y->isRed){
                    y->parent->isRed = 1;
                    y->isRed = 0;
                    z->parent->isRed = 0;
                    z = z->parent->parent;

                } else { // Uncle is black

                    // Case 2: z is right child 
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(tree, z);
                    }
                    // Case 3: z is left child
                    z->parent->isRed = 0;     
                    z->parent->parent->isRed = 1;    
                    rotateRight(tree, z->parent->parent);

                }
            
            } else { // Cases in the right
                Node* y = z->parent->parent->left; // Uncle
                
                // Case 1: Uncle is red - recolor
                if (y != nullptr && y->isRed) {
                    z->parent->isRed = 0;
                    y->isRed = 0;
                    z->parent->parent->isRed = 1;
                    z = z->parent->parent;
                } else {
                    // Case 2: z is left child 
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(tree, z);
                    }
                    
                    // Case 3: z is right child
                    z->parent->isRed = 0;
                    z->parent->parent->isRed = 1;
                    rotateLeft(tree, z->parent->parent);
                }
            }
                
        }
        tree->root->isRed = 0;
        return comp;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult searchNode = search(tree, word);
        int comp = 0;

        if (searchNode.found == 1){ //The word is already in the tree

            //To avoid repeating document IDs when adding words
            int n = searchNode.resultedNode->documentIds.size();
            bool exists = false;
            // In the massive insert on main, it's just important the last ID (fewer operations)
            for (int i = n-1; i >= 0; i--){ 
                if (searchNode.resultedNode->documentIds[i] == documentId){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                searchNode.resultedNode->documentIds.push_back(documentId); 
            }

        } else { //The word isn't in the tree
            vector<int> documentID = {documentId};
            Node *node = createNode(word, documentID, searchNode.parent);

            if (searchNode.parent == nullptr){ //The root is a nullptr
                tree->root = node;
                node->isRed = 0; // Maybe is not necessary here
            }else if(word < searchNode.parent->word){ // Determine which side to place the word on
                searchNode.parent->left = node;
            }else{
                searchNode.parent->right = node;
            }

            comp += fixInsert(tree, node);
            
        }

        auto end = high_resolution_clock::now(); //Ends clock

        //Convert the auto-typed variable to double, representing milliseconds
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

        // +1 comes from the comparison that determines which side the word goes
        // and plus the comparisons when it's fixing
        result.numComparisons = searchNode.numComparisons + 1 + comp; 
        result.executionTime = time;

        return result;

    }

    SearchResult search(BinaryTree* tree, const std::string& word){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult result;
        Node *current = tree -> root;
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

        while(current != nullptr && current->word.compare(word) != 0){
            numComparisons++;
            parent = current;
            if(current->word.compare(word) > 0){ //Current is "bigger" than word 
                current = current -> left;
            }
            else{ //Current is "smaller" than word
                current = current -> right;
            }
        }
        auto end = high_resolution_clock::now(); //Ends clock

        //Convert the auto-typed variable to double, representing milliseconds
        auto duration = end - start;
        chrono::duration<double, milli> duration_ms = duration;
        double time = duration_ms.count();

        result.numComparisons = numComparisons;
        result.executionTime = time;
        result.resultedNode = current;
        result.parent = parent;
        
        if (current == nullptr){
            result.found = 0;
        }else{
            result.found = 1;
            result.documentIds = current->documentIds;
        }
        return result;
    }

    void destroy(BinaryTree* tree){
        deleteTreeRecursive(tree -> root);
        delete tree;
        tree = nullptr;
    }

    void deleteTreeRecursive(Node* root){
        if(root == nullptr){
            return;
        }

        //Delete nodes by DFS
        deleteTreeRecursive(root -> left);
        deleteTreeRecursive(root -> right);

        delete root;
    }

}