#include <iostream>
#include "tree_utils.h"
#include "bst.h"
using namespace std;


int main(){
    BinaryTree *tree = BST::create();

    // Inserting when the root is a null pointer
    InsertResult insert_root = BST::insert(tree, "sabrina", 1); 
    BST::insert(tree, "carpenter", 2);
    BST::insert(tree, "olivia", 3);
    BST::insert(tree, "taylor", 4);
    BST::insert(tree, "swift", 5);
    BST::insert(tree, "rodrigo", 5);
    
    //Adding a node that already exists, but with a different ID
    BST::insert(tree, "swift", 4);
    
    // Adding a node that already exists, but with a equal ID
    InsertResult insert_last = BST::insert(tree, "olivia", 3);
    
    
    cout << "========= Insert: Root =========" << endl;
    cout << "Execution Time: " << insert_root.executionTime << endl;
    cout << "Number of Comparisons:" << insert_root.numComparisons << endl;
    cout << endl;

    cout << "========= Insert: Last =========" << endl;
    cout << "Execution Time: " << insert_last.executionTime << endl;
    cout << "Number of Comparisons:" << insert_last.numComparisons << endl;
    cout << endl ;

    cout << "========= Search: Different ID's =========" << endl;

    //Must appear 2 documents ID
    SearchResult result_one = BST::search(tree, "swift");
    cout << "Execution Time: " << result_one.executionTime << endl;
    cout << "Found...? " << result_one.found << endl;
    cout << "Number of Comparisons:" << result_one.numComparisons << endl;
    cout << "Parent: " << result_one.parent->word << endl;
    cout << "Documents IDs: ";
    for (int i = 0; i < result_one.documentIds.size(); i++){
        cout << result_one.documentIds[i]<< " ";
    }
    cout << endl << endl;

    cout << "========= Search: Equal ID's =========" << endl;
    // Must appear 1 documents ID
    SearchResult result_two = BST::search(tree, "olivia");
    cout << "Execution Time: " << result_two.executionTime << endl;
    cout << "Found...? " << result_two.found << endl;
    cout << "Number of Comparisons:" << result_two.numComparisons << endl;
    cout << "Parent: " << result_two.parent->word << endl;
    cout << "Documents IDs: ";
    for (int i = 0; i < result_two.documentIds.size(); i++){
        cout << result_two.documentIds[i]<< " ";
    }
    cout << endl << endl;
    
    cout << "========= Tree =========" << endl;
    printTree(tree);
    cout << endl;

    cout << "========= Delete Tree =========" << endl;
    BST::deleteTree(tree);

}