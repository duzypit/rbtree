#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <memory>

template <typename T>
class Node
{
private:
    T _key;
    std::shared_ptr<Node<T>> _left = nullptr;
    std::shared_ptr<Node<T>> _right = nullptr;
    std::shared_ptr<Node<T>> _parent = nullptr;
    enum class Color {black = false, red = true};
    Color _color = Color::red;


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

    void replace_left(std::shared_ptr<Node<T>> ptr)
    {
        _left = ptr;
    }

    void replace_right(std::shared_ptr<Node<T>> ptr)
    {
        _right = ptr;
    }

    void null_left()
    {
        _left = nullptr;
    }

    void null_right()
    {
        _right = nullptr;
    }

    Node::Color get_color() const
    {
        return _color;
    }

    void set_color(Color c)
    {
        _color = c;
    }

    bool is_red() const
    {
        return (_color == Color::red) ? true : false;
    }

    void flip_color()
    {
        (_color == Color::red) ? _color = Color::black : _color = Color::red;
    }

    std::shared_ptr<Node<T>> get_parent()
    {
        return _parent;
    }

    void set_parent(std::shared_ptr<Node<T>> new_parent)
    {
        _parent = new_parent;
    }
};
#endif
