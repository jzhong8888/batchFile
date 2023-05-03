#ifndef RIGHT_PAREN_H
#define RIGHT_PAREN_H
#include<iostream>
#include"token.h"
#include "constant.h"
using namespace std;

class RightParen : public Token
{
    public:
        RightParen():Token(")", RPAREN){
            _rp = ")";
        }

        RightParen(string rp):Token(rp, RPAREN){
        if (rp == ")" || rp == "]" || rp == "}"){
            _rp = rp;
        }
        else{
            _rp = ")";
        }
    }

        void Print(ostream& outs=cout) const{
            outs<<"Printing Rightparen: ";
            outs<<"["<<_rp<<"]";
        }

        TOKEN_TYPES TypeOf(){return RPAREN;}
        
    private:
        string _rp;
};

#endif 