//
// Created by Yuval on 01/01/2018.
//

#ifndef HASHTABLE_LIST_H
#define HASHTABLE_LIST_H

#include <assert.h>
#include "Exceptions.h"

template<class T>
class List {
    class Node {
        T data;
        Node *next;
        Node *previous;

        Node() {
            next = NULL;
            previous = NULL;
        }

        Node(T data, Node *next, Node *previous) : data(data),
                                                   next(next),
                                                   previous(previous) {}

        bool operator==(const Node &node) const {
            return (next == node.next && previous == node.previous &&
                    data == node.data);
        }

        bool operator!=(const Node &node) const {
            return !((*this) == node);
        }

        friend class Iterator;

        friend class List;
    };
    Node *head;
    Node *tail;
    int size;
    template <class Compare>
    bool bubble(int n, Compare& compare) {
        bool swapped = false;
        Iterator first_elem = begin();
        Iterator second_elem(this,first_elem.current->next);
        for(int i=1; i<n; i++) {
            assert(size >= n);
            if(compare( second_elem.operator*(),first_elem.operator*())) {
                first_elem.swap(second_elem);
                swapped = true;
            }
            first_elem++;
            second_elem++;
        }
        return swapped;
    }
public:
    class Iterator {
        const List *list_p;
        Node *current;

        Iterator(const List *list_p, const Node *const node_p) : list_p(list_p) {
            current = list_p->head->next;
            while (current != node_p && current != list_p->tail->next)                      //check this out
                current = current->next;
        }

        void swap(Iterator& param) {
            const T temp = current->data;
            current->data = param.current->data;
            param.current->data = temp;
        }
        template <class Compare>
        friend bool bubble(int n, Compare& compare);
        friend class List;

    public:

        Iterator operator=(const Iterator &iterator){
            current=iterator.current;
            list_p=iterator.list_p;
            return *this;
        }

        Iterator &operator++() {
            assert(current != list_p->tail->next);
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            //assert(current != list_p->tail->next && current != NULL);
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator &operator--() {
            assert(current != list_p->tail && current != NULL);
            current = current->previous;
            return *this;
        }

        Iterator operator--(int) {
            assert(current != list_p->head);
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator &iterator) const {
            assert(list_p == iterator.list_p);
            return current == iterator.current;
        }

        bool operator!=(const Iterator &iterator) const {
            return !(*this == iterator);
        }

        T &operator*() const {
            if (current == NULL || current == list_p->head ||
                current == list_p->tail->next) {
                throw ElementDoesntExist();
            }
            return current->data;
        }
        template<class Compare>
        bool bubble(List<T> &list, const int n, Compare &compare) {
            bool swapped = false;
            typename List<T>::Iterator first_elem = list.begin();
            typename List<T>::Iterator second_elem = list.begin()++;
            for (int i = 1; i < n; i++) {
                assert(list.getSize() >= n);
                if (compare(first_elem.operator*(), second_elem.operator*())) {
                    first_elem.swap(second_elem);
                    swapped = true;
                }
                first_elem++;
                second_elem++;
            }
            return swapped;
        }

    };
    List() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        head->previous = NULL;
        tail->previous = head;
        tail->next = NULL;
        size = 0;
    }

    List(const List &list) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        head->previous = NULL;
        tail->previous = head;
        tail->next = NULL;
        size = 0;
        for (Iterator iterator = list.begin();
             iterator != list.end(); iterator++) {
            insert(iterator.current->data);
        }
    }

    ~List() {
        for (Iterator iterator = begin(); iterator != end(); iterator=begin()) {
            remove(iterator);
        }
        delete (tail);
        delete (head);
    }
    Iterator begin() const {
        return Iterator(this, this->head->next);
    }

    Iterator end() const {
        return Iterator(this, this->tail);
    }
    void insert(const T &data, const Iterator &iterator) {
        if (iterator.list_p != this || iterator == ++end()) {
            throw ElementDoesntExist();
        }
        Node *new_node = new Node(data, iterator.current,
                                  iterator.current->previous);
        iterator.current->previous->next=new_node;
        iterator.current->previous = new_node;
        size++;
    }

    void insert(const T &data) {
        insert(data, end());
    }

    void remove(Iterator &iterator) {
        if (iterator.list_p != this || iterator.current == tail) {
            throw ElementDoesntExist();
        }
        Node *temp_next = iterator.current->next;
        Node *temp_prev = iterator.current->previous;
        delete (iterator.current);
        temp_prev->next = temp_next;
        temp_next->previous = temp_prev;
        iterator.current = tail;
        size--;
    }



    int getSize() {
        return size;
    }



    template<class Compare>
    void sort(const Compare &compare) {
        bool not_sorted = true;
        int len = size;
        while (len > 1 && not_sorted) {
            not_sorted = bubble(len--, compare);
        }
    }

    Iterator find(const T& x) {
        for (Iterator i = (*this).begin(); i != (*this).end(); i++) {
            if (*(i.operator*()) == *x) {
                return i;
            }
        }
        throw ElementDoesntExist();
    }

    void DeleteElements();
};
template <class T>
void List<T>::DeleteElements() {
    for (Iterator i = begin(); i != end(); i++){
        delete(i.current->data);
    }
}

#endif //HASHTABLE_LIST_H
