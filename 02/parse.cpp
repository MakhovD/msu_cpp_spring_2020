#include "parse.h"

OnNumber fNumber = nullptr;
OnLetter fLetter = nullptr;
OnLim fBegin = nullptr;
OnLim fEnd = nullptr;

void register_on_number_callback(OnNumber callback){
    fNumber = callback;
}

void register_on_letter_callback(OnLetter callback){
    fLetter = callback;
}

void register_on_begin_callback(OnLim callback){
    fBegin = callback;
}

void register_on_end_callback(OnLim callback){
    fEnd = callback;
}

void parse(const std::string str){
    if(fBegin != nullptr) fBegin();
    size_t pos_1 = 0;
    size_t found;
    std::string token;

    while((found = str.find_first_of(" \n\t", pos_1))!=std::string::npos){
        token = str.substr(pos_1, found-pos_1);
        if ((isdigit(token[0]))&&(fNumber!= nullptr)){
            int number = atoi(token.c_str());
            fNumber(number);
        }
        else if (fLetter!=nullptr) fLetter(token);
        pos_1 = str.find_first_not_of(" \n\t", found);
    }
    if(fEnd != nullptr) fEnd();
}