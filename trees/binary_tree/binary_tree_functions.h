#ifndef __binary_tree_fucntions_h
#define __binary_tree_fucntions_h

#include <fstream>
#include <functional>
#include <vector>
#include <string>

#include "binary_tree.h"

template <class T>
size_t size(typename binary_tree<T>::position);

template <class T>
size_t search_count(typename binary_tree<T>::position, std::function<bool(const T&)>);

template <class T>
size_t height(typename binary_tree<T>::position);

template <class T>
size_t count_leaves(typename binary_tree<T>::position);

template <class T>
T max_leaf(typename binary_tree<T>::position);

template <class T>
T get_element(typename binary_tree<T>::position, const char*);

template <class T>
void visualize(typename binary_tree<T>::position, std::ofstream&);

template <class T>
void pretty_print(typename binary_tree<T>::position);

template <class T>
std::vector<T> list_leaves(typename binary_tree<T>::position);

template <class T>
std::string find_trace(typename binary_tree<T>::position, const T& data);

template <class T>
T get_at(typename binary_tree<T>::position, int);

int evaluate_expression(typename binary_tree<char>::position);

binary_tree<int> generate_balanced_tree(size_t);

binary_tree<char> generate_string_tree(const char*);

binary_tree<int> convert_edge_count_tree(binary_tree<int>);


#include "binary_tree_functions.cpp"

#endif