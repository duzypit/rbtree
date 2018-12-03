#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include "RBTree.hpp"
#include <string>

template<typename T>
class TreeInspector
{

    std::string _prefix = "";


    void pop(){
        _prefix.erase(_prefix.length() - 4);
    }

public:
    TreeInspector(){};
    TreeInspector(RBTree<T> t)
    {
        print_tree(t._head);
    }

    void print_tree(std::shared_ptr<Node<T>> node)
    {
        if(node == nullptr)
        {
            std::cout << "No tree to print!" << std::endl;
        }

        std::cout << "(" << node -> get_key() << ")" << std::endl;
        if(node -> get_right())
        {
            std::cout << _prefix << " ├───";
            _prefix.append(std::string(" |  "));
            this -> print_tree(node -> get_right());
            pop();
        }

        if (node -> get_left())
        {
            std::cout << _prefix << " └───";
            _prefix.append(std::string("    "));
            this->print_tree(node->get_left());
            pop();
        }
    }
    ~TreeInspector(){};
};


#endif
