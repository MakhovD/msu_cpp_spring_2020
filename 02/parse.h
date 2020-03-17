#include <iostream> 
#include <string> 
#include <cstddef>

using OnLetter = void (*)(std::string token);  
using OnLim = void (*)();
using OnNumber = void (*)(int token);

void parse(std::string str, OnNumber fNumber, OnLetter fLetter, OnLim fBegin, OnLim fEnd);

