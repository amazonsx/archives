#include <iostream>
#include <map>
#define DEBUG
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s);
};

int Solution::lengthOfLongestSubstring(string s) {  
    int max = 0, start = 0, tmpMax = 0;
    map<char, int> locMap;
    int current = 0;
    while (current < (signed)s.size()) {
        if (locMap.find(s[current]) != locMap.end()) {
            if (locMap[s[current]] >= start) {
                if (tmpMax > max) {
                    max = tmpMax;
                    cout << locMap[s[current]]  << "   "<< current << endl;
                    start = locMap[s[current]] + 1;
                    tmpMax = current - start;
                }
            }
        }
        tmpMax ++;
        locMap[s[current]] = current;
        current ++;
    }
    if (max < tmpMax)
        max = tmpMax;
    return max;
}

int main(int argc, char *argv[]) {
    string str("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco");
    Solution s;
    cout << s.lengthOfLongestSubstring(str) << endl;
	return 1;
}

