# include "tree_utils.h"

using namespace std;
using namespace TreeUtils;

namespace TreeUtils {

Node* createNode(std::string word, std::vector<int> documentsId, Node* parent){
    Node* node = new Node();
    node->word = word;
    node->documentIds = documentsId;

    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;

    node->height = 0;
    node->isRed = 1;

    return node;
}

// Prints vector elements separated by commas for readable output
void printVector(const std::vector<int> vec){
    int n = vec.size();
    for (int i = 0; i < n; i++){
        cout << vec[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }    
}

// Auxiliary recursive function for printIndex
void printIndexAux(Node* root, int &counter){

    if (root != nullptr) {
        cout << counter <<". " << root->word << ": "; 
        printVector(root->documentIds);
        cout << endl;
        counter++;

        printIndexAux(root->left, counter);
        printIndexAux(root->right, counter);
    }
}

void printIndex(BinaryTree* tree){
    Node* n = tree->root;
    int counter = 1;

    if (n != nullptr) {
        printIndexAux(n, counter);
    }
};

int computeDepth(Node* node){
    int depth = 0;
    while (node->parent != nullptr){
        node=node->parent;
        depth++;
    }

    return depth;
};

int getHeight(Node* node) {
        return node == nullptr ? -1 : node->height;
    };

void computeHeight(Node* node) {
    if (node == nullptr) {
        return; 
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}


// Auxiliary recursive function for printTree
void printTreeAux(Node* root, const std::string &prefix, bool isLast){

    if (root == nullptr) return;

    cout << prefix;

    if (! prefix.empty()){
        if (isLast) {
            cout << "└──";
        } else {
            cout << "├──";
        }
    }
 
    cout << root->word << endl;

    string newPrefix = prefix + (isLast ? "   " : "│  ");

    if(root->right == nullptr)
        printTreeAux(root->left, newPrefix, true);
    else {
        printTreeAux(root->left,  newPrefix, false);
        printTreeAux(root->right, newPrefix, true);
    }
        
}

void printTree(BinaryTree* tree){

    Node* n = tree->root;
    
    if (n != nullptr) {
        printTreeAux(n, "", true);
    }
}

};