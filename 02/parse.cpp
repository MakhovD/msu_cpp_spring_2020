#include "parse.h"


void register_token_callback(const char* word, OnToken onNumber, OnToken onLetter){
	if (isdigit(word[0])) onNumber(word);
	else onLetter(word);
}

void parse(const char* text, OnToken onNumber, OnToken onLetter, OnLim onBegin, OnLim onEnd){
    onBegin();

    char tx[strlen(text)];
    strcpy(tx,text);
    char* token = strtok (tx," \n\t"); 

    while (token != NULL)
    {
        register_token_callback(token, onNumber, onLetter);
        token = strtok (NULL, " \n\t");
    }
    onEnd();
}
