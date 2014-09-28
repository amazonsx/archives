#include <iostream>
#include <vector>
#include <string>
#define DEBUG
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs);
};

string Solution::longestCommonPrefix(vector<string> &strs) {
    if (strs.empty())   return "";
    int index = 0;
    while (true) {
        if ( index == (signed)strs[0].size())  break;
        char current = strs[0][index];
        bool flag = true;
        for ( int i = 1; i < (signed)strs.size(); i ++) {
            if ((signed)strs[i].size() == index) {
                flag = false;
                break;
            }
            if (strs[i][index] != current) {
                flag = false;
                break;
            }
        }
        if (!flag)  break;
        index ++;
    }
    return strs[0].substr(0, index);
}

int main(int argc, char *argv[]) {
    string a("");
    vector<string> strs;
    strs.push_back(a);
    Solution s;
    cout << s.longestCommonPrefix(strs) << endl;
	return 1;
}
