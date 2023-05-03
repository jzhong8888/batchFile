#ifndef TOKEN_PAR_H
#define TOKEN_PAR_H
#include <iostream>
#include <string>
using namespace std;

class Token_Par
{
public:
    Token_Par();
    Token_Par(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token_Par& t);
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
};

#endif 