#ifndef TOKENSTR_H
#define TOKENSTR_H

#include<iostream>
#include "token.h"
#include "constant.h"
using namespace std;

class TokenStr: public Token
{
    public:
        TokenStr():Token(string(), TOKENSTRING){
            _str = string();
        }

        TokenStr(string str):Token(str, TOKENSTRING){
            _str = str;
        }

        void Print(ostream& outs=cout) const{
            outs<<"Printing TokenStr :";
            outs<<"["<<_str<<"]";
        }

        TOKEN_TYPES TypeOf(){return TOKENSTRING;}
        
        string string_only(){return _str;}
        
    private:
        string _str;
};




#endif