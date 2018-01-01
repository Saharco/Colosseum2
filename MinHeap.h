//
// Created by sahar on 29/12/2017.
//
#ifndef COLOSSEUM2_MINHEAP_H
#define COLOSSEUM2_MINHEAP_H

#include <exception>
#include "Exceptions.h"

template<class T>
class Comparator {
public:
    virtual ~Comparator() {};

    virtual int operator()(T a, T b) = 0;
};

template <class T>
class MinHeap {
    T* array;
    int size;
    int max_size;
    const int expand_factor;
    Comparator<T>& comparator;

    void swap (T& e1, T& e2) {
        T temp(e1);
        e1 = e2;
        e2 = temp;
    }

    void siftDown(int i) {
        int left_child = 2*i + 1;
        int right_child = 2*i + 2;
        int min_i = i;
        if(left_child >= size)
            return;
        if(comparator(array[i], array[left_child]) > 0)
            min_i = left_child;
        if((right_child < size) && comparator(array[min_i], array[right_child]) > 0) {
            min_i = right_child;
        }
        if(i != min_i) {
            swap(array[i], array[min_i]);
            siftDown(min_i);
        }
    }

    void siftUp(int i) {
        if(i == 0) {
            return; //Reached the root
        }
        int parent_i = (i-1)/2;
        if(comparator(array[parent_i], array[i]) > 0) {
            swap(array[i], array[parent_i]);
            siftUp(parent_i);
        }
    }


    void sendToRoot(int i) {
        if(i == 0) {
            return; // Reached the root
        }
        swap(array[i], array[(i-1)/2]);
        sendToRoot((i-1)/2);
    }

    void expand() {
        max_size = size * expand_factor;
        T* new_array = new T[max_size];
        for(int i = 0; i<size; i++) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }
public:
    MinHeap(T* elements, int length, Comparator<T>& comparator) :
            comparator(comparator), expand_factor(2), size(length) {
        max_size = size * expand_factor;
        array = new T[max_size];
        for(int i = 0; i<length; i++) {
            array[i] = elements[i];
        }
        for(int i = (size-1)/2; i>=0; i--) {
            siftDown(i);
        }
    }

    ~MinHeap() {
        delete[] array;
    }

    void insert(const T& element) {
        if(size == max_size) {
            expand(); //Array ran out of space: expand it
        }
        array[size] = element;
        siftUp(size++);
    }

    T findMin() const {
        return array[0];
    }

    void deleteMin() {
        if(size == 0) {
            return;
        }
        array[0] = array[--size]; //Rightmost leaf becomes the new root - size of the tree has been decreased
        siftDown(0);
    }

    void deleteNode(int index) {
        if(index>=size) {
            return;
        }
        sendToRoot(index);
        deleteMin();
        siftDown(0);
    }

    /*
     * Delet dis
     */
    void printArray() {
        for(int i = 0; i<size; i++) {
            std::cout << array[i] << std::endl;
        }
    }
};


#endif //COLOSSEUM2_MINHEAP_H
