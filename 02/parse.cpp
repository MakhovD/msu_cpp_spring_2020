#include "parse.h"

static OnNumber fNumber;
static OnLetter fLetter;
static OnLim fBegin;
static OnLim fEnd;

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

void parse(const std::string str){//, OnNumber fNumber, OnLetter fLetter, OnLim fBegin, OnLim fEnd){
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