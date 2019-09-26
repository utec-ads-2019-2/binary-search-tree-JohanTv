#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h

template <typename T>
class BSTree {
private:
    Node<T> *root;
    size_t nodes;

    void printInOrder(Node<T>* start){
        if(start != nullptr){
            printInOrder(start->left);
            cout<<start->data<<" ";
            printInOrder(start->right);
        }
    }

    void printPreOrder(Node<T>* start){
        if(start != nullptr){
            cout<<start->data<<" ";
            printPreOrder(start->left);
            printPreOrder(start->right);
        }
    }

    void printPostOrder(Node<T>* start){
        if(start != nullptr){
            printPostOrder(start->left);
            printPostOrder(start->right);
            cout<<start->data<<" ";
        }
    }

    bool inTree(T data, Node<T> **&pointer, bool find){

        if (this->nodes == 0) return false;
        else if(this->root->data == data && find ) return true;
        else {
            pointer = &(this->root);
            while (true) {

                if (data > (*pointer)->data) {
                    if ((*pointer)->right == nullptr) return false;
                    else if ((*pointer)->right->data == data && find) return true;
                    else pointer = &((*pointer)->right);
                }

                else {
                    if ((*pointer)->left == nullptr) return false;
                    else if ((*pointer)->left->data == data && find) return true;
                    else pointer = &((*pointer)->left);
                }

            }
        }
    }
    void destroyAll(Node <T>* node){
        if(node != nullptr){
            destroyAll(node->left);
            destroyAll(node->right);
            delete node;
        }
    }

    size_t totalHeight(Node<T>* node){
        if (node == nullptr) return 0;

        size_t hLeft = totalHeight(node->left);
        size_t hRight = totalHeight(node->right);

        return max(hLeft, hRight) + 1;
    }

    public:
        BSTree() : root(nullptr), nodes(0) {};


        bool find(T data) {
            Node<T>** nodeDad = &(this->root);
            return inTree(data,nodeDad,true);
        }

        BSTree& insert(T data) {
            Node<T>** nodeDad = nullptr;

            inTree(data,nodeDad,false);

            Node<T>* newNode = new Node<T>(data);

            if(nodeDad == nullptr) this->root = newNode;
            else if (data >  (*nodeDad)->data) (*nodeDad)->right = newNode;
            else (*nodeDad)->left = newNode;

            (this->nodes)++;

            return *this;
        }

        void transplant(Node<T>* nodeDelete, Node<T>* nodeNext, Node<T>* nodeDad){
            if (nodeDad == nullptr) this->root = nodeNext;
            else if(nodeDelete == nodeDad->left) nodeDad->left = nodeNext;
            else nodeDad->right = nodeNext;

            delete nodeDelete;
        }

        void nodeSelect(Node<T>* nodeDad, Node<T>*& select,T data){
            if( nodeDad->right != nullptr && nodeDad->right->data == data) select = nodeDad->right;
            else if( nodeDad->left != nullptr && nodeDad->left->data == data ) select = nodeDad->left;
            else select = nodeDad;
        }

        bool remove(T data){
            Node<T>** nodeDad = nullptr;
            if(inTree(data,nodeDad,true)){

                Node<T>* nodeDelete = nullptr;

                if (nodeDad == nullptr) nodeDelete = this->root;
                else nodeSelect((*nodeDad),nodeDelete,data);

                //one node
                if(nodeDelete->left == nullptr) {
                    if (nodeDad == nullptr) {
                        this->root = nodeDelete->right;
                        delete nodeDelete;
                    }
                    else transplant(nodeDelete, nodeDelete->right, *nodeDad);
                }
                else if(nodeDelete->right == nullptr) {
                    if(nodeDad == nullptr){
                        this->root = nodeDelete->left;
                        delete nodeDelete;
                    }
                    else transplant(nodeDelete, nodeDelete->left, *nodeDad);
                }

                //two nodes
                else{
                    Node<T>** nodeDadSuccessor = &nodeDelete;
                    T successorData = maximum(nodeDelete->left,nodeDadSuccessor);

                    Node<T>* nodeSuccessor = nullptr;
                    nodeSelect((*nodeDadSuccessor),nodeSuccessor,successorData);

                    if((*nodeDadSuccessor) != nodeDelete){
                        transplant(nodeSuccessor,nodeSuccessor->left,*nodeDadSuccessor);
                        nodeDelete->data = successorData;
                    }
                    else {
                        Node<T> *temp = nodeDelete->right;
                        if(nodeDad == nullptr){
                            this->root = nodeSuccessor;
                            delete nodeDelete;
                        }
                        else transplant(nodeDelete, nodeSuccessor, *nodeDad);
                        nodeSuccessor->right = temp;
                    }
                }
                (this->nodes)--;
                return true;
            }
            return false;
        }

        T maximum(Node<T>* start, Node<T>**& nodeDad){
            while(start->right != nullptr){
                nodeDad = &(start);
                if (start->right->right == nullptr) break;
                else start = start->right;
            }

            if (start->right == nullptr) return start->data;
            else return start->right->data;
        }
        //Unused function
        T minimum(Node<T>* start, Node<T>**& nodeDad){
            while(start->left != nullptr){
                nodeDad = &(start);
                if (start->left->left == nullptr) break;
                else start = start->left;
            }

            if (start->left == nullptr) return start->data;
            else return start->left->data;
        }

        size_t size() {
            return this->nodes;
        }

        size_t height() {
            return totalHeight(this->root);
        }

        void traversePreOrder() {
            printPreOrder(this->root);
        }

        void traverseInOrder() {
            printInOrder(this->root);
        }

        void traversePostOrder() {
            printPostOrder(this->root);
        }

        Iterator<T> begin() {
            // TODO
        }

        Iterator<T> end() {
            // TODO
        }

        ~BSTree() {
            destroyAll(this->root);
        }
};

#endif
