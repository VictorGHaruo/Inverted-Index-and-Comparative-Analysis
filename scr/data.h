#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

namespace data {

    /** 
     * @brief Retorn a vector of vectors (matrix) with the words of each text (.txt in the directory) util the number max.
     * 
     * Returns a empyt vector if the dirpath is invalid.
     * 
     * If the function can't read a .txt, means that there's not more to read thus it stops.
     * 
     * @param dirpath String with the path of the directory data
     * @param numMax Int with the maximum number of texts read
     * @return Matrix of words 
    */
    std::vector<std::vector<std::string>> readData(std::string dirpath, int numMax);

}

#endif