#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__
#include <iostream>
#include <utility> //std::pair

/*
 * Every node is either red or black.
 * If a node has a NULL child, that "child" is considered black.
 * If a node is red, then both of its children are black.
 * Every simple path from a node to a descendant NULL child has the same number of black nodes, (including the black NULL child).
 * The root is black.
 *
 * */

template<typename T>
class RBTree : public BSTree
{

public:
     void insert(T value, std::shared_ptr<Node<T>> parent = nullptr)
    {
        if(parent == nullptr && _head == nullptr)
        {
           _head = std::make_shared<Node<T>> (value);
           _head -> flip_color();

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

        // if the node is root recolor to black
        //

        //parent is red?
        //
        //rotate left
        //
        //rotate right
        }
    }
};

#endif
