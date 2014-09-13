#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <vector>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
private:
    int nextPalindrome( map<int, map<int, bool> > &parMap, string &s, int current, map<int, int> &best);
    bool recognizePalindrome(map<int, map<int, bool> > &parMap, string &s,
            int start, int end);
public:
    int minCutWA(string s);
    int minCut(string s);
    int minCutBest(string s);
    int minCutSX(string s);
};

int Solution::minCutBest(string s) {
    int N = s.size();
    vector<int> dp(N+1,numeric_limits<int>::max());
    dp[0] = 0;
    for(int i=0;i<N;i++) {
        for(int p=0;p<=1;p++) {
            for(int l=0;l<=N;l++) {
                int a=i-l, b = i+l+p;
                if( a < 0 || b >= N || s[a]!=s[b] )
                    break;
                dp[b+1] = min(dp[b+1],dp[a]+1);
            }
        }
    }
    return dp[N]-1;
}

int Solution::nextPalindrome( map<int, map<int, bool> > &parMap, 
        string &s, int current, map<int, int> &bestCut) {
    if (bestCut.find(current) != bestCut.end()) {
        return bestCut[current];
    }
    int min = s.size() - current;
    for ( map<int, bool>::iterator iter = parMap[current].begin();
            iter != parMap[current].end(); iter ++) {
        if (iter->second == false)  continue;
        if ((iter->first+1) == (signed)s.size()) {
            min = 0;
            break;
        }
        int tmp = nextPalindrome(parMap, s, iter->first + 1, bestCut) + 1;
        if (tmp < min)  min = tmp;
    }
    bestCut[current] = min;
    return min;
}

bool Solution::recognizePalindrome(map<int, map<int, bool> > &parMap, string &s, 
        int start, int end){
    if (parMap.find(start) != parMap.end()) {
        if (parMap[start].find(end) != parMap[start].end()) {
            return parMap[start][end];
        }
    }
    int len = end - start + 1;
    if ( len == 1) {
        parMap[start][end] = true;
        return true;
    } else if (len == 2) {
        bool flag = false;
        if (s[start] == s[end]) {
            flag = true;
        }
        parMap[start][end] = flag;
        return flag;
    }
    bool flag = false;
    if ( s[start] == s[end]) {
        flag = recognizePalindrome(parMap, s, start + 1, end - 1);
    }
    parMap[start][end] = flag;
    return flag;
}

int Solution::minCut(string s) {
    map<int, map<int, bool> > parMap;
    for ( int i = 0; i < (signed)s.size(); i ++) {
        for ( int j = i; j < (signed)s.size(); j ++) {
            recognizePalindrome(parMap, s, i, j);
        }
    }
    map<int, int> bestCut;
    return nextPalindrome(parMap, s, 0, bestCut); 
}

int Solution::minCutWA( string s){
    if( (s.size() == 0) || (s.size() == 1))  return 0;
    int head = 0, tail = s.size() - 1;
    int totalLen = 0, res = 0;
    while (totalLen < (signed)s.size()) {
        int i = 0;
        while(s[head+i] == s[head] ) {
            i++;
            if ( i >= (signed)s.size()) break;
        }
        int minStart = head;
        int maxTail = head, foundBest = 0;
        for ( int j = 0; j < i; j ++ ) {
            if (foundBest)  break;
            while(tail >= head) {
                int leftCurrent = head, rightCurrent = tail, flag = 1; 
                while(leftCurrent <= rightCurrent) {
                    if(s[leftCurrent] == s[rightCurrent]) {
                        leftCurrent ++;
                        rightCurrent --;
                    } else {
                        flag = 0;
                        break;
                    }
                }
                if (flag) { 
                    if(maxTail <= tail)  {
                        if ((maxTail < tail) && (i != 1) && (j == (i-1)))
                            res ++;
                        maxTail = tail;
                    } else {
                        res ++;
                        foundBest = 1;
                        break;
                    }
                    tail = s.size() - 1;
                    head = head + 1;
                    break;
                } else tail --;
            }
        }
        head = maxTail + 1;
        tail = s.size() - 1;
        totalLen += maxTail - minStart + 1;
        res ++;
    }
    return res - 1;
}

int main(int argc, char *argv[]) {
    Solution s;
    string str1("aab");
    cout << str1 << endl;
    struct timeval first;
    gettimeofday(&first, NULL);
    cout << s.minCut(str1)  << "   expected    " << 1 << endl;
    struct timeval second;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str2("abcdcbaeedf");
    cout << str2 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str2)  << "   expected    " << 3 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str3("abcdefghijklmnn");
    cout << str3 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str3) << "    expected    " << 13 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    // corner case
    string str4("aaabaa");
    cout << str4 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str4) << "    expected    " << 1 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str5("ab");
    cout << str5 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str5) << "    expected    " << 1 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str6("ababbbabbaba");
    cout << str6 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str6) << "    expected    " << 3 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str7("ccaacabacb");
    cout << str7 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str7) << "    expected    " << 3 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str8("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    cout << str8 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str8) << "    expected    " << 1 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
    gettimeofday(&first, NULL);
    cout << s.minCutBest(str8) << "    expected    " << 1 << endl;
    gettimeofday(&second, NULL);
    cout << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
	return 1;
}
