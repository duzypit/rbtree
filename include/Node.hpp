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
    ~Node() {};

    Node(T value)
    {
        _key = value;
    }

    T get_key() const
    {
        return _key;
    }

    std::shared_ptr<Node<T>> get_left() const
    {
        return _left;
    }

    std::shared_ptr<Node<T>> get_right() const
    {
        return _right;
    }

    void add_left(T value)
    {
        _left = std::make_shared<Node<T>>(value);
    }

    void add_right(T value)
    {
        _right = std::make_shared<Node<T>>(value);
    }

    void null_left()
    {
        _left = nullptr;
    }

    void null_right()
    {
        _right = nullptr;
    }

};




#endif
