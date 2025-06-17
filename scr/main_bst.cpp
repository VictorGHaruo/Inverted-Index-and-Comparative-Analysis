#include <iostream>
#include <fstream>
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
    // if not found other char means that is all numbers but all 0's, thus not positive even if the fist char is '+'
    if (strNum.find_first_not_of('0', inter) == string::npos) return false; 
    
    return true;
}

bool validate(int argc, char* argv[], string* command, vector<vector<string>>* texts){
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <command> <n_docs> <directory_path>" << endl;
        cerr << "<command> : 'search' or 'stats'" << endl;
        cerr << "<n_dcos> : a positive integer number" << endl;
        cerr << "<directory_path> : exemple '../data/' " << endl;
        return false;
    }
    *command = argv[1];
    if (!(*command == "search" || *command == "stats")) {
        cerr << "Usage: " << argv[0] << " <command> <n_docs> <directory_path>" << endl;
        cerr << "Error: The arg <command> must be 'search' or 'stats'." << endl;
        return false;
    }
    unsigned int numMax = 0;
    if (isPosInt(argv[2])){
        numMax = stoi(argv[2]);
    } else {
        cerr << "Usage: " << argv[0] << " <command> <n_docs> <directory_path>" << endl;
        cerr << "Error: <n_docs> must be a positive integer." << endl;;
        return false;
    }
    // matrix of texts' words
    *texts = data::readData(argv[3], numMax);
    if ((*texts).empty()){
        cerr << "Usage: " << argv[0] << " <command> <n_docs> <directory_path>" << endl;
        cerr << "Error: Directory path is invalid." << endl;
        return false;
    } else if((*texts).size() < numMax){ // opcional
        cerr << "Warning: n_docs is greater than the number of txt's in the directory." << endl;
    }
    
    return true;
}

