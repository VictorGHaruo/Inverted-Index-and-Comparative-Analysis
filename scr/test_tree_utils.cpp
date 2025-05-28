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

    // Some tests...
    cout << "========= PrintTree =========" << endl;
    printTree(tree);

    cout << "========= PrintIndex =========" << endl;
    printIndex(tree);

    cout << "\n========= Tests Depth =========" << endl;
    cout << "Depth (arnaldo/root): " << computeDepth(root) << endl;
    cout << "Depth (bernaldo): " << computeDepth(root->left) << endl;
    cout << "Depth (cernaldo): " << computeDepth(root->right) << endl;
    cout << "Depth (dernaldo): " << computeDepth(root->left->left) << endl;
    cout << "Depth (enaldo): " << computeDepth(root->left->right)  << endl;

    // cout << "\n========= Tests Height =========" << endl;
    // cout << "Height (arnaldo/root): " << computeHeight(root) << endl;
    // cout << "Height (bernaldo): " << computeHeight(root->left) << endl;
    // cout << "Height (cernaldo): " << computeHeight(root->right) << endl;
    // cout << "Height (dernaldo): " << computeHeight(root->left->left) << endl;
    // cout << "Height (enaldo): " << computeHeight(root->left->right) << endl;}