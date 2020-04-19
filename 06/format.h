#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <exception> 
#include <stdlib.h>
#include <iostream>


template<class T>
std::string args_to_str(T&& val)
{
    std::stringstream out;
    out << val;
    return out.str();
}

template<class... ArgsT>
std::string format(const std::string& str, ArgsT&&... args){
    std::stringstream out;

    std::vector<std::string> args_new = {args_to_str(std::forward<ArgsT>(args))... };

    size_t size = str.size();
    size_t args_size = args_new.size();
    bool open = false;
    bool check_closed = false;
    std::string temp;

    for(size_t i = 0; i < size; i++){

        if(check_closed){
            if(str[i] == '}'){
                check_closed = false;
                out << args_new[atoi(temp.c_str())];
                temp.clear();
                continue;
            } else if(std::isdigit(str[i])){
                temp+=str[i];
                continue;
            } else {
                throw std::runtime_error("bracket not closed");
            }
        }

        if(open){
            if(std::isdigit(str[i])){
                if(str[i]-'0' < args_size){
                    temp += str[i];
                    check_closed = true;
                    open = false;
                } else {
                    throw std::runtime_error("not much val in args");
                }
            } else {
                throw std::runtime_error("error in brackets");
            }
        } else {
            if(str[i] == '{'){
                open = true;
            } else if(str[i] == '}'){
                throw std::runtime_error("alone closed bracket");
            } else {
                out << str[i];
            }
        }

    }

    if(open || check_closed){
        throw std::runtime_error("alone bracket in the end of str");
    }

    return out.str();
}