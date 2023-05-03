#include <iostream>
#include <cassert>
#include "shunting_yard.h"


using namespace std;

ShuntingYard::ShuntingYard(){

}

ShuntingYard::ShuntingYard(Queue<Token*>const& queue){
    queue_input = queue;
}

Queue<Token*> ShuntingYard::postfix(){
    // The output/result
    Queue<Token*> queue_postfix;
    Token* walker=queue_input.pop();
    Token* hold;

    while(walker!=nullptr){
        switch(walker->TypeOf()){
            case TOKENSTRING:
            {
                //cout << "tokenstring here." << endl;
                queue_postfix.push(walker);
                break;
            }
            case OPERATOR:
            {
                //cout << "operator here." << endl;
                while((!stack_operator.empty() && stack_operator.top()->TypeOf() != LPAREN) && (
                (static_cast<Operator*>(stack_operator.top())->get_prec() >= static_cast<Operator*>(walker)->get_prec())))
                {
                    //cout << "precedence of top: " << static_cast<Operator*>(stack_operator.top())->get_prec() << endl;
                    //cout << "precedence of walker: " << static_cast<Operator*>(walker)->get_prec() << endl;
                    Token* o2 = stack_operator.pop();
                    queue_postfix.push(o2);
                }
                stack_operator.push(walker);
                break;
            }
            case LPAREN:
            {
                stack_operator.push(walker);
                break;
            }
            case RPAREN:
            {
                while(stack_operator.top()->TypeOf()!=LPAREN)
                {
                    assert(stack_operator.size()!=0);
                    queue_postfix.push(stack_operator.pop());
                }
                assert(stack_operator.top()->TypeOf()==LPAREN);
                stack_operator.pop();
                break;
            }
            default:
            break;
        }
        if (queue_input.empty()){
            break;
        }
        walker=queue_input.pop();
    }

    // at the end, push all the elements left in the stack into the result/output queue.
    int size=stack_operator.size();
    for(int i=0;i<size; i++){
        hold=stack_operator.pop();
        queue_postfix.push(hold);
    }

    //cout << "postfix: " << queue_postfix << endl;
    return queue_postfix;
}

Queue<Token*> ShuntingYard::ShuntingYard::postfix(Queue<Token*>const& queue){
    queue_input = queue;
    return postfix();
}

void ShuntingYard::infix(Queue<Token*>const& queue){
    queue_input = queue;
}