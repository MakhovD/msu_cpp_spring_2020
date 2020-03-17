#include "parse.h"

int Begin1(){
    return 1;
}

void Begin(){
    std::cout << "start parse ";
}

void End(){
    std::cout << " finish parse\n";
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
    register_on_end_callback(End);

    parse("123 abc\n4567\tHello");

    register_on_begin_callback(Begin);
    parse("123 abc\n4567\tHello");
    return 0;
}