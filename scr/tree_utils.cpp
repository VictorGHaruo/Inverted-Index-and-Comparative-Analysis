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
    node->isRed = 0;

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
}

int computeDepth(Node* node){
    int depth = 0;
    while (node->parent != nullptr){
        node=node->parent;
        depth++;
    }

    return depth;
}

int getHeight(Node* node) {
        return node == nullptr ? -1 : node->height;
}

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
    if(root->isRed){
        std::string color = "\033[31m" + root->word + "\033[0m";
        cout << color << endl;
    } else {
        cout << root->word << endl;
    }

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

// Auxiliary recursive function for savePrintTree
void savePrintTreeAux(Node* root, const std::string &prefix, bool isLast, std::ofstream& txt){

    if (root == nullptr) return;

    txt << prefix;

    if (! prefix.empty()){
        if (isLast) {
            txt << "└──";
        } else {
            txt << "├──";
        }
    }
    
    txt << root->word << endl;

    std::string newPrefix = prefix + (isLast ? "   " : "│  ");

    if(root->right == nullptr)
        savePrintTreeAux(root->left, newPrefix, true, txt);
    else {
        savePrintTreeAux(root->left,  newPrefix, false, txt);
        savePrintTreeAux(root->right, newPrefix, true, txt);
    }
        
}

void savePrintTree(BinaryTree* tree, std::string filename){
    Node* n = tree->root;
    std::ofstream txt(filename);
    if(!n){
        cerr << "Eroor: Tree empty." << endl;
    }
    if(txt.is_open()) {
        savePrintTreeAux(n, "", true, txt);
    } else{
        cerr << "Error opening file " << filename << endl;
    }
}

};