#ifndef __binary_tree_cpp
#define __binary_tree_cpp

#include "binary_tree.h"
#include <cassert>
#include <cmath>

// ======================================================== // binary tree // ======================================================== // 

template <class T>
binary_tree<T>::binary_tree() : root(nullptr)
{}

template <class T>
binary_tree<T>::binary_tree(const binary_tree<T>& b_t)
{
    copy(&root, b_t.root);
}

template <class T>
binary_tree<T>& binary_tree<T>::operator=(const binary_tree<T>& b_t)
{
    if (this != &b_t)
    {
        clear(root);
        copy(&root, b_t.root);
    }
    return *this;
}

template <class T>
binary_tree<T>::~binary_tree()
{
    clear(root);
}

template <class T>
binary_tree<T>& binary_tree<T>::from_scheme(std::istream& in)
{
    clear(root);
    root = scheme_deserialize(in);
    return *this;
}

template <class T>
binary_tree<T>& binary_tree<T>::to_scheme(std::ostream& out)
{
    scheme_serialize(out, root);
    return *this;
}

// ======================================================== // position // ======================================================== // 

template <class T>
binary_tree<T>::position::position(node*& current_root) : current(current_root)
{}

template <class T>
typename binary_tree<T>::position& binary_tree<T>::position::operator= (const position& position)
{
    current = position.current;
    return *this;
}

template <class T>
typename binary_tree<T>::position binary_tree<T>::position::left() const
{
    assert(current != nullptr);
    return position(current->left);
}

template <class T>
typename binary_tree<T>::position binary_tree<T>::position::right() const
{
    assert(current != nullptr);
    return position(current->right);
}

template <class T>
bool binary_tree<T>::position::empty() const
{
    return current == nullptr;
}

template <class T>
typename binary_tree<T>::position& binary_tree<T>::position::set(const T& data)
{
    if (!current)
    {
        current = new node {data, nullptr, nullptr};
    }
    else
    {
        current->data = data;    
    }
    return *this;
}

template <class T>
T binary_tree<T>::position::get() const
{
    assert(current != nullptr);
    return current->data;
}

template <class T>
typename binary_tree<T>::node* binary_tree<T>::position::tree_node() const
{
    return current;
}

template <class T>
typename binary_tree<T>::position binary_tree<T>::root_position()
{
    return position(root);
}

// ======================================================== // iterator // ======================================================== // 

template <class T>
binary_tree<T>::iterator::iterator(position start, bool end)
{
    if (!end && !start.empty()) 
    {
        s.push(start);
        while (!s.top().left().empty())
        {
            s.push(s.top().left());
        }
    }
}

template <class T>
T binary_tree<T>::iterator::operator*()
{
    assert(!s.empty());
    return s.top().get();
}

template <class T>
typename binary_tree<T>::iterator& binary_tree<T>::iterator::operator++()
{
    assert(!s.empty());
    position top = s.top(); s.pop();
    if (!top.right().empty())
    {
        s.push(top.right());
        while (!s.top().left().empty())
        {
            s.push(s.top().left());
        }
    }
    return *this;
}

template <class T>
bool binary_tree<T>::iterator::operator!=(const iterator& it)
{
    if (s.empty())
    {
        return !it.s.empty();
    }
    return it.s.empty();
}

template <class T>
typename binary_tree<T>::iterator binary_tree<T>::begin()
{
    return iterator(position(root), false);
}

template <class T>
typename binary_tree<T>::iterator binary_tree<T>::end()
{
    return iterator(position(root), true);
}

// ======================================================== // helper // ======================================================== // 

template <class T>
void binary_tree<T>::copy(node** current_root, node* b_root)
{
    if (!b_root)
    {
        return;
    }
    *current_root = new node {b_root->data, nullptr, nullptr};
    if (b_root->left)
    {
        copy(&(*current_root)->left, b_root->left);
    }
    if (b_root->right)
    {
        copy(&(*current_root)->right, b_root->right);
    }
}

template <class T>
void binary_tree<T>::clear(node* current_root)
{
    if (!current_root)
    {
        return;
    }
    clear(current_root->left);
    clear(current_root->right);
    delete current_root;
}

template <class T>
typename binary_tree<T>::node* binary_tree<T>::scheme_deserialize(std::istream& in)
{
    assert(in.peek() == '(');
    in.get();
    if (in.peek() == ')')
    {
        in.get();
        return nullptr;
    }
    T data;
    in >> data;
    node *left = scheme_deserialize(in);
    node *right = scheme_deserialize(in);
    assert(in.peek() == ')');
    in.get();
    return new node {data, left, right};
}

template <class T>
void binary_tree<T>::scheme_serialize(std::ostream& out, binary_tree<T>::node* current)
{
    if (!current)
    {
        out << "()";
        return;
    }
    out << "(" << current->data;
    scheme_serialize(out, current->left);
    scheme_serialize(out, current->right);
    out << ")";
}

#endif