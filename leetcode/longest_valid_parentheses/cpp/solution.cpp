#include <iostream>
#include <string>
#include <stack>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s);
};

int Solution::longestValidParentheses(string s) {
    int i = 0;
    stack<int> leftPLoc;
    stack<int> matchCount;
    int res = 0;
    while (i != (signed)s.size()) {
        if (s[i] == '(') {
            leftPLoc.push(i);
            matchCount.push(0);
        } else {
            if (!leftPLoc.empty()) {
                int curMatch = matchCount.top() + 1;
                leftPLoc.pop();
                matchCount.pop();
                if (matchCount.empty()) {
                    matchCount.push(curMatch);
                } else {
                   matchCount.top() += curMatch; 
                }
            } else {
                if (!matchCount.empty()) {
                    if (matchCount.top() > res) res = matchCount.top();
                    matchCount.pop();
                }
            }
        }
        i ++;
    }
    while (!matchCount.empty()) {
        int tmp = matchCount.top();
        if (tmp > res)  res = tmp;
        matchCount.pop();
    }
    return res << 1;
}

int main(int argc, char *argv[]) {
    Solution s;

    string str1("(()");
    cout << s.longestValidParentheses(str1) 
        << " expected ---- " << 2 << endl;

    string str2(")()())");
    cout << s.longestValidParentheses(str2) 
        << " expected ---- " << 4 << endl;

    string str3("))))))))");
    cout << s.longestValidParentheses(str3) 
        << " expected ---- " << 0 << endl;

    string str4(")))()))))");
    cout << s.longestValidParentheses(str4) 
        << " expected ---- " << 2<< endl;

    string str5("(((((((((((((");
    cout << s.longestValidParentheses(str5) 
        << " expected ---- " << 0 << endl;

    string str6("()(()");
    cout << s.longestValidParentheses(str6) 
        << " expected ---- " << 2 << endl;

    string str7("()(())");
    cout << s.longestValidParentheses(str7) 
        << " expected ---- " << 6 << endl;

    string str8("()(()");
    cout << s.longestValidParentheses(str8) 
        << " expected ---- " << 2 << endl;

    string str9("()(()(((");
    cout << s.longestValidParentheses(str9) 
        << " expected ---- " << 2 << endl;

    string str10(")()())()()(");
    cout << s.longestValidParentheses(str10) 
        << " expected ---- " << 4 << endl;
	return 1;
}
