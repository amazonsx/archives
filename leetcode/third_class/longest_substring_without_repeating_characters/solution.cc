#include <iostream>
#include <algorithm>
#include <map>
#define DEBUG
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s);
};

int Solution::lengthOfLongestSubstring(string s) {  
    int maxlen = 0, begin = 0;
    map<char, int> charLoc;
    for ( int i = 0; i < s.size(); i ++ ) {
        if (charLoc.find(s[i]) != charLoc.end() && charLoc[s[i]] >= begin) {
            begin = charLoc[s[i]] + 1;
        }
        charLoc[s[i]] = i;
        maxlen = max(maxlen, i - begin + 1);
    }
    return maxlen;
}

int main(int argc, char *argv[]) {
    string str("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco");
    Solution s;
    cout << s.lengthOfLongestSubstring(str) << endl;
	return 1;
}

