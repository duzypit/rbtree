#ifndef __BSTREE_HPP__
#define __BSTREE_HPP__
#include "Node.hpp"
#include <iostream>
#include <utility> //std::pair

template<typename T>
class BSTree
{

friend class TreeInspector;

protected:
    std::shared_ptr<Node<T>> _head = nullptr;

    /**
     * @brief check if given node is a left node
     *
     * @param ptr to needle node
     * @return bool
     */
    bool is_left_child(std::shared_ptr<Node<T>> child)
    {
        return (child -> get_parent() -> get_left() == child);
    }

public:
    BSTree() {};
    BSTree(T value)
    {
        insert(value);
    }
    ~BSTree() {};

    /**
     * @brief returns head node ptr
     *
     * @return ptr to head
     */
    std::shared_ptr<Node<T>> get_head() const
    {
        return _head;
    }

    /**
     * @brief removes node from tree, using Hibbard algorithm
     * more details:
     * http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete.html
     * http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete2.html
     *
     * @param T key
     * @return ptr to successor
     */
    std::shared_ptr<Node<T>> remove(T key)
    {
        auto result = this -> search(key);
        //parent, replacement
        std::shared_ptr<Node<T>> successor = nullptr;

        if(result != nullptr)
        {
            //we have a valid result
            //case 1. deleting node that has no subtree
            if (result -> get_left() == nullptr && result -> get_right() == nullptr)
            {
                if(this -> is_left_child(result))
                {
                    result -> get_parent() -> null_left();
                } else
                {
                    result -> get_parent() -> null_right();
                }
                //if deletion node is the root node
                if (_head == result) _head = nullptr;
            }

            //case 2. deleting a node that has one subtree
            //left subtree
            if(result -> get_left() != nullptr && result -> get_right() == nullptr)
            {
                if(result == _head)
                {
                        _head = result -> get_left();
                        successor = _head;
                }
                //node to delete is a left child
                if (this -> is_left_child(result))
                {
                        result -> get_parent() -> replace_left(result -> get_left());
                        successor = result -> get_parent() -> get_left();
                } else
                {
                        result -> get_parent() -> replace_right(result -> get_left());
                        successor = result -> get_parent() -> get_right();
                }

                //set parent for all cases
                successor -> set_parent(result -> get_parent());
            }
            //right subtree
            if(result -> get_left() == nullptr && result -> get_right() != nullptr)
            {
                if(result == _head)
                {
                    _head = result -> get_right();
                    successor = _head;
                }

                if (this -> is_left_child(result))
                {
                    result -> get_parent() -> replace_left(result -> get_right());
                    successor = result -> get_parent() -> get_left();
                } else
                {

                    result -> get_parent() -> replace_right(result -> get_right());
                    successor = result -> get_parent() -> get_right();
                }

                //set parent for all cases
                successor -> set_parent(result -> get_parent());
            }

            //case 3. deletion node has two subtrees
            if(result -> get_left() != nullptr && result -> get_right() != nullptr)
            {
                //find successor node in the node with the minimum value in the right subtree
                auto right_subtree_head = result -> get_right();
                auto to_delete = result;
                // if right subtree head has no left leaf just swap it
                if (right_subtree_head -> get_left() == nullptr)
                {
                    if(this -> is_left_child(to_delete))
                    {
                        result -> get_parent() -> replace_left(right_subtree_head);
                    } else
                    {
                        //right child
                        result -> get_parent() -> replace_right(right_subtree_head);

                        if(result -> get_left() != nullptr) {
                            right_subtree_head -> replace_left(to_delete -> get_left());
                        }
                    }

                    if(_head == to_delete){
                        _head = right_subtree_head;
                        _head -> replace_left(to_delete -> get_left());
                    }
                    successor = right_subtree_head;
                } else //both leafs present
                {
                    auto replacement = successor = this -> find_min_val_node(right_subtree_head);
                    if(_head != to_delete)
                    {
                        if(is_left_child(result))
                        {
                           //left child
                            result -> get_parent() -> replace_left(replacement);
                        } else
                        {
                            //right child
                            result -> get_parent() ->replace_right(replacement);
                        }
                    } else
                    {
                        //_head == to_delete
                        _head = replacement;
                    }

                    replacement -> replace_left(to_delete -> get_left());
                    replacement -> replace_right(to_delete -> get_right());
                    replacement -> get_parent() -> null_left();
                    successor = replacement;
                }
                successor -> set_parent(result -> get_parent());
                to_delete -> null_left();
                to_delete -> null_right();
                result.reset();
                to_delete.reset();

            }
        }
        return successor;
    }

    /**
     * @brief finds node with min value, search begins at given node, default param should be head
     *
     * @param parent node
     * @return needle
     */
    std::shared_ptr<Node<T>> find_min_val_node(std::shared_ptr<Node<T>> parent = nullptr) const
    {

        if (parent == nullptr)
        {
            return nullptr;
        } else
        {
            std::shared_ptr<Node<T>> needle = nullptr;

            needle = parent -> get_left();

            while(needle->get_left() != nullptr)
            {
                needle = needle -> get_left();
            };

            return needle;
        }
    }

    /**
     * @brief serch for node with given value
     *
     * @param key
     * @return ptr to needle
     */
    std::shared_ptr<Node<T>> search(T value) const
    {

        if(_head != nullptr && _head -> get_key() == value)
        {
            return  _head;
        }

        auto needle = _head;

        do {

            if(value > needle -> get_key())
            {
                needle = needle -> get_right();
            } else if(value < needle -> get_key())
            {
                needle = needle -> get_left();
            }


       } while((needle != nullptr) && (needle -> get_key() != value));

        return needle;

    }

    /**
     * @brief insert a node into tree, new node stores parent address
     *
     * @pram key
     * @param ptr to parent node
     * @return ptr to inserted node
     */
    std::shared_ptr<Node<T>> insert(T value, std::shared_ptr<Node<T>> parent = nullptr)
    {
        if(parent == nullptr && _head == nullptr)
        {
           _head = std::make_shared<Node<T>> (value);
           return _head;
        } else
        {
            std::shared_ptr<Node<T>> current;
            if (parent == nullptr)
            {
                parent = _head;
            }

            if (value < parent -> get_key())
            {
                if (parent -> get_left() == nullptr)
                {
                    parent -> add_left(value);
                    current = parent -> get_left();
                    current -> set_parent(parent);
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
                    current -> set_parent(parent);
                } else
                {

                    this -> insert(value, parent -> get_right());
                }
            }
            return current;
        }
    }
};

#endif


