#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "data.h"

using namespace std;

namespace data {

    vector<vector<string>> readData(string dirpath, int numMax){

        vector<vector<string>> texts;
        for(int i = 0; i < numMax; i++){
            vector<string> text;
            string filename = dirpath + to_string(i) + ".txt";            
            fstream arquivo(filename);
            
            if (!arquivo.is_open()){
                // stop if the directory path is invalid or when the number is greater than .txt's  
                break; 
            } else{
                string word;
                while (arquivo >> word) {
                    text.push_back(word);
                }
            }
            texts.push_back(text);
        }
        return texts;
    }

}
