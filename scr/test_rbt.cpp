#include <iostream>
#include "tree_utils.h"
#include "rbt.h"
using namespace std;

// PrintTree with colors for better visualization and debug
void printRBTAux(Node* root, const std::string &prefix, bool isLast){

    if (root == nullptr) return;

    cout << prefix;

    if (! prefix.empty()){
        if (isLast) {
            cout << "└──";
        } else {
            cout << "├──";
        }
    }
 
    cout << (root->isRed ? "\033[31m" : "\033[0m") << root->word << "\033[0m" << endl;

    string newPrefix = prefix + (isLast ? "   " : "│  ");

    if(root->right == nullptr)
        printRBTAux(root->left, newPrefix, true);
    else {
        printRBTAux(root->left,  newPrefix, false);
        printRBTAux(root->right, newPrefix, true);
    }
        
}

void printRBT(BinaryTree* tree){

    Node* n = tree->root;
    
    if (n != nullptr) {
        printRBTAux(n, "", true);
    }
}

int main(){

    BinaryTree *tree = RBT::create();

    cout << "=========== Initial Tree ===========" << endl;
    // Inserting when the root is a null pointer
    InsertResult insert_root = RBT::insert(tree, "fernaldo", 1); 
    RBT::insert(tree, "enaldo", 5);
    printRBT(tree);
    // Cases in the left, dernaldo is left child, so we need to RotateRight
    cout << "======== Case 3 in the left ========" << endl;
    RBT::insert(tree, "dernaldo", 5);
    printRBT(tree);

    // Uncle is red, so we need to recolor
    cout << "======== Case 1 in the left ========" << endl;
    RBT::insert(tree, "bernaldo", 2);
    printRBT(tree);
    
    // Uncle doesn't exists, cernaldo is right child, so, case 2 and after, case 3.
    cout << "======== Case 2 in the left ========" << endl;
    RBT::insert(tree, "cernaldo", 3);
    printRBT(tree);
    
    
    // Inserting same word with different ID
    RBT::insert(tree, "dernaldo", 4);
    cout << "============ PrintIndex ============" << endl;
    printIndex(tree);

    RBT::insert(tree, "gernaldo", 3); // No need fixInsert
    
    InsertResult insert_last = RBT::insert(tree, "gabriel", 1);
    cout << "=========== Insert: Root ===========" << endl;
    cout << "Execution Time: " << insert_root.executionTime << endl;
    cout << "Number of Comparisons:" << insert_root.numComparisons << endl;
    cout << endl;

    cout << "=========== Insert: Last ===========" << endl;
    cout << "Execution Time: " << insert_last.executionTime << endl;
    cout << "Number of Comparisons:" << insert_last.numComparisons << endl;
    cout << endl ;

    // Search for dernaldo
    cout << "========= Search: dernaldo =========" << endl;

    SearchResult result_one = RBT::search(tree, "dernaldo");
    cout << "Execution Time: " << result_one.executionTime << endl;
    cout << "Found...? " << result_one.found << endl;
    cout << "Number of Comparisons: " << result_one.numComparisons << endl;
    cout << "Parent: " 
         << (result_one.parent == nullptr 
         ? "None (this node is the root)" 
         : result_one.parent->word) << endl;
    cout << "Documents IDs: ";
    for (int i = 0; i < static_cast<int>(result_one.documentIds.size()); i++){
        cout << result_one.documentIds[i]<< " ";
    }
    cout << endl << endl;

    // Search for root (enaldo)
    cout << "=========== Search: Root ===========" << endl;

    SearchResult result_two = RBT::search(tree, "enaldo");
    cout << "Execution Time: " << result_two.executionTime << endl;
    cout << "Found...? " << result_two.found << endl;
    cout << "Number of Comparisons: " << result_two.numComparisons << endl;
    cout << "Parent: " 
         << (result_two.parent == nullptr 
         ? "None (this node is the root)" 
         : result_two.parent->word) << endl;
    cout << "Documents IDs: ";
    for (int i = 0; i < static_cast<int>(result_two.documentIds.size()); i++){
        cout << result_two.documentIds[i]<< " ";
    }
    cout << endl << endl;
    
    cout << "============= The Tree =============" << endl;
    printRBT(tree);
    cout << endl;

    cout << "============ Delete Tree ===========" << endl;
    RBT::destroy(tree);

}