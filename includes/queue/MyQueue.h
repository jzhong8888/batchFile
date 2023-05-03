#ifndef MY_QUEUE_H
#define MY_QUEUE_H
#include <iostream>
#include <cassert>
#include "../linked_list_functions/linked_list_functions.h"
#include "../node/node.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator(){_ptr = nullptr;}                 //default ctor
        Iterator(node<T>* p){
            _ptr = p;
        }                             //Point Iterator to where
        //...                        //  p is pointing to
        
        T &operator*(){
            assert(_ptr);
            return _ptr->_item;
        }     

        T *operator->(){
            assert(_ptr);
            T* p;
            *p = _ptr->_item;
            return p;
        }    

        bool is_null(){
            if (_ptr == nullptr){
                return true;
            }
            else return false;
        } 

        friend bool operator!=(const Iterator &left, const Iterator &right){
            if (left._ptr != right._ptr){
                return true;
            }
            else return false;
        } //true if left != right     

        friend bool operator==(const Iterator &left, const Iterator &right){
            if (left._ptr == right._ptr){
                return true;
            }
            else return false;
        } //true if left == right

        Iterator &operator++(){
            _ptr = _ptr->_next;
            return *this;
        }     

        friend Iterator operator++(Iterator &it, int unused){
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }          //friend operator: it++                             
 
    private:
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <class T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template <class T>
Queue<T>::~Queue(){
    _clear_list(_front);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if (this == &RHS){
        return *this;
    }
    _clear_list(_front);
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

template <class T>
bool Queue<T>::empty(){
    if (_front == nullptr){
        return true;
    }
    else{
        return false;
    }
}

template <class T>
T Queue<T>::front(){
    return _front->_item;
}

template <class T>
T Queue<T>::back(){
    return _rear->_item;
}

template <class T>
void Queue<T>::push(T item){
    if (_front == nullptr){
        _front = _insert_head(_front, item);
        _rear = _front;
        _size++;
    }
    else{
        _rear = _insert_after(_front, _rear, item);
        _size++;
    }
}

template <class T>
T Queue<T>::pop(){
    T pop = _remove_head(_front);
    _size--;
    return pop;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    Iterator result(_front);
    return result;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() const{
    Iterator result(nullptr);
    return result;
}

template <class T>
void Queue<T>::print_pointers(){
    _print_list(_front);
}

template<typename TT>
    ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        outs << "Queue:Head->";
        _print_list(printMe._front);
        return outs;
    }

#endif