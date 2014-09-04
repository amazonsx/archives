#include <iostream>
#include <string>
#include <string.h>
#define DEBUG
using namespace std;

class Solution {
public:
    bool isPalindrome(string s);
};

bool Solution::isPalindrome(string s) {
    if (s.size() == 0)  return true;

    int front = 0, back = s.size() - 1;
    while (front <= back) {
        while (!(((s[front]>='A') && (s[front]<= 'Z')) 
            || ((s[front]>='a') && (s[front]<='z'))
            || ((s[front]>=48 && (s[front]<=57))))) {
            front ++;
            if (front == (signed)s.size())  break;
        }
        while (!(((s[back]>='A') && (s[back]<= 'Z')) 
            || ((s[back]>='a') && (s[back]<='z'))
            || ((s[back]>=48 && (s[back]<=57))))) {
            back --;
            if (back == -1)  break;
        }

        if ((front == (signed)s.size()) && (back == -1))    return true;
        if (front >= back)   return true;
        
        if ((s[front]>='A') && (s[front]<= 'Z')) s[front] += 32;
        if ((s[back]>='A') && (s[back]<= 'Z')) s[back] += 32;

        if (s[front] == s[back]) {
            front ++;
            back --;
        } else return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    Solution s;
    //string str("A man, a plan, a canal: Panama");
    //string str("race a car");
    //string str(" ");
    //string str(",. ");
    //string str("a ba");
    string str("a b2a");
    cout << s.isPalindrome(str) << endl;
	return 1;
}
