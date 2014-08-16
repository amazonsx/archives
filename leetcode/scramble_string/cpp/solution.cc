#include <iostream>
#include <map>
#include <string>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
    private:
        bool recognizeScramble( string &s1, string &s2, 
                int begin1, int begin2, int len, map<int, map<int, map<int, bool>> > &accessed);
    public:
        bool isScramble(string s1, string s2);
};

bool Solution::recognizeScramble( string &s1, string &s2,
        int begin1, int begin2, int len, map<int, map<int, map<int, bool> > > &accessed) {
    cout << begin1 << "   " << begin2 << "   " << len << endl;
    if ( accessed.find(begin1) != accessed.end()) {
        if (accessed[begin1].find(begin2) != accessed[begin1].end()) {
            if (accessed[begin1][begin2].find(len) != accessed[begin1][begin2].end()) {
                return accessed[begin1][begin2][len];
            }
        }
    }
    if (len == 1) {
        if (s1[begin1] == s2[begin2]) {
            accessed[begin1][begin2][len] = true;
            return true;
        } else {
            accessed[begin1][begin2][len] = false;
            return false;
        }
    }
    bool flag = true;
    if (s1.substr( begin1, len) == s2.substr(begin2, len)) {
        accessed[begin1][begin2][len] = true;
        return true;
    } else {
        for ( int i = 0; i < len; i ++) {
            if ( s1[begin1 + i] != s2[begin2 + len - i - 1]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            accessed[begin1][begin2][len] = true;
            return true;
        }
    }

    for ( int i = 0; i < len-1; i ++) {
        bool leftFlag = recognizeScramble(s1, s2, 
                begin1, begin2 + len - i - 1, i + 1, accessed);
        if (leftFlag) {
            bool rightFlag = recognizeScramble(s1, s2,
                    begin1 + i + 1, begin2, len - i - 1, accessed);
            if (leftFlag && rightFlag) {
                flag = true;
                break;
            }
        }
        leftFlag = recognizeScramble(s1, s2, begin1, begin2, i + 1, accessed);
        if (leftFlag){
            bool rightFlag = recognizeScramble(s1, s2, begin1 + i + 1, begin2 + i + 1, len - i - 1, accessed);
            if (leftFlag && rightFlag) {
                flag = true;
                break;
            }
        }
    }
    accessed[begin1][begin2][len] = flag;
    return flag;
}
bool Solution::isScramble(string s1, string s2) {
    if (s1.size() != s2.size()) return false;
    map<int, map<int,map<int, bool>> > accessed;
    return recognizeScramble( s1, s2, 0, 0, s1.size(), accessed);
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
    /*
       string s1("abc");
       string s2("bca");
       */
    /*
       string s1("great");
       string s2("rgtae");
       */
    /*
       string s1("bbbaaaaccaabbbaa");
       string s2("baababaababacabc");
       */
    string s1("xstjzkfpkggnhjzkpfjoguxvkbuopi");
    string s2("xbouipkvxugojfpkzjhnggkpfkzjts");
    timeval first, second;
    Solution s;
    gettimeofday( &first, NULL);
    cout << s.isScramble(s1, s2) << endl;
    gettimeofday( &second, NULL);
    cout << "time cost is ---- " 
        << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    return 1;
}
