#ifndef __binary_tree_h
#define __binary_tree_h

#include <iostream>
#include <stack>

template <class T>
class binary_tree
{
private:
    struct node
    {
        T data;
        node *left, *right;
    };
    node *root;


public:
    binary_tree();
    binary_tree(const binary_tree&);
    binary_tree& operator= (const binary_tree&);
    ~binary_tree();

    binary_tree& insert(const T&);
    
    binary_tree& from_scheme(std::istream&);
    binary_tree& to_scheme(std::ostream&);

    binary_tree& parse_expression(std::istream&);
    
    binary_tree<int>& generate_balanced_tree(size_t);
    binary_tree<char>& generate_string_tree(const char*);
    binary_tree<int>& generate_edge_count_tree();


public:
    class position
    {
    private:
        node*& current;
    public:
        position(node*&);

        position left() const;
        position right() const;
        bool empty() const;
        void set(const T&);
        T get() const;
        node* tree_node() const; 
    };

    position root_position();


public:
    class iterator
    {
    private:
        std::stack<position> s;
    public:
        iterator(position, bool);
        T operator*();
        iterator& operator++();
        bool operator!=(const iterator&);
    };

    iterator begin();
    iterator end();


private:
    void copy(node**, node*);
    void clear(node*);

    node* scheme_deserialize(std::istream&);
    void scheme_serialize(std::ostream&, node*);

    node* expression_deserialize(std::istream&);

    void edge_count_conversion(node*&);


};

#include "binary_tree.cpp"

#endif