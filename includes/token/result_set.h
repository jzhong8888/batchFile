#ifndef RESULT_SET_H
#define RESULT_SET_H

#include <iostream>
#include <vector>
#include "token.h"
#include "constant.h"


using namespace std;

class Result_Set: public Token{
    public:
    Result_Set():Token("Result_Set", RESULT_SET){
        record_nums.clear();
    }

    Result_Set(vector<long> records){
        record_nums = records;
    }

    void Print(ostream& outs = cout) const{
        outs << "Printing Reselt_Set :";
        for (int i = 0; i < record_nums.size(); i++){
            outs << record_nums[i] << "|";
        }
    }

    TOKEN_TYPES TypeOf(){return RESULT_SET;}

    vector<long> vector_of_long_only(){return record_nums;}


    private:
    vector<long> record_nums;
};
#endif