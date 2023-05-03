#ifndef RPN_H
#define RPN_H
#include "../token/token.h"
#include "../token/tokenstr.h"
#include "../token/relational.h"
#include "../token/result_set.h"
#include "../token/logical.h"
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../table/typedefs.h"
#include "../table/table.h"
#include "../token/operator.h"
#include <iostream>
#include <cmath>
using namespace std;

class RPN
{
    public:
        RPN(){

        }

        RPN(Queue<Token*>const& queue){
            queue_rpn = queue;
        }

        void set_input(Queue<Token*>const& queue){
            queue_rpn = queue;
        }

        vector<long> evaluate(Map<string, long> table_field_map, vector<MMap<string, long> > table_indicies_mmap){
            // two variables to store the strings.
            string str1, str2;
            vector<long> recno;
            vector<long> hold1, hold2;
            Token* a;
            Token* b;
            //cout << "queue_rpn size: " << queue_rpn.size() << endl;

            while (!queue_rpn.empty()){
                // pop out from the queue.
                Token* walker = queue_rpn.pop();
                switch(walker->TypeOf()){
                    case TOKENSTRING:
                    {
                        //cout << "token string here." << endl;
                        stack_rpn.push(walker);
                        break;
                    }

                    case OPERATOR:
                    {
                        //cout << "operator here." << endl;
                        if (stack_rpn.size()>=2){
                        a = stack_rpn.pop();
                        b = stack_rpn.pop();
                        //cout << "stack size: " << stack_rpn.size() << endl;
                        Operator* op = static_cast<Operator*>(walker);
                        Token* tokenPtr = op->evaluate(a, b, table_field_map, table_indicies_mmap);
                        stack_rpn.push(tokenPtr);
                        //cout << "stack size (after push): " << stack_rpn.size() << endl;
                        } 
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }

            assert(stack_rpn.size()==1);
            result = static_cast<Result_Set*>(stack_rpn.pop())->vector_of_long_only();
            return result;
        }


    private:
    vector<long> result;
    Stack<Token*>stack_rpn;
    Queue<Token*>queue_rpn;


};


#endif 