#include <iostream>
#include <string>
#include <vector>
#include "data.h"
#include "bst.h"
#include "tree_utils.h"

using namespace std;

bool isPosInt(string strNum){
    int inter = 0;
    if(strNum[0] == '-'){
        return false;
    } else if (strNum[0] == '+'){
        inter = 1;
    }
    int size = strNum.size();
    for(int i = inter; i < size; i++){
        if(!isdigit(strNum[i])) return false;
    }
    //if not found other char means that is all numbers but all 0's, thus not positive even if the fist char is '+'
    if (strNum.find_first_not_of('0', inter) == string::npos) return false; 
    
    return true;
}

int main(int argc, char** argv) {
    
    // Validate arguments
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "<comand> : 'search' or 'stats'" << endl;
        cerr << "<n_dcos> : a positve integer number" << endl;
        cerr << "<directory_path> : exemple '../data/' " << endl;
        return 1;
    }
    string comand = argv[1];
    if (!(comand == "search" || comand == "stats")) {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "Error: The arg <comand> must be 'search' or 'stats'." << endl;
        return 1;
    }
    int numMax = -1;
    if (isPosInt(argv[2])){
        numMax = stoi(argv[2]);
    } else {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "Error: <n_docs> must be a positive integer." << endl;;
        return 1;
    }
    auto texts = data::readData(argv[3], numMax);
    if (texts.empty()){
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "Error: Directory path is invalid." << endl;
        return 1;
    } else if(texts.size() < numMax){ //opcional
        cerr << "Warning: n_docs is greater than the number of txt's in the directory." << endl;
    }

    // Populate the tree 
    BinaryTree* bst = BST::create();

    int sizeTexts = texts.size();
    for(int i = 0; i < sizeTexts; i++){
        int sizeT = texts[i].size();
        for(int j = 0; j < sizeT; j++){
            BST::insert(bst, texts[i][j], i);
        }
    }

    // Commands
    if (comand == "search"){
        
        printIndex(bst);
        // cout << "OIII" << endl;

    } else { //already garanted that is stats.
        
        cout << "Not to do yet" << endl;
    
    }


    return 0;
}