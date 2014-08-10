#include <iostream>
#include <string>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    bool isPalindrome(string &str);
public:
    vector<string> anagrams(vector<string> &strs);
};

bool Solution::isPalindrome(string &str1, string &str2) {
    if (str1.size() != str2.size()) return false;
    int len = str1.size();
    int begin = 0, end = len - 1;
    while (begin < len) {
        if (str1[begin++] != str2[end--])
            return false;
    }
    return true;
}

vector<string> Solution::anagrams(vector<string> &strs) {
    int len = (signed) strs.size();
    vector<string> res;



    return res;
}

int main(int argc, char *argv[]) {
    vector<string> strs;
    strs.push_back("");
    //strs.push_back("");

    Solution s;
    vector<string> res = s.anagrams(strs);

    cout << res.size() << endl;
	return 1;
}

