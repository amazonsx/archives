#include <iostream>
#include <stack>
#include <string>
#include <map>
#define DEBUG
using namespace std;

class Solution {
public:
    bool isValid( string s);
};

bool Solution::isValid(string s) {
    if (s.empty())  return true;
    stack<char> parStack;
    map<char, char> parMap;
    parMap[')'] = '(';
    parMap[']'] = '[';
    parMap['}'] = '{';
    for ( int i = 0; i < (signed)s.size(); i ++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            parStack.push(s[i]);
        else {
            if (parStack.empty())   return false;
            if (parStack.top() == parMap[s[i]])
                parStack.pop();
        }
    }
    if (!parStack.empty())   return false;
    return true;
}

int main(int argc, char *argv[]) {
	return 1;
}
