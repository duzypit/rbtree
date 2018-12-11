#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__
#include <iostream>
#include <utility> //std::pair
#include "BSTree.hpp"

/*
 * Every node is either red or black.
 * If a node has a NULL child, that "child" is considered black.
 * If a node is red, then both of its children are black.
 * Every simple path from a node to a descendant NULL child has the same number of black nodes, (including the black NULL child).
 * The root is black.
 * http://www.catonmat.net/blog/mit-introduction-to-algorithms-part-six
 * */

template<typename T>
class RBTree : public BSTree<T>
{

public:
    RBTree() {};
    RBTree(T value)
    {
        insert(value);
    }
    ~RBTree() {};
/*
    std::shared_ptr<Node<T>> get_head() const
    {
        return this->_head;
    }

*/
    std::shared_ptr<Node<T>> insert(T value, std::shared_ptr<Node<T>> parent = nullptr)
    {
        if(parent == nullptr && this->_head == nullptr)
        {
            //current node is head - repaint it to black
           this->_head = std::make_shared<Node<T>> (value);
           this->_head -> flip_color();
           return this->_head;

        } else
        {
            std::shared_ptr<Node<T>> current = nullptr;
            if (parent == nullptr)
            {
                parent = this->_head;
            }

            if (value < parent -> get_key())
            {
                if (parent -> get_left() == nullptr)
                {
                    parent -> add_left(value);
                    current = parent -> get_left();
                } else
                {
                    this -> insert(value, parent -> get_left());
                }
            } else
            {

                if (parent -> get_right() == nullptr)
                {

                    parent -> add_right(value);
                    current = parent -> get_right();
               } else
                {

                    this -> insert(value, parent -> get_right());
                }

           }

/*
        //set parrent to current node
        if (current != nullptr)
            current -> set_parent(parent);

        //nullptr if current is head
        if(parent != nullptr && parent -> is_red())
        {
        // case 1. current's uncle, is red
            if(parent->get_parent() != nullptr)
            {
                if(parent->get_parent()->get_right() != nullptr)
                {
                    if(parent->get_parent()->get_right()->is_red())
                    {
                        //recolor parent
                        parent->flip_color();
                        //grandpa
                        parent->get_parent()->flip_color();
                        //uncle
                        parent->get_parent()->get_right()->flip_color();
                    }
                }
            }

            //case 2. current's uncle is black, current is the right child
        //
        //rotate left
        //
        //rotate right

        //default node color is red
        //if parent is red recolor - but first check for rotations
        if(parent->is_red())
            current -> flip_color();

        }
*/
        return current;
        }
    }

};

#endif
