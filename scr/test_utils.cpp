# include "tree_utils.h"
# include <iostream>

using namespace std;

int main(){

    Node* root = createNode("arnaldo", {1, 2, 3}, nullptr);
    BinaryTree* tree = createTree(root);

    root->left = createNode("bernaldo", {1, 2}, root);
    root->right = createNode("cernaldo", {1,3}, root);
    root->left->left = createNode("dernaldo", {1,2}, root->left);
    root->left->right = createNode("enaldo", {2}, root->left);

    // Some tests...
    cout << "========= PrintTree =========" << endl;
    printTree(tree);

    cout << "========= PrintIndex =========" << endl;
    printIndex(tree);
    
    cout << "Depth (Bernaldo): " << computeDepth(root->left) << endl;
    cout << "Height (enaldo): " << computeHeight(root->left->right) << endl;
}