# include "tree_utils.h"

using namespace std;

Node* createNode(std::string word, std::vector<int> documentsId, Node* parent){
    Node* node = new Node();
    node->word = word;
    node->documentIds = documentsId;

    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;

    // To be corrected...
    node->height = 1;
    node->isRed = 0;

    return node;
}


// Maybe will be changed file
BinaryTree* createTree(Node* root){
    BinaryTree* tree = new BinaryTree();
    tree->root = root;
    tree->NIL = nullptr;

    return tree;
}

// Auxiliary function
void printVector(const std::vector<int> vec){
    int n = vec.size();
    for (int i = 0; i < n; i++){
        cout << vec[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }    
}

// To be fixed: the position of each word is missing
void printIndex(BinaryTree* tree){
    Node* n = tree->root;

    if (n != nullptr) {
        cout << ". " << n->word << ": "; 
        printVector(n->documentIds);
        cout << endl;
        // better if create a new tree for each side? ...
        printIndex(createTree(n->left));
        printIndex(createTree(n->right));
    }
};

int computeDepth(Node* node){
    Node* curr = node;
    int depth = 0;
    while (curr->parent != nullptr){
        curr=curr->parent;
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

// To be corrected...
void printTree(BinaryTree* tree){
    Node* n = tree->root;

    // // │   ├── │   └──"
    // if (n != nullptr) {
    //     cout << n->word << endl;

    //     if (n->left != nullptr){
    //         cout << "├── ";
    //         printTree(createTree(n->left));
    //     }

    //     if (n->right != nullptr){
    //         cout << "└── ";
    //         printTree(createTree(n->right));
    //     }
    
    // }
}



