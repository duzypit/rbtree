#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include "BSTree.hpp"
#include <string>

class TreeInspector
{

    std::string _prefix = "";

    void _pop(){
        _prefix.erase(_prefix.length() - 4);
    }
    std::string _red = std::string("\033[0;31m");
    std::string _reset = std::string("\033[0m");
public:
    TreeInspector(){};

    template<typename T>
    TreeInspector(BSTree<T> t)
    {
        print_tree(t.get_head());
    }

    template<typename T>
    void print_tree(BSTree<T> t)
    {
        print_tree(t.get_head());
    }

    template<typename T>
    void print_tree(std::shared_ptr<Node<T>> node)
    {
        if(node == nullptr)
        {
            std::cout << "No tree data to print!" << std::endl;
        }

        std::cout << "(";
        if (node -> is_red())
        {
            std::cout << _red << node -> get_key() << _reset;

        } else
        {
            std::cout << node -> get_key();
        }
        std::cout << ")" << std::endl;

        if(node -> get_right())
        {
            if(node -> get_left() == nullptr)
            {
                std::cout << _prefix << " └───";
                _prefix.append(std::string("    "));
            } else
            {
                std::cout << _prefix << " ├───";
                _prefix.append(std::string(" |  "));
            }
            this -> print_tree(node -> get_right());
            _pop();
        }

        if (node -> get_left())
        {
            std::cout << _prefix << " └───";
            _prefix.append(std::string("    "));
            this->print_tree(node->get_left());
            _pop();
        }
    }

    ~TreeInspector(){};
};


#endif
