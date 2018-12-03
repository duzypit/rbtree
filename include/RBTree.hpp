#ifndef __BWTREE_HPP__
#define __BWTREE_HPP__
#include "VTree.hpp"
#include "Node.hpp"
#include <iostream>

template<typename T>
class RBTree
{

    friend class Viewer;
private:
    std::shared_ptr<Node<T>> head = nullptr;
public:
    RBTree() {};
    RBTree(T value)
    {
        insert(value);
    }
    ~RBTree() {};
    void remove(T r);
    void destroy_tree();
    Node<T>* search(T value);

    void insert(T value, std::shared_ptr<Node<T>> parent = nullptr)
    {
        if(parent == nullptr && head == nullptr)
        {
            head = std::make_shared<Node<T>> (value);
        } else
        {
            if (parent == nullptr)
            {
                parent = head;
            }

            if (value < parent -> get_key())
            {
                if (parent -> get_left() == nullptr)
                {
                    parent -> add_left(value);
                } else
                {
                    this -> insert(value, parent -> get_left());
                }
            } else
            {

                if (parent -> get_right() == nullptr)
                {

                    parent -> add_right(value);
                } else
                {

                    this -> insert(value, parent -> get_right());
                }
            }

        }
    }
};
#endif


