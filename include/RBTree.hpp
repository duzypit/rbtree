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
 * https://www.csee.umbc.edu/courses/pub/www/undergraduate/courses/341/fall13/section3/lectures/10-Red-Black-Trees.pdf
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

            //case 0.1 - both childrens are red -> recolor?
            if (father != nullptr && father -> get_left() != nullptr && father -> get_right() != nullptr)
            {
                if(father -> get_left() -> is_red() && father -> get_right() -> is_red())
                {
                    father -> get_left() -> flip_color();
                    father -> get_right() -> flip_color();
                    father -> flip_color();
                    this -> reorganize(father);
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

/*
    void reorganize(std::shared_ptr<Node<T>> current)
    {
        if (current != nullptr && current -> get_parent() != nullptr)
        {
            // case 0 - current is the rooti
            if (current == this->_head && current -> is_red())
            {
                current -> flip_color();
            }

            auto father = current -> get_parent();

            if(father -> get_parent() != nullptr)
            {
                auto grandfather = father -> get_parent();

                //init vars in case uncle is empty (null) leaf
                std::shared_ptr<Node<T>> uncle = nullptr;
                bool uncle_is_red = false;
                bool uncle_is_left = false;

                //default uncle is right do we need to change?
                if(father == grandfather -> get_right())
                {
                    uncle_is_left = true;
                    uncle = grandfather -> get_left();
                } else
                {
                    uncle = grandfather -> get_right();
                }

                if(uncle != nullptr)
                {
                    uncle_is_red = uncle->is_red();
                }

                //1:  Both father and uncle are Red -- color father and uncle
                //Black, color grandparent Red. Point X to grandparent and
                //check new situation.
                if( father->is_red() && uncle_is_red)
                {
                    father->flip_color();
                    uncle->flip_color();
                    if(!grandfather->is_red())
                        grandfather->flip_color();
                    //check from grandfather if we need reorganize further
                    this->reorganize(grandfather);
                }

                if(father->is_red() && !uncle_is_red)
                {

                    //2 (zig-zag): Parent is Red, but uncle is Black. X and its parent
                    //are opposite type children -- color grandparent Red, color X
                    //Black, rotate left(right) on parent, rotate right(left) on grandparent

                    if (father == grandfather->get_left() && current == father -> get_right())
                    {
                        current -> set_parent(grandfather->get_parent());
                        current -> replace_left(father);
                        current -> replace_right(grandfather);

                        father -> null_right();
                        father -> set_parent(current);

                        grandfather -> set_parent(current);
                        grandfather -> null_left();

                        current -> flip_color();
                        grandfather -> flip_color();

                        //if( grandfather == this -> _head)
                        //    this -> _head = current;
                    }

                    //2 (zig-zag): mirror case
                    if (father == grandfather -> get_right() && current == father -> get_left())
                    {
                        current -> set_parent(grandfather -> get_parent());
                        father -> replace_left(current -> get_right());
                        current -> replace_right(father);
                        //current -> replace_left(grandfather);

//                        father -> replace_left(current -> get_right());
                        father -> set_parent(current);
//                        current -> replace_right(father);
                        grandfather -> replace_right(current);
                        current -> flip_color();
                        grandfather -> flip_color();

                        //if( grandfather == this -> _head)
                        //    this -> _head = current;

                    }

                    //3 (zig-zig):  Parent is Red, but uncle is Black. X and its parent
                    //are both left (right) children -- color parent Black, color
                    //grandparent Red, rotateright(left) on grandparent

                    if (father == grandfather->get_left() && current == father -> get_left())
                    {

                        auto greatgrandfather = grandfather -> get_parent();
                        if (greatgrandfather != nullptr && grandfather == greatgrandfather -> get_left())
                        {
                            greatgrandfather -> replace_left(father);
                        }
                        father -> set_parent(grandfather -> get_parent());
                        grandfather -> set_parent(father);
                        auto tmp = father -> get_right();
                        father -> replace_right(grandfather);
                        grandfather -> replace_left(tmp);

                        if(father -> is_red())
                            father -> flip_color();

                        if (grandfather == this -> _head)
                            this -> _head = father;

                        if(!grandfather -> is_red())
                            grandfather -> flip_color();
                    }

                    //3 (zig-zag): mirror case
                    if(father == grandfather -> get_right() && current == father -> get_right())
                    {
                        auto greatgrandfather = grandfather -> get_parent();
                        if (greatgrandfather != nullptr && grandfather == greatgrandfather -> get_right())
                        {
                            greatgrandfather -> replace_right(father);
                        }
                        father -> set_parent(grandfather -> get_parent());
                        grandfather -> set_parent(father);
                        auto tmp = father -> get_left();
                        father -> replace_left(grandfather);
                        grandfather -> replace_right(tmp);

                        if(father -> is_red())
                            father -> flip_color();

                        if (grandfather == this -> _head)
                            this -> _head = father;

                        if(!grandfather -> is_red())
                            grandfather -> flip_color();


                    }
                }


            }
        }
    }
*/
};

#endif
