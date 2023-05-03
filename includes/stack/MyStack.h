#ifndef MY_STACK_H
#define MY_STACK_H
#include <iostream>
#include <cassert>
#include "../linked_list_functions/linked_list_functions.h"
#include "../node/node.h"

using namespace std;

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = NULL;}            //default ctor
        Iterator(node<ITEM_TYPE>* p){
            _ptr = p;
        }      //Point Iterator to where
               //p is pointing to

        ITEM_TYPE operator *(){
            assert(_ptr);
            return _ptr->_item;
        }    //dereference operator

        bool is_null(){return _ptr == NULL;}            //true if _ptr is NULL
        
        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr;}

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr;}


        Iterator& operator++(){
            _ptr = _ptr->_next;
            return *this;
        }                                              //member operator:++it
                                                       //or ++it = new_value

        friend Iterator operator++(Iterator& it, int unused){        //friend operator: it++
            assert(it._ptr!=NULL);
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe);
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

template <class ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(){
    _top = nullptr;
    _size = 0;
}

template <class ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe){
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <class ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack(){
    _clear_list(_top);
}

template <class ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS){
    if (this == &RHS){
        return *this;
    }
    _clear_list(_top);
    _top = _copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}

template <class ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top(){
    return _top->_item;
}

template <class ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty(){
    if (_top == nullptr){
        return true;
    }
    else{
        return false;
    }
}

template <class ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item){
    _top = _insert_head(_top, item);
    _size++;
}

template <class ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop(){
    ITEM_TYPE pop = _remove_head(_top);
    _size--;
    return pop;
}

template <class T>
ostream& operator<<(ostream& outs, const Stack<T>& printMe){
    outs << "Stack:";
    _print_list(printMe._top);
    return outs;
}

template <class T>
typename Stack<T>::Iterator Stack<T>::begin() const{
    Iterator result(_top);
    return result;
}

template <class T>
typename Stack<T>::Iterator Stack<T>::end() const{
    Iterator result(nullptr);
    return result;
}

#endif