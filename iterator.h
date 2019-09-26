#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <vector>

template <typename T>
class Iterator {
    private:
        Node<T>* current;
        Node<T>* root;
        std::vector<Node<T>*> repositoryNodes;

        Node<T>* refillRepository(Node<T>* node){
            if(node != nullptr){
                refillRepository(node->left);
                repositoryNodes.push_back(node);
                refillRepository(node->right);
            }
        }

    public:
        Iterator() {
            this->current = nullptr;
            this->root = nullptr;
        }

        Iterator(Node<T> *node, Node<T>* root) {
            this->current = node;
            this->root = root;
        }

        Iterator<T>& operator=(const Iterator<T> &other) {          
            this->current = other.current;
            return *this;
        }

        bool operator!=(Iterator<T> other) {
            return this->current != other.current;
        }

        Iterator<T>& operator++() {

            refillRepository(this->root);

            if(current == repositoryNodes[repositoryNodes.size()-1]) current = nullptr;
            else{
                for (int i = 0; i < repositoryNodes.size()-1; ++i) {
                    if(repositoryNodes[i] == current) {
                        current = repositoryNodes[i+1];
                        break;
                    }
                }
            }

            repositoryNodes.clear();
            return *this;
        }

        Iterator<T>& operator--() {

            refillRepository(this->root);

            if (current == nullptr) current = repositoryNodes[repositoryNodes.size() - 1];
            else {
                for (int i = 0; i < repositoryNodes.size(); ++i) {
                    if (repositoryNodes[i] == current && i != 0) {
                        current = repositoryNodes[i - 1];
                        break;
                    }
                }
                repositoryNodes.clear();
                return *this;
            }
        }

        T operator*() {
            if(current != nullptr) return this->current->data;
            return -1;
        }
};

#endif
