#include "parse.h"
#include <iostream>
//test1 functions
void Begin(){
    std::cout << "start parse ";
}

void End(){
    std::cout << " finish parse";
}

void onNumberFound(const char* n){
        std::cout << n << "||";
}

void onLetterFound(const char* n){
        std::cout << n << "??";
}
//test2 functions
void Begin1(){
    std::cout << "\nstart parse\n";
}
void End1(){
    std::cout << "finish parse\n";
}
void onNumberFound1(const char* n){
        std::cout << "number: " << n << std::endl;
}
void onLetterFound1(const char* n){
        std::cout << "string: " << n << std::endl;
}

int main(){
    parse("123 abc\n4567\tHello", onNumberFound, onLetterFound, Begin, End);
    // start parse 123||abc??4567||Hello?? finish parse

    parse("Hello\n world 19999\t500", onNumberFound1, onLetterFound1, Begin1, End1);
    /*start parse
    string: Hello
    string: world
    number: 19999
    number: 500
    finish pars*/
    return 0;
}