void searchLooping(BinaryTree* bst){
    cout << endl << "Welcome to the CLI - Search!" << endl << endl;
    while (true){
        cout << "To quit, search for 'Q'." << endl;
        cout << "Search the word: ";
        string line_ignored;
        string word;
        cin >> word; // take the fist word
        getline(cin, line_ignored);
        //if the rest of input is just ' ' it's okay, if not it's 2+ words
        if(line_ignored.length() > 1 && line_ignored.find_first_not_of(' ') != string::npos){
            cout << endl << "- Wait, just one word. Try again." << endl << endl;
            continue;
        }
        
        if(word == "Q") break;
 
        SearchResult result = BST::search(bst, word);
        if(result.found){
            cout << endl << "- The word '" << word << "' was found!" << endl;
            cout << "- It's in " << result.documentIds.size() << " docs, with index: ";
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

void save(vector<InsertResult> insertResults, vector<SearchResult> searchResults, string filename){
    ofstream insertFileOut("../stats/insertResultsBST_" + filename);
    ofstream searchFileOut("../stats/searchResultsBST_" + filename);
    if(insertFileOut.is_open()){
        insertFileOut << "Execution Time, Is new, Num Comparasion, Word, Max Height, Min Height \n";
        int sizeInsert = insertResults.size();
        for(int i = 0; i < sizeInsert; i++){
            insertFileOut << insertResults[i].executionTime << "," 
                << insertResults[i].isNew << "," 
                << insertResults[i].numComparisons << "," 
                << insertResults[i].word << ","
                << insertResults[i].maxHeight << ", "
                << insertResults[i].minHeight << "\n";
        }
    }else{
        cerr << "Error opening file or directory ../stats/" << endl;
    }
    
    if(searchFileOut.is_open()){
        int sizeSearch = searchResults.size();
        searchFileOut << "Size of DocumentIds, Execution Time, Num Comparisions \n";
        for(int i = 0; i < sizeSearch; i++){
            int sizeDocumentIds = searchResults[i].documentIds.size();
            searchFileOut << sizeDocumentIds << "," 
                << searchResults[i].executionTime << ","
                << searchResults[i].numComparisons << "\n";
        }
    }else{
        cerr << "Error opening file or directory ../stats/" << endl;
    }

}

void stats(vector<InsertResult> insertResults, BinaryTree* bst){
    //  stats of insert
    int sizeInsRes = insertResults.size();
    double totTimeInsert = 0;
    int totCompInsert = 0;
    vector<string> uniqWords;
    for(int i = 0; i < sizeInsRes; i++){
        totTimeInsert += insertResults[i].executionTime;
        totCompInsert += insertResults[i].numComparisons;
        if(insertResults[i].isNew){
            uniqWords.push_back(insertResults[i].word);
        }
    }
    double aveTimeInsert = totTimeInsert / sizeInsRes;

    //  stats of search
    int sizeUniqWords = uniqWords.size();
    double totTimeSearch = 0;
    int totCompSearch = 0;
    vector<SearchResult> searchResults;
    double maxTimeSearch = 0;
    double minTimeSearch = 0;
    for(int i = 0; i < sizeUniqWords; i++){
        searchResults.push_back(BST::search(bst, uniqWords[i]));
        totTimeSearch += searchResults[i].executionTime;
        totCompSearch += searchResults[i].numComparisons;
        if(searchResults[i].executionTime > maxTimeSearch) maxTimeSearch = searchResults[i].executionTime;
        if(searchResults[i].executionTime < minTimeSearch) minTimeSearch = searchResults[i].executionTime;
    }
    double aveTimeSearch = totTimeSearch / sizeUniqWords;

    //  height
    int maxHeightTree = getMinOrMaxPath(bst->root, "max");
    int minHeightTree = getMinOrMaxPath(bst->root, "min");

    cout << endl <<  "Welcome to the CLI - Stats!" << endl;
    cout << "The stats were: " << endl;
    cout << "- "<< sizeUniqWords << " different words were added." << endl;
    cout << "- Height of longest path and Tree's height: " << maxHeightTree << endl;
    cout << "- Height of shortest path : " << minHeightTree << endl << endl;
    cout << "Insertion: " << endl;
    cout << "- Total time : " << totTimeInsert << "ms = " << totTimeInsert/1000 << "s" << endl;
    cout << "- Average time : " << aveTimeInsert << "ms = " << aveTimeInsert/1000 << "s" << endl;
    cout << "- Total number of comparisons : " << totCompInsert << endl << endl;
    cout << "Search: " << endl;
    cout << "- Total time to search for all the words : " << totTimeSearch << "ms = " << totTimeSearch/1000 << "s" << endl;
    cout << "- Average time : " << aveTimeSearch << "ms = " << aveTimeSearch/1000 << "s" << endl;
    cout << "- Total number of comparisons : " << totCompSearch << endl;

    while (true) {
        cout << endl << "Options to do:" << endl;
        cout << "1 - Quit and Save the Stats in a csv." << endl;
        cout << "2 - Print the tree." << endl;
        cout << "3 - Save the print of the tree in a '.txt'." << endl;
        cout << "4 - Print index of the tree." << endl;
        cout << "5 - Save the print index of the tree." << endl << endl;
        cout << "- Select the option: ";
        
        string answer; 
        cin >> answer;

        // Ignore after the space
        string line_ignored;
        getline(cin, line_ignored);

        unsigned int option = 0;
        if(isPosInt(answer)){
            option = stoi(answer);
        } else {
            cout << endl << "- Sorry, but it's not a positive integer. Try again." << endl;
            continue;
        }

        if(option == 1){
            string filename;
            while(true){
                cout << "- Chose the file name: ";
                cin >> filename;
                getline(cin, line_ignored);
                //if the rest of input is just ' ' it's okay, if not it's 2+ words
                if(line_ignored.length() > 1 && line_ignored.find_first_not_of(' ') != string::npos){
                    cout << endl << "- Wait, just one word. Try again." << endl << endl;
                    continue;
                }
                filename += ".csv";
                break;
            }
            save(insertResults, searchResults, filename);
            cout << endl << "- Saved!" << endl;
            return;
        }

        else if(option == 2){
            printTree(bst);
            // return;
        }

        else if(option == 3){
            while(true){
                cout << "- Chose the file name: ";
                string filename;
                cin >> filename;
                getline(cin, line_ignored);
                //if the rest of input is just ' ' it's okay, if not it's 2+ words
                if(line_ignored.length() > 1 && line_ignored.find_first_not_of(' ') != string::npos){
                    cout << endl << "- Wait, just one word. Try again." << endl << endl;
                    continue;
                }
                filename = "../stats/" + filename + ".txt";
                savePrintTree(bst, filename);
                cout << endl << "- Saved!" << endl;
                break;
                // return;
            }
        }

        else if(option == 4){
            printIndex(bst);
            // return;
        }

        else if(option == 5){
            while(true){
                cout << "- Chose the file name: ";
                string filename;
                cin >> filename;
                getline(cin, line_ignored);
                //if the rest of input is just ' ' it's okay, if not it's 2+ words
                if(line_ignored.length() > 1 && line_ignored.find_first_not_of(' ') != string::npos){
                    cout << endl << "- Wait, just one word. Try again." << endl << endl;
                    continue;
                }
                filename = "../stats/" + filename + ".txt";
                ofstream txt(filename);
                if(txt.is_open()){
                    // Make the cout write in the txt
                    streambuf* coutOriginal = cout.rdbuf();
                    cout.rdbuf(txt.rdbuf());
                    printIndex(bst);
                    cout.rdbuf(coutOriginal);
                    cout << endl << "- Saved!" << endl; 
                    break;
                } else{
                    cerr << "Error opening file." << endl;
                }
                // return;
            }
        } else {
            cout << endl << "- Number out of range. Try again." << endl;
        }

    }
    
}

int main(int argc, char** argv) {
    
    // Validate arguments
    string command;
    vector<vector<string>> texts;
    bool valide = validate(argc, argv, &command, &texts);
    if (!valide) return 1;

    // Populate the tree 
    BinaryTree* bst = BST::create();

    int sizeTexts = texts.size(); 
    vector<InsertResult> insertResults;
    for(int i = 0; i < sizeTexts; i++){
        int sizeT = texts[i].size();
        for(int j = 0; j < sizeT; j++){
            insertResults.push_back(BST::insert(bst, texts[i][j], i));
        }
    }  

    // Commands
    if (command == "search"){
        searchLooping(bst);
    } else { 
        stats(insertResults, bst);
    }

    return 0;
}