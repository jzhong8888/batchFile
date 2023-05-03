#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include <string>
#include "token.h"
#include "../table/table.h"

using namespace std;

class Operator : public Token
{
public:
    Operator(string op):Token(op, OPERATOR){
        _op = op;
        _precedence = get_prec();
    }

    virtual int get_prec(){
        if (_op == ">" || _op == "<" || _op == ">=" || _op == "<=" || _op == "="){
            return 3;
        }
        else if (_op == "and"){
            return 2;
        }
        else if (_op == "or"){
            return 1;
        }
        else{
            return 0;
        }
    }

    virtual int precedence(){return _precedence;}

    virtual void Print(ostream& outs=cout) const{
        outs<<"[" << _op << "]";
    }

    virtual TOKEN_TYPES TypeOf(){return OPERATOR;}

    string string_only(){return _op;}

    virtual Token* evaluate(Token* a, Token* b, Map<string, long> table_field_map, vector<MMap<string, long> > table_indicies_mmap){
        cout << "This is not correct!!!" << endl;
        Token* empty;
        return empty;
    }

private:
    int _precedence;
    string _op;
};

#endif