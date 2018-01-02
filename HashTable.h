#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <exception>
#include "List.h"
template<class T>
class HashTable {
    List<T> **table;
    int table_length;
    int num_elements;
    int expand_factor;
    int h(const T& x);          //NEED CHANGES
    void expand();
    typename List<T>::Iterator find(const T& x);
public:
    HashTable(int initial_size,int expand_factor);
    void insert(const T& x);
    void deleteElement(const T& x);
    bool member(const T& x);
};
template <class T>
int HashTable<T>::h(const T &x) {
    return x%table_length;
}
template <class T>
void HashTable<T>::expand() {
    List<T>** new_table=new List<T> *[table_length*expand_factor];
    for(int i=0;i<table_length*expand_factor;i++){
        new_table[i]= new List<T>();
    }
    table_length=table_length*expand_factor;
    for(int i=0;i<table_length/expand_factor;i++){
            int size;
            for(typename List<T>::Iterator it=table[i]->begin();it!=table[i]->end();it++){
                new_table[h(*it)]->insert(*it);
            }
            delete(table[i]);
    }
    delete[] table;
    table=new_table;
}
template<class T>
HashTable<T>::HashTable(int initial_size, int expand_factor) : table_length(initial_size),
                                                            expand_factor(expand_factor),
                                                            num_elements(0),
                                                            table(new List<T>*[initial_size]){
    for (int i = 0; i < initial_size; ++i) {
        table[i] = new List<T>();
    }
}

template <class T>
void HashTable<T>::insert(const T &x) {
    if(num_elements>table_length){
        expand();
    }
    int position=h(x);
    try{
        find(x);
    }catch(const ElementDoesntExist& e){
        table[position]->insert(x);
        num_elements++;
        return;
    }
        throw ElementAlreadyExists();
}

template <class T>
void HashTable<T>::deleteElement(const T &x) {
    int position=h(x);
    typename List<T>::Iterator it=find(x);
    table[position]->remove(it);
}

template <class T>
bool HashTable<T>::member(const T &x) {
    int position=h(x);
    try {
        typename List<T>::Iterator it = find(x);
    }catch(const ElementDoesntExist& e){
        return false;
    }
    return true;
}
template <class T>
typename List<T>::Iterator HashTable<T>::find(const T &x) {
    int position=h(x);
    typename List<T>::Iterator result = table[position]->find(x);
    return result;
}

#endif //HASHTABLE_HASHTABLE_H
