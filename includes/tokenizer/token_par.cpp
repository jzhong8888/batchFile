#include "token_par.h"

Token_Par::Token_Par()
{
    _token=" ";
    _type=0;
}

Token_Par::Token_Par(string str, int type)
{
    _token=str;
    _type=type;
}

ostream& operator <<(ostream& outs, const Token_Par& t)
{
    outs<< "   |"<<t.token_str()<<"|"<<endl;
    return outs;
}

int Token_Par::type() const
{
    return _type;
}

string Token_Par::type_string() const
{
    if(_type==1)
    {
        return "ALPHA";
    }
    else if((_type==2)||(_type==7))
    {
        return "DOUBLE";
    }
    else if(_type==3)
    {
        return "OPERATOR";
    }
    else if(_type==4)
    {
        return "SPACE";
    }
    else if(_type==5)
    {
        return "PUNC";
    }
    else if(_type==10)
    {
        return "STRING";
    }
    else
        return "UNKNOWN";
}

string Token_Par::token_str() const
{
    return _token;
}