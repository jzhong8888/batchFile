#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <cmath>

#include "../token/token.h"
#include "../token/tokenstr.h"
#include "../token/relational.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../token/logical.h"
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../rpn/rpn.h"



class ShuntingYard
{
    public:
    ShuntingYard();
    ShuntingYard(Queue<Token*>const& queue);
    void infix(Queue<Token*>const& queue);
    Queue<Token*> postfix(Queue<Token*>const& queue);
    Queue<Token*> postfix();

    private:
    Stack<Token*> stack_operator;
    Queue<Token*> queue_input;
};

#endif