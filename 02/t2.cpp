#include "parse.h"


void Begin(){
    std::cout << "start parse ";
}

void End(){
    std::cout << " finish parse";
}

void onNumberFound(int n){
        std::cout << n << "||";
}

void onLetterFound(std::string n){
        std::cout << n << "??";
}

int main(){
    register_on_number_callback(onNumberFound);
    register_on_letter_callback(onLetterFound);
    register_on_begin_callback(Begin);
    register_on_end_callback(End);
    parse("123 abc\n4567\tHello");
    return 0;
}