#include <iostream>
#include "tree_utils.h"
#include "avl.h"
using namespace std;

int main(){
    BinaryTree *tree = AVL::create();

    // AVL::insert(tree, "f", 1); 
    // AVL::insert(tree, "g", 2);
    // AVL::insert(tree, "h", 3);
    // printTree(tree);
    // cout << "========= \\ =========" << endl;
    // AVL::insert(tree, "b", 4);
    // printTree(tree);
    // cout << "========= \\ =========" << endl;
    // AVL::insert(tree, "a", 5);
    // printTree(tree);
    // cout << "========= \\ =========" << endl;

    cout << "========= Teste Right Rotation =========" << endl;
    InsertResult insert_root = AVL::insert(tree, "charizard", 3);
    AVL::insert(tree, "bulbasaur", 2);
    AVL::insert(tree, "arceus", 1); // Right Rotation
    printTree(tree);
    cout << endl ;

    cout << "========= Teste Left Rotation =========" << endl;
    AVL::insert(tree, "dratini", 4);
    AVL::insert(tree, "elekid", 5); // Left Rotation ao inserir "e"
    printTree(tree);
    cout << endl ;

    cout << "========= Teste Left-Right Rotation =========" << endl;
    AVL::insert(tree, "galade", 7);
    AVL::insert(tree, "flareon", 6); // Left-Right Rotation ao inserir "f"
    printTree(tree);
    cout << endl ;

    cout << "========= Teste Right-Left Rotation =========" << endl;
    AVL::insert(tree, "igglybuff", 9);
    InsertResult insert_last = AVL::insert(tree, "hypno", 8); // Right-Left Rotation ao inserir "h"
    printTree(tree);
    cout << endl ;

    cout << "========= Insert: Root =========" << endl;
    cout << "Execution Time: " << insert_root.executionTime << endl;
    cout << "Number of Comparisons:" << insert_root.numComparisons << endl;
    cout << endl;

    cout << "========= Insert: Last =========" << endl;
    cout << "Execution Time: " << insert_last.executionTime << endl;
    cout << "Number of Comparisons:" << insert_last.numComparisons << endl;
    cout << endl ;

    cout << "========= Delete Tree =========" << endl;
    AVL::deleteTree(tree);

}