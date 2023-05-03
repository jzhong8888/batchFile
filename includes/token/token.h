#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "constant.h"
using namespace std;

class Token{
    public:
    Token():_tk_str("UNINITIALIZED"){}
    Token(string Tok_str, TOKEN_TYPES type):_tk_str(Tok_str), _type(type){} 
    
    friend ostream& operator <<(ostream& outs, Token* token_ptr){
        token_ptr->Print(outs);
        return outs;
    }
    friend ostream& operator <<(ostream& outs, const Token& token){
        token.Print(outs);
        return outs;
    }

    // virtual void Print(ostream& outs=cout){
    //     outs << "<" << _tk_str << ">";
    // }

    virtual void Print(ostream &outs) const{
    outs<<"TOKEN Print: DON't ^%#$# call me again!"<<endl;
    }
    
    virtual TOKEN_TYPES TypeOf(){return _type;}
    private:
        string _tk_str;
        TOKEN_TYPES _type;
};

#endif