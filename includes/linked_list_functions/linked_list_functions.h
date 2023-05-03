#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include <iostream>
#include <cassert>
#include "../node/node.h"

using namespace std;

//Linked List General Functions:
    template <typename ITEM_TYPE>
    void _print_list(node<ITEM_TYPE>* head);

    //recursive fun! :)
    template <typename ITEM_TYPE>
    void _print_list_backwards(node<ITEM_TYPE> *head);

    //return ptr to key or NULL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key);


    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this);

    //insert after ptr
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this);

    //remove the first node
    template <typename ITEM_TYPE>
    ITEM_TYPE _remove_head(node<ITEM_TYPE>*& head);

    //insert before ptr
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this);

    //ptr to previous node
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this);

    //delete, return item
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this);

    //duplicate the list...
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

    //duplicate list and return the last node of the copy
    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src);


    //delete all the nodes
    template <typename ITEM_TYPE>
    void _clear_list(node<ITEM_TYPE>*& head);

    //_item at this position
    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>*&head);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //      Sorted List Routines. order: 0: ascending, order: other: descending
    //                              Assume a Sorted List
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true);

    //insert or add if a dup
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true);
    //node after which this item goes order: 0 ascending
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending=true);
    //Last Node in the list
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* &head);            //never use this function.



    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this){

        node<ITEM_TYPE>* temp;
        temp = new node<ITEM_TYPE>(insert_this);
        temp->_next = head;
        head = temp;
        return head;
    }

    template <typename ITEM_TYPE>
    void _print_list(node<ITEM_TYPE>* head){
        node<ITEM_TYPE>* walker;
        walker = head;
        while (walker != nullptr){
            cout << "[" << walker->_item << "]-> ";
            walker = walker->_next;
        }
        cout << "|||";
    }

    template <typename ITEM_TYPE>
    void _print_list_backwards(node<ITEM_TYPE> *head){
        node<ITEM_TYPE>* walker;
        walker = _last_node(head);
        cout << "||| <-";
        cout << "[" << walker->_item << "]";
        while (walker != head){
            walker = _previous_node(head, walker);
            cout << " <-[" << walker->_item << "]";
        }
    }



    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key){
        node<ITEM_TYPE>* walker;
        walker = head;
        while(walker != nullptr){
            if ((walker->_item) == key){
            return walker;
            }
        walker = walker->_next;
        }
        return nullptr;
    }

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this){
        node<ITEM_TYPE>* insert;
        insert = new node<ITEM_TYPE>(insert_this);
        insert->_next = after_this->_next;
        after_this->_next = insert;
        return insert;
    }

    template <typename ITEM_TYPE>
    ITEM_TYPE _remove_head(node<ITEM_TYPE>*& head){
        assert (head != nullptr);
        node<ITEM_TYPE>* remove;
        remove = head;
        head = head->_next;
        ITEM_TYPE item = remove->_item;
        delete remove;
        return item;
    }

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this){
        bool found = false;
        node<ITEM_TYPE>* walker;
        
        walker = head;
        while (walker != nullptr && found == false){
            if (walker->_next == prev_to_this){
                found = true;
            }
            else{
            walker = walker->_next;
            }
        }
        assert (found == true);

        if (prev_to_this == head){
            return nullptr;
        }

        walker = head;
        while (walker != nullptr){
        if (walker->_next == prev_to_this){
            return walker;
            }
        walker = walker->_next;
        }
    }

    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this){
        
        ITEM_TYPE del;
        
        if (delete_this == head){
            del = _remove_head(head);
            return del;
        }
        else{
            node<ITEM_TYPE>* previous;
            previous = _previous_node(head, delete_this);
            previous->_next = delete_this->_next;
            del = delete_this->_item;
            delete delete_this;
            return del;
        }
    }

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this){
        if (before_this == head){
            return _insert_head(head, insert_this);
        }
        else{
            node<ITEM_TYPE>* insert = new node<ITEM_TYPE>(insert_this, before_this);
            node<ITEM_TYPE>* previous;
            previous = _previous_node(head, before_this);
            previous->_next = insert;
            return insert;
        }
    }

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
        if (!head) return nullptr;
        node<ITEM_TYPE>* copy = new node<ITEM_TYPE>(head->_item);
        node<ITEM_TYPE>* w_s = head;
        node<ITEM_TYPE>* w_d = copy;
        while((w_s->_next) != nullptr){
            w_s = w_s->_next;
            w_d->_next = new node<ITEM_TYPE>(w_s->_item);
            w_d = w_d->_next;
        }
        return copy;
    }

    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src){
        dest = _copy_list(src);
        node<T>* rear;
        rear = _last_node(dest);
        return rear;
    }

    template <typename ITEM_TYPE>
    void _clear_list(node<ITEM_TYPE>*& head){
        while (head != nullptr){
            _remove_head(head);
        }
    }

    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
        node<ITEM_TYPE>* walker;
        walker = head;
        for (int i = 0; i < pos; i++){
            walker = walker->_next;
        }
        return walker->_item;
    }

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>*&head){
        if (!head) return nullptr;
        node<ITEM_TYPE>* walker;
        walker = head;
        while (walker->_next != nullptr){
            walker = walker->_next;
        }
        return walker;
    }


    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending){
        node<int>* leader = head->_next;
        node<int>* follower = head;
        if (ascending == true){
            while(leader != nullptr){
                if (item < leader->_item){
                    return follower;
                }
                leader = leader->_next;
                follower = follower->_next;
            }
            return follower;
        }
        else {
            while (leader != nullptr){
                if (item > (leader->_item)){
                    return follower;
                }
                leader = leader->_next;
                follower = follower->_next;
            }
            return follower;
        }
    }


    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
        if (head == nullptr){
            head = _insert_head(head, item);
            return head;
        }
        if (ascending == true){
            if (item < head->_item){
                head = _insert_head(head, item);
                return head;
            }
            else{
                node<int>* mark = _where_this_goes(head, item);
                return _insert_after(head, mark, item);
            }
        }
        else{
            if (item > (head->_item)){
                head = _insert_head(head, item);
                return head;
            }
            else{
                ascending = false;
                node<int>* mark = _where_this_goes(head, item, ascending);
                return _insert_after(head, mark, item);
            }
        }
    }

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
        
        if (head == nullptr){
            head = _insert_head(head, item);
            return head;
        }
        if (ascending == true){
            if (item < head->_item){
                head = _insert_head(head, item);
                return head;
            }
            else{
                node<int>* mark = _where_this_goes(head, item);
                mark->_item = mark->_item + item;
                return mark;
            }
        }
        else{
            if (item > (head->_item)){
                head = _insert_head(head, item);
                return head;
            }
            else{
                ascending = false;
                node<int>* mark = _where_this_goes(head, item);
                mark->_item = mark->_item + item;
                return mark;
            }
        }

    }
    


#endif