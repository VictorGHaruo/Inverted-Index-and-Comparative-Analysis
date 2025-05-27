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

bool Validade(int argc, char* argv[], string* comand, vector<vector<string>>* texts){
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "<comand> : 'search' or 'stats'" << endl;
        cerr << "<n_dcos> : a positve integer number" << endl;
        cerr << "<directory_path> : exemple '../data/' " << endl;
        return false;
    }
    *comand = argv[1];
    if (!(*comand == "search" || *comand == "stats")) {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "Error: The arg <comand> must be 'search' or 'stats'." << endl;
        return false;
    }
    unsigned int numMax = 0;
    if (isPosInt(argv[2])){
        numMax = stoi(argv[2]);
    } else {
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "Error: <n_docs> must be a positive integer." << endl;;
        return false;
    }
    //matrix of texts' words
    *texts = data::readData(argv[3], numMax);
    if ((*texts).empty()){
        cerr << "Usage: " << argv[0] << " <comand> <n_docs> <directory_path>" << endl;
        cerr << "Error: Directory path is invalid." << endl;
        return false;
    } else if((*texts).size() < numMax){ //opcional
        cerr << "Warning: n_docs is greater than the number of txt's in the directory." << endl;
    }
    
    return true;
}

void SearchLooping(BinaryTree* bst){
    cout << endl << "Welcome to the CLI - Search!" << endl << endl;
    while (true){
        cout << "To quit, search for 'Q'." << endl;
        cout << "Search the word: ";
        string line;
        string word;
        cin >> word; // take the fist word
        getline(cin, line);
        //if the rest of input is just ' ' it's okay, if not it's 2+ words
        if(line.length() > 1 && line.find_first_not_of(' ') != string::npos){
            cout << "- Please, just one word. Try again." << endl << endl;
            continue;
        }
        
        if(word == "Q") break;
 
        SearchResult result = BST::search(bst, word);
        if(result.found){
            cout << endl << "- The word '" << word << "' was found!" << endl;
            cout << "- It's in the docs with index: ";
            int sIds = result.documentIds.size();
            cout << "{" << result.documentIds[0];
            for(int i = 1; i < sIds; i++){
                cout << ", " << result.documentIds[i];
            }
            cout << "}" << endl;
            cout << "- It takes " << result.executionTime << "ms." << endl;
            cout << "- In " << result.numComparisons << " comparisons." << endl << endl;
        } else {
            cout << endl << "- The word '" << word << "' isn't in the texts! Try another word." << endl << endl;
        }
    }
}

void StatsLoopingg(vector<InsertResult> insRes, BinaryTree* bst, int sizeTexts){
    int sizeInsRes = insRes.size();
    double totTime = 0;
    int totComp = 0;
    for(int i = 0; i < sizeInsRes; i++){
        totTime += insRes[i].executionTime;
        totComp += insRes[i].numComparisons;
    }

    cout << "Welcome to the CLI - Stats!" << endl;
    cout << "The init stats were: " << endl;
    cout << "- Executation Time : " << totTime << "ms = " << totTime/1000 << "s" << endl;
    cout << "- Number of comparisons : " << totComp << endl;
    
    while(true){
        cout << endl << "To quit, add 'Q'." << endl;
        cout << "Add a new word: ";

        string line;
        string word;
        cin >> word; // take the fist word
        getline(cin, line);
        //if the rest of input is just ' ' it's okay, if not it's 2+ words
        if(line.length() > 1 && line.find_first_not_of(' ') != string::npos){
            cout << endl << "- Please, just one word. Try again." << endl;
            continue;
        }
        if(word == "Q") break;

        InsertResult res = BST::insert(bst, word, sizeTexts);
        cout << endl << "- Executation Time : " << res.executionTime << "ms = " << res.executionTime/1000 << "s" << endl;
        cout << "- Number of comparisons : " << res.numComparisons << endl;
    }
}

int main(int argc, char** argv) {
    
    // Validate arguments
    string comand;
    vector<vector<string>> texts;
    bool valide = Validade(argc, argv, &comand, &texts);
    if (!valide) return 1;

    // Populate the tree 
    BinaryTree* bst = BST::create();

    int sizeTexts = texts.size();
    vector<InsertResult> insRes;
    for(int i = 0; i < sizeTexts; i++){
        int sizeT = texts[i].size();
        for(int j = 0; j < sizeT; j++){
            insRes.push_back(BST::insert(bst, texts[i][j], i));
        }
    }

    // Commands
    if (comand == "search"){
        SearchLooping(bst);
    } else { 
        StatsLoopingg(insRes, bst, sizeTexts);
    }

    return 0;
}