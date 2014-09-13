#include <string>
#include <sys/time.h>
#include <map>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
    private:
        bool searchScramble( string &s1, string &s2,
                int begin1, int begin2, int len,
                map<int, map<int ,map<int, bool> > > &accessed) {
            if ( accessed.find(begin1) != accessed.end() ) {
                if ( accessed[begin1].find(begin2) != accessed[begin1].end() ) {
                    if (accessed[begin1][begin2].find(len) != accessed[begin1][begin2].end() ) {
                        return accessed[begin1][begin2][len];
                    }
                }
            }
            if (s1.substr(begin1, len) == s2.substr(begin2, len)) {
                accessed[begin1][begin2][len] = true;
                return true;
            } else if ( len == 1) {
                accessed[begin1][begin2][len] = false;
                return false;
            }
            for ( int i = 0; i < len-1; i ++) {
                bool flag1 = searchScramble(s1, s2, begin1, begin2, i+1, accessed);
                if (flag1) {
                    bool flag2 = searchScramble(s1, s2, begin1+i+1, begin2+i+1, len - i - 1, accessed);
                    if (flag2)  {
                        accessed[begin1][begin2][len] = true;
                        return true;
                    }
                }
                flag1 = searchScramble(s1, s2, begin1, begin2+len-i-1, i+1, accessed);
                if (flag1) {
                    bool flag2 = searchScramble(s1, s2, begin1+i, begin2, len - i - 1, accessed);
                    if (flag2)  {
                        accessed[begin1][begin2][len] = true;
                        return true;
                    }
                }
            }
            accessed[begin1][begin2][len] = false;
            return false;
        }
    public:
        bool isScramble(string s1, string s2) {
            if (s1.size() != s2.size()) return false;
            map<int, map<int ,map<int, bool> > > accessed;
            return searchScramble(s1, s2, 0, 0, s1.size(), accessed);
        }
};
int main(int argc, char *argv[]) {
    string s1("pcighfdjnbwfkohtklrecxnooxyipj");
    string s2("npodkfchrfpxliocgtnykhxwjbojie");
    timeval first, second;
    Solution s;
    gettimeofday( &first, NULL);
    cout << s.isScramble(s1, s2) << endl;
    gettimeofday( &second, NULL);
    cout << "time cost is ---- " 
        << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    return 1;
}
