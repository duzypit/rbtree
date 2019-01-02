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
 * */

template<typename T>
class RBTree : public BSTree<T>
{
private:

    std::shared_ptr<Node<T>> get_uncle(std::shared_ptr<Node<T>> current)
    {
        std::shared_ptr<Node<T>> uncle = nullptr;
        if(current -> get_parent() != nullptr)
        {
            auto father = current -> get_parent();
            if (father -> get_parent())
            {
                auto grandfather = father -> get_parent();

                if(father == grandfather -> get_left())
                {
                    if(grandfather -> get_right() != nullptr) { uncle = grandfather -> get_right(); }
                } else
                {
                    if(grandfather -> get_left() != nullptr ) {uncle = grandfather -> get_left(); }
                }
            }
        }

        return uncle;
    }

public:
    RBTree() {};

    RBTree(T value)
    {
        insert(value);
    }

    ~RBTree() {};

    std::shared_ptr<Node<T>> insert(T value, std::shared_ptr<Node<T>> parent = nullptr)
    {

        std::shared_ptr<Node<T>> current = nullptr;

        if(parent == nullptr && this->_head == nullptr)
        {
            //current node is head - repaint it to black
            current = this->_head = std::make_shared<Node<T>> (value);

        } else
        {
            if (parent == nullptr)
            {
                parent = this->_head;
            }

            if (value >=  parent -> get_key())
            {
                if (parent -> get_right() == nullptr)
                {

                    parent -> add_right(value);
                    current = parent -> get_right();
                    current -> set_parent(parent);
                    this->reorganize(current);
                } else
                {

                    this -> insert(value, parent -> get_right());
                }

            } else
            {

                if (parent -> get_left() == nullptr)
                {
                    parent -> add_left(value);
                    current = parent -> get_left();
                    current ->set_parent(parent);
                    this->reorganize(current);
                } else
                {
                    this -> insert(value, parent -> get_left());
                }

           }

        }
        return current;
    }

    void reorganize(std::shared_ptr<Node<T>> current)
    {
        if( current != nullptr)
        {
            // case 0 - current is the root
            if (current == this->_head && current -> is_red())
            {
                current -> flip_color();
            }

            std::shared_ptr<Node<T>> father = nullptr;

            father = current -> get_parent();

            //case 0.5 - both childrens are red =>
            //father and uncle are red - recolor
            if(father != nullptr && father -> is_red())
            {
                auto uncle = this->get_uncle(current);
                if(uncle != nullptr && uncle -> is_red() && father -> is_red())
                {
                        uncle -> flip_color();
                        father -> flip_color();
                        father -> get_parent() -> flip_color();
                        this -> reorganize(father -> get_parent());
                }
            }

            std::shared_ptr<Node<T>> grandfather = nullptr;

            if(father != nullptr && father -> get_parent() != nullptr && father -> is_red() && current -> is_red())
            {
                grandfather = father -> get_parent();
                std::shared_ptr<Node<T>> ancestor = nullptr;
                if(grandfather != nullptr)
                {
                    ancestor = grandfather -> get_parent();
                }
                //case 1 - father is left
                if (father == grandfather -> get_left())
                {
                    //case 1a - current is left (left-left)
                    if(current == father -> get_left())
                    {

                        grandfather -> replace_left(father -> get_right());
                        if(grandfather -> get_left() != nullptr)
                        {
                            grandfather -> get_left() -> set_parent(grandfather);
                        }
                        father -> replace_right(grandfather);
                        father -> set_parent(grandfather -> get_parent());
                        grandfather-> set_parent(father);

                        if(ancestor != nullptr)
                        {
                            if (grandfather == ancestor -> get_left())
                            {
                                ancestor -> replace_left(father);
                            } else
                            {
                                ancestor -> replace_right(father);
                            }
                        }

                        //recolor?
                        if (!grandfather -> is_red())
                        {
                            grandfather -> flip_color();
                        }

                        if (father -> is_red())
                        {
                            father -> flip_color();
                        }

                        if (grandfather == this -> _head)
                        {
                            this -> _head = father;
                        }

                        this->reorganize(father);
                    } else //1b current is right (left - right)
                    {
                        father -> replace_right(current -> get_left());
                        if(father -> get_right() != nullptr)
                        {
                            father -> get_right() -> set_parent(father);
                        }
                        father -> set_parent(current);
                        current -> replace_left(father);
                        current-> set_parent(grandfather -> get_parent());
                        grandfather -> replace_left(current -> get_right());
                        current -> replace_right(grandfather);
                        grandfather -> set_parent(current);

                        if(ancestor != nullptr)
                        {
                            if (grandfather == ancestor -> get_left())
                            {
                                ancestor -> replace_left(current);
                            } else
                            {
                                ancestor -> replace_right(current);
                            }
                        }

                       //recolor?
                        if (current -> is_red())
                        {
                            current -> flip_color();
                        }

                        if (!grandfather -> is_red())
                        {
                            grandfather -> flip_color();
                        }



                        if (grandfather == this -> _head)
                        {
                            this -> _head = current;
                        }

                        this -> reorganize(current);
                    }
                } else //case 2 father is right
                {
                    //case 2a current is right (right-right)
                    if(current == father-> get_right())
                    {
                        grandfather -> replace_right(father -> get_left());
                        if(grandfather -> get_right() != nullptr)
                        {
                            grandfather -> get_right() -> set_parent(grandfather);
                        }
                        father -> set_parent(grandfather -> get_parent());
                        grandfather -> set_parent(father);
                        father -> replace_left(grandfather);

                        if(ancestor != nullptr)
                        {
                            if (grandfather == ancestor -> get_left())
                            {
                                ancestor -> replace_left(father);
                            } else
                            {
                                ancestor -> replace_right(father);
                            }
                        }

                        //recolor?
                        if (!grandfather -> is_red())
                        {
                            grandfather -> flip_color();
                        }

                        if (father -> is_red())
                        {
                            father -> flip_color();
                        }

                        if (grandfather == this -> _head)
                        {
                            this -> _head = father;
                        }

                        this->reorganize(father);

                    } else //case 2b, current is left (right - left)
                    {
                        father -> replace_left(current -> get_right());
                        if(father -> get_left() != nullptr)
                        {
                            father -> get_left() -> set_parent(father);
                        }

                        father -> set_parent(current);
                        current -> replace_right(father);
                        current-> set_parent(grandfather -> get_parent());
                        grandfather -> replace_right(current -> get_left());
                        current -> replace_left(grandfather);
                        grandfather -> set_parent(current);


                        if(ancestor != nullptr)
                        {
                            if (grandfather == ancestor -> get_left())
                            {
                                ancestor -> replace_left(current);
                            } else
                            {
                                ancestor -> replace_right(current);
                            }
                        }

                       //recolor?
                        if (current -> is_red())
                        {
                            current -> flip_color();
                        }

                        if (!grandfather -> is_red())
                        {
                            grandfather -> flip_color();
                        }

                        if (grandfather == this -> _head)
                        {
                            this -> _head = current;
                        }

                        this -> reorganize(current);

                    }
                }

            }


        }
    }

    void remove(T key)
    {
        auto result = this -> search(key);
        if(result.second -> is_red())
        {
            BSTree<T>::remove(key);
        }


    }

};

#endif
