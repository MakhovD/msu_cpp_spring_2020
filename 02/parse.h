#include <iostream> 
#include <string> 
#include <cstddef>

using OnLetter = void (*)(std::string token);  
using OnLim = void (*)();
using OnNumber = void (*)(int token);

void register_on_number_callback(OnNumber callback);

void register_on_letter_callback(OnLetter callback);

void register_on_begin_callback(OnLim callback);

void register_on_end_callback(OnLim callback);

void parse(const std::string str);// OnNumber fNumber, OnLetter fLetter, OnLim fBegin, OnLim fEnd);

