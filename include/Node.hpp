#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <memory>

template <typename T>
class Node
{
    T key;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;


public:
    Node();

};




#endif
