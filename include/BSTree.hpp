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

    bool node_is_left_child(std::shared_ptr<Node<T>> parent, std::shared_ptr<Node<T>> child)
    {
        return (parent -> get_left() == child);
    }

public:
    BSTree() {};
    BSTree(T value)
    {
        insert(value);
    }
    ~BSTree() {};

    std::shared_ptr<Node<T>> get_head() const
    {
        return _head;
    }

    //http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete.html
    std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>> remove(T key)
    {
        auto result = this -> search(key);
        //parent, replacement
        std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>> successor = std::make_pair(nullptr, nullptr);

        if(result.second != nullptr)
        {
            //we have a valid result
            //case 1. deleting node that has no subtree
            if (result.second -> get_left() == nullptr && result.second -> get_right() == nullptr)
            {
                if(node_is_left_child(result.first, result.second))
                {
                    result.first -> null_left();
                } else
                {
                    result.first -> null_right();
                }
                //if deletion node is the root node
                if (_head == result.second) _head = nullptr;
                //successor & his parent is equal to nullptr
            }
            //case 2. deleting a node that has one subtree
            //left subtree
            if(result.second -> get_left() != nullptr && result.second -> get_right() == nullptr)
            {
                if(result.second == _head)
                {
                        _head = result.second -> get_left();
                        successor.second = _head;
                }
                if (node_is_left_child(result.first, result.second))
                {
                        result.first -> replace_left(result.second -> get_left());
                        successor = std::make_pair(result.first, result.first -> get_left());
                } else
                {
                        result.first -> replace_right(result.second -> get_left());
                        successor = std::make_pair(result.first, result.first -> get_right());
                }
            }
            //right subtree
            if(result.second -> get_left() == nullptr && result.second -> get_right() != nullptr)
            {
                if (node_is_left_child(result.first, result.second))
                {
                    if(result.second == _head)
                    {
                        _head = result.second -> get_right();
                        successor.second = _head;
                    } else
                    {
                        result.first -> replace_left(result.second -> get_right());
                        successor = std::make_pair(result.first, result.first ->get_left());
                    }
                } else
                {
                    if(result.second == _head)
                    {
                        _head = result.second -> get_right();
                        successor.second = _head;
                    } else
                    {
                        result.first -> replace_right(result.second -> get_right());
                        successor = std::make_pair(result.first, result.first -> get_right());
                    }
                }
            }
            //case 3. deletion node has two subtrees
            if(result.second -> get_left() != nullptr && result.second -> get_right() != nullptr)
            {
                //find successor node in the node with the minimum value in the right subtree
                auto right_subtree_head = result.second -> get_right();
                successor = std::make_pair(result.first, result.second -> get_right());
                auto to_delete = result.second;
                // if right subtree head has no left leaf just swap it
                if (right_subtree_head -> get_left() == nullptr)
                {
                    std::cout << "first" << std::endl;
                    if(node_is_left_child(result.first, to_delete))
                    {
                       //left child
                        result.first -> replace_left(right_subtree_head);
                    } else
                    {
                        //right child
                        result.first ->replace_right(right_subtree_head);
                        if(result.second -> get_left() != nullptr) {
                            right_subtree_head -> replace_left(to_delete -> get_left());
                        }
                    }

                    if(_head == to_delete){
                        _head = right_subtree_head;
                    }

                } else //both leafs present
                {
                    std::cout << "second" << std::endl;
                    auto replacement = find_min_val_node(right_subtree_head);
                    successor = std::make_pair(result.first, replacement.second);
                    if(node_is_left_child(result.first, result.second))
                    {
                       //left child
                        result.first -> replace_left(replacement.second);
                    } else
                    {
                        //right child
                        result.first ->replace_right(replacement.second);
                    }
                    if(_head == to_delete){
                        _head = replacement.second;
                    }
                    replacement.second -> replace_left(to_delete -> get_left());
                    replacement.second -> replace_right(to_delete -> get_right());
                    replacement.first -> null_left();
                }

                to_delete -> null_left();
                to_delete -> null_right();
                result.second.reset();
                to_delete.reset();

            }
        }
        return successor;
    }

    //void destroy_tree();

    std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>> find_min_val_node(std::shared_ptr<Node<T>> parent = nullptr) const
    {

        if (parent == nullptr)
        {
            return std::make_pair(nullptr, nullptr);
        } else
        {
            std::shared_ptr<Node<T>> needle = nullptr;

            needle = parent -> get_left();

            while(needle->get_left() != nullptr)
            {
                parent = needle;
                needle = needle -> get_left();
            };

            return std::make_pair(parent, parent->get_left());
        }
    }

    std::pair<std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>> search(T value) const
    {
        if(_head != nullptr && _head -> get_key() == value)
        {
            return make_pair(nullptr, _head);
        }
        std::shared_ptr<Node<T>> parent = nullptr;
        std::shared_ptr<Node<T>> needle = _head;
        do {
            parent = needle;

            if(value > needle -> get_key())
            {

                needle = needle -> get_right();
            } else if(value < needle -> get_key())
            {
                needle = needle -> get_left();
            }

            if (needle == nullptr) parent = nullptr;

       } while((needle != nullptr) && (needle -> get_key() != value));

        return std::make_pair(parent, needle);

    }

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
            return current;
        }
    }
};

#endif


