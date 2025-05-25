#include <iostream>
#include <vector>
#include "bst.h"
#include "tree_utils.h"
#include <chrono>
using namespace std;
using namespace BST;
using namespace std::chrono;

namespace BST{
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult searchNode = search(tree, word);

        if (searchNode.found == 1){ //The word is already in the tree

            //To avoid repeating document IDs when adding words
            for (int i = 0; i < searchNode.resultedNode->documentIds.size(); i++){
                if (searchNode.resultedNode->documentIds[i] == documentId){
                    break;
                }
                else{
                    searchNode.resultedNode->documentIds.push_back(documentId);     
                }
            }
        }
        else{ //The word isn't in the tree
            vector<int> documentID = {documentId};
            Node *node = createNode(word, documentID, searchNode.parent);

            if (searchNode.parent == nullptr){ //The root is a nullptr
                tree->root = node;
            }
            else if(word < searchNode.parent->word){ // Determine which side to place the word on
                searchNode.parent->left = node;
            }
            else{
                searchNode.parent->right = node;
            }
        }
        auto end = high_resolution_clock::now(); //Ends clock

        //Convert the auto-typed variable to double, representing milliseconds
        auto duration = end - start;
        chrono::duration<double, milli> duration_ms = duration;
        double time = duration_ms.count();

        InsertResult result;
        
        // +1 comes from the comparison that determines which side the word goes
        result.numComparisons = searchNode.numComparisons + 1; 
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
        }
        else{
            result.found = 1;
            result.documentIds = current->documentIds;
        }
        return result;
    }

    void deleteTree(BinaryTree* tree){
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