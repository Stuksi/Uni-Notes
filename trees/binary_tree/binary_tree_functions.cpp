#ifndef __binary_tree_functions_h
#define __binary_tree_functions_h

#include "binary_tree_functions.h"

#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

template <class T>
size_t size(typename binary_tree<T>::position tree)
{
    if (tree.empty())
    {
        return 0;
    }
    return 1 + size<T>(tree.left()) + size<T>(tree.right());
}

template <class T>
size_t search_count(typename binary_tree<T>::position tree, std::function<bool(const T&)> pred)
{
    if (tree.empty())
    {
        return 0;
    }
    return pred(tree.get()) + search_count<T>(tree.left(), pred) + search_count<T>(tree.right(), pred);
}

template <class T>
size_t height(typename binary_tree<T>::position tree)
{
    if (tree.empty())
    {
        return 0;
    }
    return 1 + std::max(height<T>(tree.left()), height<T>(tree.right()));
}

template <class T>
size_t count_leaves(typename binary_tree<T>::position tree)
{
    if (tree.empty())
    {
        return 0;
    }
    if (tree.left().empty() && tree.right().empty())
    {
        return 1;
    }
    return count_leaves<T>(tree.left()) + count_leaves<T>(tree.right());
}

template <class T>
T max_leaf(typename binary_tree<T>::position tree)
{
    if (tree.empty())
    {
        throw std::out_of_range("Null Tree!");
    }
    if (tree.left().empty() && tree.right().empty())
    {
        return tree.get();
    }
    return tree.left().empty() ? 
                max_leaf<T>(tree.right())
                :
                tree.right().empty() ?
                    max_leaf<T>(tree.left())
                    :
                    std::max(max_leaf<T>(tree.left()), max_leaf<T>(tree.right()));
}

template <class T>
T get_element(typename binary_tree<T>::position tree, const char* path)
{
    if (!*path || tree.empty())
    {
        if (tree.empty())
        {
            throw std::out_of_range("Null Tree!");
        }
        return tree.get();
    }
    if (*path == 'L')
    {
        return get_element<T>(tree.left(), ++path);
    }
    return get_element<T>(tree.right(), ++path);
}

template <class T>
void visualize(typename binary_tree<T>::position tree, std::ofstream& out)
{
    if (tree.empty())
    {
        return;
    }
    out << (long)tree.tree_node() << "[label=\"" << tree.get() << "\"]\n";
    if (!tree.left().empty())
    {
        out << (long)tree.tree_node() << "->" << (long)tree.left().tree_node() << "\n";
    }
    if (!tree.right().empty())
    {
        out << (long)tree.tree_node() << "->" << (long)tree.right().tree_node() << " [color=red]\n";
    }
    visualize<T>(tree.left(), out);
    visualize<T>(tree.right(), out);
}

template <class T>
void pretty_print(typename binary_tree<T>::position tree)
{
    assert(!tree.empty());
    struct pair
    {
        typename binary_tree<T>::position tree;
        size_t indentation;
    };
    size_t index = 1;
    std::stack<pair> s;
    s.push(pair {tree, 0});
    while (!s.empty())
    {
        if (s.top().tree.empty())
        {
            s.pop();
        } 
        else 
        {
            while (!s.top().tree.right().empty())
            {
                s.push (pair {s.top().tree.right(), s.top().indentation + 4});
            }
        }
        if (!s.empty())
        {
            pair top = s.top(); s.pop();
            std::cout << index++ << ": ";
            index = index == 10 ? 1 : index; 
            for (size_t i = 0; i < top.indentation; i++) std::cout << " ";
            std::cout << top.tree.get() << std::endl;
            s.push(pair {top.tree.left(), top.indentation + 4});
        }
    }
}

template <class T>
std::vector<T> list_leaves(typename binary_tree<T>::position tree)
{
    assert(!tree.empty());
    std::stack<typename binary_tree<T>::position> s;
    std::vector<T> list;
    s.push(tree);
    while (!s.empty())
    {
        typename binary_tree<T>::position top = s.top();
        s.pop();
        if (top.left().empty() && top.right().empty())
        {
            list.push_back(top.get());
        }
        else
        {
            if (!top.right().empty())
            {
                s.push(top.right());
            }
            if (!top.left().empty())
            {
                s.push(top.left());
            }
        }
    }
    return list;
}

template <class T>
std::string find_trace(typename binary_tree<T>::position tree, const T& data)
{
    assert(!tree.empty());
    struct pair
    {
        typename binary_tree<T>::position tree;
        std::string trace;
    };
    std::queue<pair> q;

    q.push(pair{tree, ""});
    while (!q.empty() && q.front().tree.get() != data)
    {
        pair front = q.front(); q.pop();
        if (!front.tree.left().empty())
        {
            q.push({front.tree.left(), front.trace + "L"});
        }
        if (!front.tree.right().empty())
        {
            q.push({front.tree.right(), front.trace + "R"});
        }
    }
    return q.empty() ? "_" : q.front().trace;
}

template <class T>
T get_at(typename binary_tree<T>::position tree, int i)
{
    assert(!tree.empty());
    std::queue<typename binary_tree<T>::position> q;
    q.push(tree);
    while (!q.empty() && i--)
    {
        typename binary_tree<T>::position front = q.front();
        q.pop();
        if (!front.left().empty())
        {
            q.push(front.left());
        }
        if (!front.right().empty())
        {
            q.push(front.right());
        }
    }
    assert(!q.empty());
    return q.front().get();
}

int evaluate_expression(typename binary_tree<char>::position tree)
{
    assert(!tree.empty());
    std::stack<typename binary_tree<char>::position> s;
    std::stack<char> operators, operands;

    s.push(tree);
    while (!s.empty())
    {
        typename binary_tree<char>::position top = s.top(); s.pop();
        if (top.get() == '+' || top.get() == '-' || top.get() == '*' || top.get() == '/')
        {
            operators.push(top.get());
        }
        else
        {
            operands.push(top.get());
        }
        if (!top.left().empty())
        {
            s.push(top.right());
            s.push(top.left());
        }
    }
    
    while (!operators.empty())
    {
        char oper = operators.top(); operators.pop();
        char operand = operands.top(); operands.pop();
        switch (oper)
        {
        case '+':
            operands.top() = '0' + (operands.top()-'0') + (operand-'0'); 
            break;
        case '-':
            operands.top() = '0' + (operands.top()-'0') - (operand-'0'); 
            break;
        case '*':
            operands.top() = '0' + (operands.top()-'0') * (operand-'0'); 
            break;
        case '/':
            operands.top() = '0' + (operands.top()-'0') / (operand-'0'); 
            break;
        default:
            break;
        }
    }
    
    return operands.top()-'0';
}

#endif