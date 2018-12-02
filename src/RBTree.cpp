#include "../include/RBTree.hpp"
#include <iostream>

//https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

template<typename T>
RBTree<T>::RBTree(){ std::cout << "RBTree default ctor" << std::endl; };

template<typename T>
RBTree<T>::~RBTree(){ std::cout << "RBTree default dtor" << std::endl; };

template<typename T>
RBTree<T>::RBTree(T value)
{
    insert(value);
}

template<typename T>
void RBTree<T>::insert(T value)
{
    if(head == nullptr)
    {
        head = std::make_shared<Node<T>> (value);
    } else
    {
        if (value < head -> get_key())
        {
            if (head -> get_left == nullptr)
            {
                head -> add_left(value);
            }
        }
    }
}
