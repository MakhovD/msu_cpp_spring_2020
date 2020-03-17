#include "parse.h"

void parse(std::string str, OnNumber fNumber, OnLetter fLetter, OnLim fBegin, OnLim fEnd){
    fBegin();
    size_t pos_1 = 0;
    size_t found;
    std::string token;

    while((found = str.find_first_of(" \n\t", pos_1))!=std::string::npos){
        token = str.substr(pos_1, found-pos_1);
        if (isdigit(token[0])){
            int number = atoi(token.c_str());
            fNumber(number);
        }
        else fLetter(token);
        pos_1 = str.find_first_not_of(" \n\t", found);
    }
    fEnd();
}