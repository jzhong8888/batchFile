#ifndef RELATIONAL_H
#define RELATIONAL_H

#include <iostream>
#include <vector>
#include "token.h"
#include "constant.h"
#include "operator.h"
#include "../table/table.h"
#include "result_set.h"
#include "tokenstr.h"

using namespace std;

class Relational: public Operator
{
    public:
        Relational(string r):Operator(r){
            _r = r;
            _precedence = get_prec();
        }

        void Print(ostream& outs=cout) const{
            outs<<"Printing Relational :";
            outs<<"["<<_r<<"]";
        }

        int get_prec(){
            return 3;
        }

        TOKEN_TYPES TypeOf(){return OPERATOR;}

        int precedence(){return get_prec();}

        string string_only(){return _r;}

        Token* evaluate(Token* a, Token* b, Map<string, long> table_field_map, vector<MMap<string, long> > table_indicies_mmap){
            string string_a = static_cast<TokenStr*>(a)->string_only();
            string string_b = static_cast<TokenStr*>(b)->string_only();
            vector<long> recno = get_recno(string_b, _r, string_a, table_field_map, table_indicies_mmap);
            Token* vector_record = new Result_Set(recno);
            return vector_record;
        }



        vector<long> get_recno(string field, string condition, const string& entry, Map<string, long> table_field_map, vector<MMap<string, long> > table_indicies_mmap){
            vector <long> recno;
            if(condition == "="){
                // use field map to find the index of the field first.
                // then, use the field index and the entry string to find the record number.
                recno = table_indicies_mmap[table_field_map[field]][entry];
            }
            else if(condition == ">"){ 
                // make the Iterator it to point to the upper bound of the entry.
                MMap<string, long>::Iterator it = (table_indicies_mmap[table_field_map[field]].upper_bound(entry));
                //use a while loop to store all the record numbers after upper bound.
                while(it != table_indicies_mmap[table_field_map[field]].end())
                {
                    recno+=(*it).value_list;
                    it++;
                }
            }
            else if(condition == "<"){
                // set the Iterator begin to the very first Multiple Map.
                MMap<string,long>::Iterator begin = table_indicies_mmap[table_field_map[field]].begin();
                // set the Iterator end to the lower bound of the entry.
                MMap<string,long>::Iterator end=(table_indicies_mmap[table_field_map[field]].lower_bound(entry));
                // store the record numbers into recno from begin to end not including end.
                for(MMap<string,long>::Iterator it=begin; it!=end; it++)
                {
                    recno+=(*it).value_list;
                }
            }
            else if(condition == ">="){
                // make Iterator it point to the lower bound of the entry. (> or = entry)
                MMap<string,long>::Iterator it=(table_indicies_mmap[table_field_map[field]].lower_bound(entry));
                // use a while loop to store the record numbers into recno.
                while(it != table_indicies_mmap[table_field_map[field]].end())
                {
                    recno+=(*it).value_list;
                    it++;
                }
            }
            else if(condition == "<=")
            {
                // set the Iterator begin to point to the very first Multiple Map.
                MMap<string,long>::Iterator begin = table_indicies_mmap[table_field_map[field]].begin();
                // set the Iterator end to point to the upper bound of the entry (> entry).
                MMap<string,long>::Iterator end=(table_indicies_mmap[table_field_map[field]].upper_bound(entry));
                // store the record numbers into recno from begin to end not including end.
                for(MMap<string,long>::Iterator it=begin; it!=end; it++)
                {
                    recno+=(*it).value_list;
                }
            }
            return recno;
        }

        
    private:
        string _r;
        int _precedence;
};




#endif 