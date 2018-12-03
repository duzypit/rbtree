#ifndef __BWTREE_HPP__
#define __BWTREE_HPP__
#include "VTree.hpp"
#include "Node.hpp"
#include <iostream>
#include <utility> //std::pair

template<typename T>
class RBTree
{

    friend class TreeInspector;
private:
    std::shared_ptr<Node<T>> _head = nullptr;
public:
    RBTree() {};
    RBTree(T value)
    {
        insert(value);
    }
    ~RBTree() {};

    //http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete.html
    void remove(T r);

    void destroy_tree();

    std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>> search(T value)
    {
        std::shared_ptr<Node<T>> parent = nullptr;
        std::shared_ptr<Node<T>> needle = _head;

        while(  (needle != nullptr) &&
                (needle -> get_key() != value))
        {
            parent = needle;

            if(value > needle -> get_key())
            {

                needle = needle -> get_right();
            }

            if(value < needle -> get_key())
            {
                needle = needle -> get_left();
            }
        }

        return std::make_pair(parent, needle);
    }

    void insert(T value, std::shared_ptr<Node<T>> parent = nullptr)
    {
        if(parent == nullptr && _head == nullptr)
        {
           _head = std::make_shared<Node<T>> (value);
        } else
        {
            if (parent == nullptr)
            {
                parent = _head;
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


