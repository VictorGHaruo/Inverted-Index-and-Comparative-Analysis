#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

namespace data {

    /** 
     * @brief Retorn a vector of vectors with the words of each text (.txt in the dirname) util the number max.
     * @param dirname String with the path of the directory data
     * @param numMax Int with the maximum number of texts read
     * @return vector<vector<string>> 
    */
    std::vector<std::vector<std::string>> readData(std::string dirname, int numMax);

}

#endif