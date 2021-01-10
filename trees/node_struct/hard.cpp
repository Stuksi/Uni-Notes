#include <iostream>
#include <stack>
#include <queue>
#include <cmath>

template <class T>
struct node
{
    T data;
    node *left, *right;
};

node<int>* balanced_tree(size_t height)
{
    std::stack<node<int>*> s;
    node<int>* root = new node<int> {0, nullptr, nullptr};

    s.push(root);
    while (!s.empty())
    {
        node<int>* top = s.top();
        s.pop();
        if (top->data + 1 != height)
        {
            top->left = new node<int> {top->data + 1, nullptr, nullptr};
            top->right = new node<int> {top->data + 1, nullptr, nullptr};
            s.push(top->left);
            s.push(top->right);
        }
    }
    
    return root;
}

node<char>* leaf_string_tree(std::string str)
{
    if (str.length() == 0)
    {
        return nullptr;
    }
    else if (str.length() == 1)
    {
        return new node<char> {str[0], nullptr, nullptr};
    }

    struct node_level
    {
        node<char>* root;
        int level;
    };
    int height = std::ceil(log2(str.length()));
    std::queue<node_level> q;
    node<char>* root = new node<char> {' ', nullptr, nullptr};

    q.push(node_level {root, 0});
    while (!q.empty() && !str.empty())
    {
        node_level front = q.front();
        q.pop();

        if(front.level + 1 < height)
        {
            front.root->left = new node<char> {' ', nullptr, nullptr};
            front.root->right = new node<char> {' ', nullptr, nullptr};
            q.push(node_level {front.root->left, front.level + 1});
            q.push(node_level {front.root->right, front.level + 1});
        }
        else if (front.level + 1 == height)
        {
            front.root->left = new node<char> {str[0], nullptr, nullptr};
            str.erase(0, 1);
            if (str.empty())
            {
                break;
            }
            front.root->right = new node<char> {str[0], nullptr, nullptr};
            str.erase(0, 1);
        }
    }
    
    return root;
}

template <class T>
node<int>* count_tree(node<T>* root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    node<int>* current = new node<int> {1, nullptr, nullptr};
    current->left = count_tree(root->left);
    current->right = count_tree(root->right);
    current->data += (current->left == nullptr ? 0 : current->left->data) + (current->right == nullptr ? 0 : current->right->data);
    return current;
}

node<std::string>* balance_string_tree(node<std::string>* root)
{
    struct node_level
    {
        node<std::string>* root;
        int level;
    };
    std::vector<std::string> values;
    std::stack<node_level> s;

    s.push(node_level{root, 0});
    while (!s.empty())
    {
        node_level top = s.top();
        s.pop();
        if (values.size() <= top.level)
        {
            values.push_back(top.root->data);
        }
        else
        {
            values[top.level] += top.root->data;
        }
        if (top.root->right)
        {
            s.push(node_level{top.root->right, top.level+1});
        }
        if (top.root->left)
        {
            s.push(node_level{top.root->left, top.level+1});
        }
    }
    
    node<std::string>* tree = new node<std::string> {values[0], nullptr, nullptr};
    std::vector<int> lengths;
    for (size_t i = 0; i < values.size(); i++)
    {
        lengths.push_back(values[i].size()/std::pow(2, i));
    }

    s.push(node_level{tree, 0});
    while (!s.empty())
    {
        node_level top = s.top();
        s.pop();

        if (top.level + 1 < values.size())
        {
            std::string& value = values[top.level+1];
            top.root->left = new node<std::string> {value.substr(0, lengths[top.level+1]), nullptr, nullptr};
            value.erase(0, lengths[top.level+1]);
            top.root->right = new node<std::string> {value.substr(0, lengths[top.level+1]), nullptr, nullptr};
            value.erase(0, lengths[top.level+1]);
            s.push(node_level{top.root->right, top.level+1});
            s.push(node_level{top.root->left, top.level+1});
        }
    }
    
    node<std::string>* temp = tree->right;
    int level = 1;
    while (temp != nullptr)
    {
        if (values[level].size() > 0)
        {
            temp->data += values[level];
        }
        temp = temp->right;
        level++;
    }
    
    return tree;
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

    node<int>* balanced = balanced_tree(3);
    std::cout << "Balanced tree: " << std::endl;
    prettyPrint(balanced);
    std::cout << std::endl;
    
    node<char>* leaf_string = leaf_string_tree("Hello world");
    std::cout << "String tree: " << std::endl;
    prettyPrint(leaf_string);
    std::cout << std::endl;

    node<int>* count_t = count_tree(tree);
    std::cout << "Count tree: " << std::endl;
    prettyPrint(count_t);
    std::cout << std::endl;

    node<std::string> *string_tree = new node<std::string> 
                            {
                                "BALANCING", 
                                new node<std::string> 
                                {
                                    "A STRING", 
                                    new node<std::string> 
                                    {
                                        "BY ITS", 
                                        nullptr, 
                                        nullptr
                                    },
                                    new node<std::string> 
                                    {
                                        "STRING LENGTHS", 
                                        new node<std::string> 
                                        {
                                            "COOL RIGHT?", 
                                            nullptr, 
                                            nullptr
                                        },
                                        nullptr
                                    }
                                },
                                new node<std::string> 
                                {   
                                    "TREEEE",
                                    new node<std::string> 
                                        {
                                            "INSIDE THE TREE", 
                                            nullptr, 
                                            nullptr
                                        },
                                    nullptr
                                }
                            };

    node<std::string>* balanced_string_tree_root = balance_string_tree(string_tree);
    std::cout << "Balanced string tree:" << std::endl;
    prettyPrint(balanced_string_tree_root);
    std::cout << std::endl;

    free(string_tree);
    free(tree);
    free(balanced_string_tree_root);
    free(balanced);
    free(leaf_string);
    free(count_t);

    return 0;
}