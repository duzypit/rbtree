#include "../include/Node.hpp"

template<typename T>
Node<T>::Node(T value)
{
    _key = value;
}

template<typename T>
T Node<T>::get_key() const
{
    return _key;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::get_left() const
{
    return _left;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::get_right() const
{
    return _right;
}

template<typename T>
void Node<T>::add_left(T value)
{
    _left = std::make_shared<Node<T>>(value);
}

