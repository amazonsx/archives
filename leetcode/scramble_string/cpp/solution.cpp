#include <iostream>
#include <map>
#include <string>
#define DEBUG
using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2);
};

bool Solution::isScramble(string s1, string s2) {
    if (s1.size() != s2.size()) return false;
    if (s1 == s2)   return true;
    int begin = -1, end = -1;

    map<char, int> origin_map;
    map<char, int> scramble_map;

    for (int j = (signed)s1.size() - 1; j >= 0; j --) {
        if (s1[j] != s2[j]) {
            end = j;
            break;
        }
    }

    for (int i = 0; i <= end; i ++) {
        if ((s1[i] != s2[i]) && (begin == -1)) {
            begin = i;
        }
        if ( (begin != -1) && (i >= begin)) {
            origin_map[s1[i]] ++;
            scramble_map[s2[i]] ++;
        }
    }

    if (origin_map != scramble_map) return false;

    
    return true;
}

int main(int argc, char *argv[]) {
    /*
    string s1("ab");
    string s2("ba");
    */

    /*
    string s1("abb");
    string s2("bab");
    */

    /*
    string s1("abc");
    string s2("acb");
    */
    string s1("abc");
    string s2("bca");
    Solution s;
    cout << s.isScramble(s1, s2) << endl;
	return 1;
}
