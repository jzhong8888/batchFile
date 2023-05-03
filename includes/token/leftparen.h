#ifndef LEFT_PAREN_H
#define LEFT_PAREN_H
#include<iostream>
#include<cmath>
#include"token.h"
#include "constant.h"
using namespace std;

class LeftParen: public Token{
    public:
    LeftParen():Token("(", LPAREN){
        _lp ="(";
    }

    LeftParen(string lp):Token(lp, LPAREN){
        if (lp == "(" || lp == "[" || lp == "{"){
            _lp = lp;
        }
        else{
            _lp = "(";
        }
    }

    void Print(ostream& outs=cout) const{
        outs<<"Printing LeftParen: ";
        outs<<"["<<_lp<<"]";
    }


    TOKEN_TYPES TypeOf(){return LPAREN;}

    private:
    string _lp;
};


#endif