# include "tree_utils.h"
# include <iostream>

using namespace std;
using namespace TreeUtils;

int main(){

    Node* root = createNode("arnaldo", {1, 2, 3}, nullptr);
    BinaryTree* tree = new BinaryTree();
    tree->root = root;
    tree->NIL = nullptr;

    root->left = createNode("bernaldo", {1, 2}, root);
    root->right = createNode("cernaldo", {1,3}, root);
    root->left->left = createNode("dernaldo", {1,2}, root->left);
    root->left->right = createNode("enaldo", {2}, root->left);

    cout << "========= PrintTree =========" << endl;
    printTree(tree);

    cout << "========= PrintIndex =========" << endl;
    printIndex(tree);

    }