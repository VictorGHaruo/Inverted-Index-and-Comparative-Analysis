#include <iostream>
#include <vector>
#include <string> // Adicionado para std::string
#include <algorithm> // Adicionado para std::max
#include "avl.h"      // Presume que Node, BinaryTree, SearchResult, InsertResult são definidos aqui
#include "tree_utils.h" // Presume que createNode e computeHeight são definidos aqui
#include <chrono>

using namespace std;
// using namespace AVL; // Melhor evitar 'using namespace' globalmente em arquivos .h ou .cpp grandes. Usar std:: e AVL:: explicitamente.
using namespace std::chrono;

// Protótipo para computeHeight, assumindo que está em tree_utils.h ou avl.h
// Se não estiver, você precisará de uma definição como:
/*
namespace AVL {
    void computeHeight(Node* node) {
        if (node == nullptr) return;
        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        node->height = 1 + std::max(leftHeight, rightHeight);
    }
}
*/


namespace AVL {
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree();
        tree->root = nullptr;
        tree->NIL = nullptr; // Se NIL for usado como sentinela, precisa de tratamento especial.
                             // Se for apenas um alias para nullptr, é redundante.
                             // O código atual usa nullptr para checagens.
        return tree;
    }

    int BalancingFactor(Node* node) {
        if (node == nullptr) {
            return 0; // Fator de balanceamento de um nó nulo é 0
        }
        // Altura de um nó nulo é convencionalmente -1 para que folhas (com filhos nulos) tenham altura 0.
        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        return leftHeight - rightHeight;
    }

    // As funções de rotação devem estar corretas e chamar computeHeight nos nós afetados.
    // O código original para rotações parece lidar com os ponteiros e alturas.
    // Elas retornam a nova raiz da subárvore rotacionada.

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

    Node* balance(Node* node_to_balance) {
        if(node_to_balance == nullptr){
            return nullptr;
        }
        
        computeHeight(node_to_balance);
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

    int getHeight(Node* n) {
        return n == nullptr ? -1 : n->height;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        auto start = high_resolution_clock::now(); //Starts clock
        SearchResult search_result = search(tree, word);

        if(search_result.found == 1){//The word is already in the tree
            
            //To avoid repeating document IDs when adding words
            int n = search_result.resultedNode->documentIds.size();
            bool exists = false;
            for (int i = 0; i < n; i++){
                if(search_result.resultedNode->documentIds[i] == documentId){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                search_result.resultedNode->documentIds.push_back(documentId);
            }
        }
        else{ //The word isn't in the tree
            vector<int> documentID = {documentId};
            Node *node = createNode(word, documentID, search_result.parent);

            if(search_result.parent == nullptr){ //The root is a nullptr
                tree->root = node;
            } 
            else if(word < search_result.parent->word){ // Determine which side to place the word on
                search_result.parent->left = node;
            }
            else {
                search_result.parent->right = node;
            }
            
            tree->root->height = 1 + std::max(getHeight(tree->root->left), getHeight(tree->root->right));
            tree->root = balance(tree->root);
        }


        auto end = high_resolution_clock::now(); //Ends clock

        //Convert the auto-typed variable to double, representing milliseconds
        auto duration = end - start;
        chrono::duration<double, milli> duration_ms = duration;
        double time = duration_ms.count();

        InsertResult result;

        // + 1 comes drom the comparson that determines which side the word goes
        result.numComparisons = search_result.numComparisons + 1;
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
        if (tree == nullptr) return; // Adiciona verificação para árvore nula
        deleteTreeRecursive(tree->root);
        delete tree;
        // tree = nullptr; // Definir o ponteiro original como nullptr é responsabilidade do chamador
    }

    void deleteTreeRecursive(Node* node) { // Renomeado 'root' para 'node' para clareza no contexto recursivo
        if (node == nullptr) {
            return;
        }

        // Deleta os nós em pós-ordem (DFS)
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);

        delete node;
    }
} // Fim do namespace AVL
