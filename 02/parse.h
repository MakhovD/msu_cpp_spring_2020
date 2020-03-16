#include <string.h>
#include <ctype.h>
#include <iostream>

using OnToken = void (*)(const char* token);  
using OnLim = void (*)();

void register_token_callback(const char* word, OnToken onNumber, OnToken onLetter);

void parse(const char* text, OnToken onNumber, OnToken onLetter, OnLim onBegin, OnLim onEnd);

