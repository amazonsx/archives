#include <iostream>
#include <string>
#define DEBUG
using namespace std;

class Solution {
public:
    string countAndSay(int n);
};

string Solution::countAndSay(int n) {
    if ( n == 1 )   return "1";
    string former = countAndSay(n-1);
    string res("");
    int sameCount = 1;
    for ( int i = 1; i < (signed)former.size(); i ++) {
        if ( former[i] == former[i-1]) sameCount ++;
        else  {
            res += to_string((long long)sameCount);
            res += former[i-1];
            sameCount = 1;
        }
    }
    res += to_string((long long)sameCount);
    res += former[former.size()-1];
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    for ( int i = 1; i <= 20; i ++) {
        cout << s.countAndSay(i) << endl;
    }
	return 1;
}
