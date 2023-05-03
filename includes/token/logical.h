#ifndef LOGICAL_H
#define LOGICAL_H

#include <iostream>
#include <vector>
#include "token.h"
#include "constant.h"
#include "operator.h"
#include "../table/table.h"
#include "result_set.h"

using namespace std;

class Logical: public Operator
{
    public:
        Logical(string l):Operator(l){
            _l= l;
            _precedence = get_prec();
        }


        void Print(ostream& outs=cout) const{
            outs<<"Printing Logical :";
            outs<<"["<<_l<<"]";
        }

        int get_prec(){
            if (_l == "and"){
                return 2;
            }
            else if (_l == "or"){
                return 1;
            }
            else{
                return -1;
            }
        }

        TOKEN_TYPES TypeOf(){return OPERATOR;}

        int precedence(){return get_prec();}

        string string_only(){return _l;}

        Token* evaluate(Token* a, Token* b, Map<string, long> table_field_map, vector<MMap<string, long> > table_indicies_mmap){
            if(_l == "and"){
                vector<long> record1 = static_cast<Result_Set*>(a)->vector_of_long_only();
                vector<long> record2 = static_cast<Result_Set*>(b)->vector_of_long_only();
                vector<long> recno = vector_intersection(record1, record2);
                Token* vector_record = new Result_Set(recno);
                return vector_record;
            }
            else if (_l == "or"){
                vector<long> record1 = static_cast<Result_Set*>(a)->vector_of_long_only();
                vector<long> record2 = static_cast<Result_Set*>(b)->vector_of_long_only();
                vector<long> recno = vector_union(record1, record2);
                Token* vector_record = new Result_Set(recno);
                return vector_record;
            }
        }
        
    private:
        string _l;
        int _precedence;
};


#endif