#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

void clear_string(std::string& s)
{
    char last = s[s.length()-1], first = s[0];
    if (last == '.' || last == ',' || last == ')')
    {
        s.pop_back();
    }
    if (first == '(')
    {
        s.erase(0, 1);
    }
}

void text_monitoring(std::string txt1, std::string txt2)
{
    std::stringstream ss1(txt1), ss2(txt2);
    std::string s;
    std::unordered_map<std::string, int> m1, m2;

    while (ss1 >> s)
    {
        clear_string(s);
        m1[s]++;
    }

    while (ss2 >> s)
    {
        clear_string(s);
        m2[s]++;
    }
    
    for (std::pair<std::string, int> p : m2)
    {
        if (m1.find(p.first) != m1.end())
        {
            std::cout << p.first << " : " << p.second << std::endl;
        }
    }
}

int text_unique_words_count(std::string txt1, std::string txt2)
{
    std::stringstream ss1(txt1), ss2(txt2);
    std::string s;
    std::unordered_set<std::string> m1, m2;

    while (ss1 >> s)
    {
        clear_string(s);
        m1.insert(s);
    }

    while (ss2 >> s)
    {
        clear_string(s);
        m2.insert(s);
    }
    
    int count = 0;
    for (std::string str : m2)
    {
        if (m1.find(str) != m1.end())
        {
            count++;
        }
    }

    return count;
}

std::string text_word_monitoring(std::string txt)
{
    std::stringstream ss(txt);
    std::string s;
    std::unordered_map<std::string, int> m;

    while (ss >> s)
    {
        clear_string(s);
        if (s.length() >= 3)
        {
            m[s]++;
        }
    }

    if (m.empty())
    {
        throw "Invalid text!";
    }

    std::pair<std::string, int> max_pair = *m.begin();
    for (std::pair<std::string, int> p : m)
    {
        max_pair = p.second > max_pair.second ? p : max_pair; 
    }

    return max_pair.first;
}

bool hash_monitoring(int n)
{
    std::unordered_map<size_t, size_t> m;
    int a, b;
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> a >> b;
        if (m.find(a) != m.end() && m[a] != b)
        {
            return false;
        }
        m[a] = b;
    }
    return true;
}

int main()
{
    std::string txt1 = "In computing, a hash table (hash map) is a data structure used to implement "
        "an associative array, a structure that can map keys to values. A hash table "
        "uses a hash function to compute an index into an array of buckets or slots, "
        "from which the correct value can be found.";
    
    std::string txt2 = "Ideally, the hash function will assign each key to a unique bucket, but this "
        "situation is rarely achievable in practice (usually some keys will hash to the "
        "same bucket)";

    std::cout << "Text monitoring: " << std::endl;
    text_monitoring(txt1, txt2);
    std::cout << std::endl;

    std::cout << "Text unique words count: " << text_unique_words_count(txt1, txt2) << std::endl;
    std::cout << std::endl;

    std::cout << "Text word monitoring: " << text_word_monitoring(txt1) << std::endl;
    std::cout << std::endl;

    std::cout << "Hash monitoring: " << hash_monitoring(3) << std::endl;
    std::cout << std::endl;

    return 0;
}