#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <memory>

template <typename T>
class Node
{
    T _key;
    std::shared_ptr<Node<T>> _left = nullptr;
    std::shared_ptr<Node<T>> _right = nullptr;
public:
    Node(T value);
    ~Node();

    T get_key() const;
    std::shared_ptr<Node<T>> get_left() const;
    std::shared_ptr<Node<T>> get_right() const;
    void add_left(T value);
};




#endif
