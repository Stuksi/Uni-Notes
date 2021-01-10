#include <iostream>

template <class T>
struct node
{
    T data;
    node *left, *right;
};

template <class T>
int count(node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + count(root->left) + count(root->right);
}

template <class T>
int count_even(node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return (root->data % 2 == 0) + count_even(root->left) + count_even(root->right);
}

template <class T>
int search_count(node<T>* root, bool (*pred)(const T&)) 
{
    if (root == nullptr)
    {
        return 0;
    }
    return pred(root->data) + search_count(root->left, pred) + search_count(root->right, pred);
}

template <class T>
int height(node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

template <class T>
int count_leaves(node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }
    return count_leaves(root->left) + count_leaves(root->right);
}

template <class T>
T max_leaf(node<T>* root)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        return root->data;
    }
    T _max_leaf;
    if (root->left)
    {
        _max_leaf = max_leaf(root->left);
        if (root->right)
        {
            _max_leaf = std::max(_max_leaf, max_leaf(root->right));
        }
    }
    else
    {
        _max_leaf = max_leaf(root->right);
    }
    return _max_leaf;
}

template <class T>
T& get_element(node<T>* root, const char* path)
{
    node<T>* temp = root;
    while (temp && *path)
    {
        if (path[0] == 'L')
        {
            temp = temp->left;
        }
        else if (path[0] == 'R')
        {
            temp = temp->right;
        }
        else 
        {
            throw "Invalid character in path!";
        }
        ++path;
    }

    if (temp == nullptr)
    {
        throw "Invalid path!";
    }
    
    return temp->data;
}

template <class T>
void free(node<T>* root)
{
    if (root == nullptr)
    {
        return;
    }
    free(root->left);
    free(root->right);
    delete root;
}

template <class T>
bool example_pred(const T& data)
{
    return data % 2 == 1 || data % 2 == -1;
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
                                    -1, 
                                    nullptr, 
                                    nullptr
                                },
                            nullptr
                        }
                    };

    std::cout << "Count: " << count(tree) << std::endl;
    std::cout << "Count even: " << count_even(tree) << std::endl;
    std::cout << "Search count: " << search_count(tree, example_pred) << std::endl;
    std::cout << "Height: " << height(tree) << std::endl;
    std::cout << "Count leaves: " << count_leaves(tree) << std::endl;
    std::cout << "Max leaf: " << max_leaf(tree) << std::endl;
    std::cout << "Get element: " << get_element(tree, "LRL") << std::endl;

    free(tree);

    return 0;
}