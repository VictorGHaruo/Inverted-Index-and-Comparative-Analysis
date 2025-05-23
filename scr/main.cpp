#include "data.h"
#include <iostream>

using namespace std;

int main(){

    char dirname[] = "../data/";

    data::readData(dirname, 2);
    return 0;
}