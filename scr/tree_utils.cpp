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

    // To be corrected...
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
};

int computeDepth(Node* node){
    int depth = 0;
    while (node->parent != nullptr){
        node=node->parent;
        depth++;
    }

    return depth;
};

int computeHeight(Node* node){
    if (node == nullptr)
        return -1;
    int x = computeHeight(node->left);
    int y = computeHeight(node->right);

    return 1 + max(x,y);
}

// TODO: fix tree view
// Auxiliary recursive function for printTree
void printTreeAux(Node* root, int counter, bool isLast){

    if (root != nullptr) {
            
        if (counter > 0) {
            for (int i=1; i < counter; i++)
            cout << "│  ";
 
            if (isLast){
                cout << "└──";
            } else {
                cout << "├──";
            }
        }

        cout << root->word << endl;

        // If there is no child on the right, the child 
        // on the left will be the last
        if(root->right == nullptr)
            printTreeAux(root->left, counter + 1, true);
        else {
            printTreeAux(root->left, counter + 1, false);
            printTreeAux(root->right, counter + 1, true);
        }
        
    }

};

void printTree(BinaryTree* tree){

    Node* n = tree->root;
    int counter = 0;
    
    if (n != nullptr) {
        printTreeAux(n, counter, true);
    }
}

}
