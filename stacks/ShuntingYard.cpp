#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>

#define THEN {result += oper.top(); oper.pop(); result += " ";} 

using namespace std;

int calculate_special_operator(char oper, int num) {
    switch (oper) {
        case 'c': return sin(num);
        default: return ceil(sqrt(num));
    }
}

int calculate_operator(char oper, int num1, int num2) {
    switch (oper) {
        case '+': return num1 + num2;        
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        default: return num1 / num2;
    }
}

bool is_special_operator(char oper) {
    return oper == 'c' || oper == 's';
}

bool is_operator(char oper) {
    return oper == '+' || oper == '-' 
        || oper == '*' || oper == '/';
}

string shunting_yard(string& s) {
    stack<string> oper;
    string result = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        if(s[i] == 'c' && s[i+1] == 'o') {
            oper.push("cos");
        } else if(s[i] == 's' && s[i+1] == 'q') {
            oper.push("sqrt");
        } else if(s[i] == '(') {
            oper.push(s.substr(i, 1));
        } else if(s[i] == ')') {
            while(oper.top() != "(") THEN
            oper.pop(); 
        } else if(s[i] == '*' || s[i] == '/' && (oper.top() == "+" || oper.top() == "-")) {
            oper.push(s.substr(i, 1));
        } else if(is_operator(s[i])) {
            while(!oper.empty() && oper.top() != "(") THEN
            oper.push(s.substr(i, 1));
        } else if(isdigit(s[i])) {
            while (i < s.length() && isdigit(s[i])) {
                result += s[i];
                i++;
            }
            result += " ";
        }
    }
    while(!oper.empty()) THEN
    return result;
}

int calculate_postfix(string &s) {
    stack<int> nums;
    int num;
    for (size_t i = 0; i < s.length(); i++) {
        if(is_operator(s[i])) {
            num = nums.top();
            nums.pop();
            nums.top() = calculate_operator(s[i], nums.top(), num); 
        } else if(is_special_operator(s[i])) {
            nums.top() = calculate_special_operator(s[i], nums.top());
        }
        if(isdigit(s[i])) {
            num = 0;
            while (i < s.length() && isdigit(s[i])) {
                num = num*10 + s[i]-'0';
                i++;
            }
            nums.push(num);
        }
    }
    return nums.top();
}

int main() {

    string calc, result;
    while (true) {
        getline(cin, calc);
        result = shunting_yard(calc);
        cout << result << endl;
        cout << calculate_postfix(result) << endl;
    }    

    return 0;
}