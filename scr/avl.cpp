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
            return; // Não há altura para calcular para um nó nulo
        }
        // Usa sua função getHeight que já trata filhos nulos como altura -1
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

        std::cout << "passei aqui" << std::endl;
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

        std::cout << "passei aqui" << std::endl;
        std::cout << "fb = " << fb << std::endl;
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



    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto start_time_measurement = std::chrono::high_resolution_clock::now();
        SearchResult search_result = search(tree, word);

        if (search_result.found == 1) { // A palavra já está na árvore
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
        } else { // A palavra não está na árvore
            std::vector<int> initial_doc_ids = {documentId};
            // createNode deve definir a altura do novo nó (ex: 0 para folhas) e o ponteiro parent.
            Node *new_node = createNode(word, initial_doc_ids, search_result.parent);

            if (search_result.parent == nullptr) { // A árvore estava vazia
                tree->root = new_node;
            } else {
                if (word < search_result.parent->word) {
                    search_result.parent->left = new_node;
                } else {
                    search_result.parent->right = new_node;
                }
            }

            // === LÓGICA DE BALANCEAMENTO AVL BOTTOM-UP ===
            Node* current_ancestor = search_result.parent; // Começa pelo pai do nó inserido

            while (current_ancestor != nullptr) {
                // std::cout << "Balanceando ancestral: " << current_ancestor->word << std::endl;

                Node* original_ancestor_at_this_level = current_ancestor; // CORRIGIDO TYPO
                Node* parent_of_current_ancestor = current_ancestor->parent;

                // balance() chama computeHeight internamente e retorna a nova raiz da subárvore
                std::cout << "Passei no balance" << std::endl;
                Node* new_subtree_root = balance(current_ancestor);

                // Reconecta a (possivelmente nova) raiz da subárvore ao seu pai
                if (parent_of_current_ancestor == nullptr) {
                    // Se o pai do ancestral atual é nulo, significa que o ancestral era a raiz.
                    // Portanto, a new_subtree_root (resultado do balanceamento) é a nova raiz da árvore.
                    tree->root = new_subtree_root;
                } else {
                    // Se há um pai, precisamos ligar new_subtree_root ao filho correto desse pai.
                    if (parent_of_current_ancestor->left == original_ancestor_at_this_level) {
                        parent_of_current_ancestor->left = new_subtree_root;
                    } else {
                        parent_of_current_ancestor->right = new_subtree_root;
                    }
                }
                // As funções de rotação (chamadas por balance) devem atualizar o ponteiro `parent`
                // da `new_subtree_root` para que ele aponte para `parent_of_current_ancestor`.

                current_ancestor = parent_of_current_ancestor; // Move para o próximo ancestral
            }
        }

        auto end_time_measurement = std::chrono::high_resolution_clock::now();
        auto duration = end_time_measurement - start_time_measurement;
        std::chrono::duration<double, std::milli> duration_ms = duration; // Usar std::milli
        double time_taken = duration_ms.count();

        InsertResult result_obj;
        // Ajuste na contagem de comparações se a lógica de search for alterada
        result_obj.numComparisons = search_result.numComparisons; 
        // Se search_result.numComparisons já conta todas as comparações para encontrar o local,
        // o +1 anterior poderia ser removido. Mantendo como estava por enquanto.
        // Se a busca foi ajustada como sugeri, o +1 pode não ser necessário.
        // Para ser mais preciso, se a busca retorna o PAI do local de inserção,
        // o número de comparações da busca é o que levou até lá.
        // A lógica original `+1` para a comparação que decide esquerda/direita é implícita na busca.
        // Se a busca retorna 0 para árvore vazia, e N para encontrar o local/nó,
        // então numComparisons da busca é o correto.
        if (search_result.found == 0 && tree->root != nullptr) { // Se não encontrou e a árvore não está vazia
             // O +1 original poderia ser para a comparação final que falhou em encontrar.
             // Mas a lógica de numComparisons em search já deve cobrir isso.
             // Vou manter o +1 como no original, mas é um ponto para revisão detalhada.
            result_obj.numComparisons = search_result.numComparisons +1;
        } else {
            result_obj.numComparisons = search_result.numComparisons;
        }


        result_obj.executionTime = time_taken;

        return result_obj;
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
