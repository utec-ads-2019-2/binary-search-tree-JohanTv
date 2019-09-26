#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"

template <typename T> 
class Iterator {
    private:
        Node<T> *current;

    public:
        Iterator() {
            this->current = nullptr;
        }

        Iterator(Node<T> *node) {
            this->current = node;
        }

        Iterator<T>& operator=(const Iterator<T> &other) {          
            this->current = other.current;
            return *this;
        }

        bool operator!=(Iterator<T> other) {
            return this->current == other.current;
        }

        Iterator<T>& operator++() {

        }

        Iterator<T>& operator--() {
            // TODO
        }

        T operator*() {
            return this->current->data;
        }
};

#endif
