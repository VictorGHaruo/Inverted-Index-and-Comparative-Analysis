#include <iostream>
#include <string>
#include <vector>
#include "data.h"
#include "bst.h"
#include "tree_utils.h"

using namespace std;

int main(int argc, char** argv) {
    
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        return 1;
    }

    string comand = argv[1];
    if (!(comand == "search" || comand == "stats")) {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "The arg <comand> must be 'search' or 'stats'." << endl;
        return 1;
    }

    int numMax = -1;
    try{
        int numMax = stoi(argv[2]);
    } catch (...) {
        cerr << "Algo de errado não está certo." << endl;
    } 
    if(numMax < 0) {
        cerr << "Algo de errado não está certo. 2" << endl;
        return 1;
    }
    auto texts = data::readData(argv[3], numMax);
    
    if (texts.empty()){
        cerr << "Directory path is invalid." << endl;
        return 1;
    } else if(texts.size() < numMax){ //opcional
        cerr << "n_docs is greater than the number of txt's in the directory." << endl;
    }
    
    //Só por agr
    string a = "Teste";
    vector<int> b = {1};

    Node* fistnode = createNode(a, b, nullptr);
    BinaryTree* bst = createTree(fistnode);

    if (comand == "search"){
        
        cout << "OIII" << endl;

    } else { //already garanted that is stats.
        
        cout << "Not to do yet" << endl;
    
    }


    return 0;
}