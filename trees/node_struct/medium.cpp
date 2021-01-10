#include <iostream>
#include <string>
#include <stack>
#include <vector>

template <class T>
struct node
{
    T data;
    node *left, *right;
};

template <class T>
void prettyPrint(node<T>* root)
{
    struct s_node
    {
        node<T>* root;
        int identation;
    };
    std::stack<s_node> s;

    s.push(s_node{root, 0});
    while (s.size() != 1 || s.top().root != nullptr)
    {
        while (s.top().root != nullptr)
        {
            s.push(s_node {s.top().root->right, s.top().identation+1});
        }
        s.pop();
        s_node top = s.top();
        s.pop();
        for (size_t i = 0; i < top.identation; i++)
        {
            std::cout << "    ";
        }
        std::cout << top.root->data << std::endl;
        s.push(s_node {top.root->left, top.identation+1});
    }
}

// Scheme
std::string serialize_tree(node<int>* root)
{
    if (root == nullptr)
    {
        return "()";
    }
    return "(" + std::to_string(root->data) + " " + serialize_tree(root->left) + " " + serialize_tree(root->right) + ")";
}

// Scheme
node<int>* parse_tree(std::string& scheme_tree)
{
    if (scheme_tree[0] != '(') throw "Syntax error!";
    scheme_tree.erase(0, 1);

    if (scheme_tree[0] == ')')
    {
        scheme_tree.erase(0, 1);
        return nullptr;
    }

    if (!std::isdigit(scheme_tree[0])) throw "Syntax error!";
    int number = 0;
    while (std::isdigit(scheme_tree[0]))
    {
        number = number * 10 + scheme_tree[0] - '0';
        scheme_tree.erase(0, 1);
    }

    node<int> *left = parse_tree(scheme_tree);
    node<int> *right = parse_tree(scheme_tree);

    if (scheme_tree[0] != ')') throw "Syntax error!";
    scheme_tree.erase(0, 1);

    return new node<int>{number, left, right};
}

template <class T>
std::vector<T> list_leaves(node<T>* root)
{
    if (root == nullptr)
    {
        return std::vector<T>();
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        return std::vector<T>(1, root->data);
    }
    std::vector<T> left = list_leaves(root->left);
    std::vector<T> right = list_leaves(root->right);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

template <class T>
std::string find_trace(node<T>* root, const T& value)
{
    if (root == nullptr)
    {
        return "_";
    }
    if (root->data == value)
    {
        return "";
    }
    std::string left = "L" + find_trace(root->left, value);
    if (left[left.length()-1] != '_') return left;
    std::string right = "R" + find_trace(root->right, value);
    if (right[right.length()-1] != '_') return right;
    return "_";
}

template <class T>
T get_at(node<T>* root, size_t i)
{
    std::stack<node<T>*> s;
    s.push(root);
    while (i != 0 && !s.empty())
    {
        node<T>* top = s.top();
        s.pop();
        if (top == nullptr)
        {
            throw "Invalid argument!";
        }
        if (top->right)
        {
            s.push(top->right);
        }
        if (top->left)
        {
            s.push(top->left);
        }
        --i;
    }
    if (s.empty())
    {
        throw "Invalid argument!";
    }
    return s.top()->data;
}

template <class T>
bool palindrome_at(node<T>* root, size_t i)
{
    std::vector<T> values;
    struct node_level
    {
        node<T>* root;
        size_t level;
    };
    std::stack<node_level> s;

    s.push(node_level {root, 0});
    while (!s.empty())
    {
        node_level top = s.top();
        s.pop();
        if (top.level == i)
        {
            values.push_back(top.root->data);
        }
        else 
        {
            if (top.root->left) 
            {
                s.push(node_level {top.root->left, top.level + 1});
            }
            if (top.root->right)
            {
                 s.push(node_level {top.root->right, top.level + 1});
            }
        }
    }

    size_t size = values.size();
    for (size_t i = 0; i < size/2; i++)
    {
        if (values[i] != values[size-1-i])
        {
            return false;
        }
    }
    
    return true;
}

template <class T>
void free(node<T>*& root)
{
    if (root == nullptr)
    {
        return;
    }
    free(root->left);
    free(root->right);
    delete root;
}

int main()
{
    node<int> *tree = new node<int> 
                    {
                        0, 
                        new node<int> 
                        {
                            1, 
                            new node<int> 
                            {
                                2, 
                                nullptr, 
                                nullptr
                            },
                            new node<int> 
                            {
                                2, 
                                new node<int> 
                                {
                                    3, 
                                    nullptr, 
                                    nullptr
                                },
                                nullptr
                            }
                        },
                        new node<int> 
                        {   
                            4,
                            new node<int> 
                            {
                                2, 
                                nullptr, 
                                nullptr
                            },
                            new node<int> 
                            {
                                2, 
                                nullptr, 
                                nullptr
                            }
                        }
                    };

    std::cout << "Pretty print:" << std::endl;
    prettyPrint(tree);
    std::cout << std::endl;

    std::cout << "Palindrom: " << palindrome_at(tree, 1) << std::endl;
    std::cout << std::endl;

    std::cout << "Serialized tree: " << serialize_tree(tree) << std::endl;
    std::cout << std::endl;
    
    std::cout << "Parsed tree: " << std::endl;
    std::string serialization = "(0(1(2()())(2(3()())()))(4(5()())()))";
    node<int>* parsed_tree = parse_tree(serialization);
    prettyPrint(parsed_tree);
    std::cout << std::endl;

    std::cout << "Leaves list: ";
    for (int leaf : list_leaves(tree))
    {
        std::cout << leaf << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Find trace: " << find_trace(tree, 3) << std::endl; 
    std::cout << std::endl;

    std::cout << "Get at: " << get_at(tree, 5) << std::endl;
    std::cout << std::endl;

    free(tree);

    return 0;
}
