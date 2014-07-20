#include <iostream>
#include <vector>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
public:
    int minCutWA(string s);
    int minCut(string s);

};

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

int Solution::minCutWA(string s) {
    if( (s.size() == 0) && (s.size() == 1))  return 0;
    int head = 0, tail = s.size() - 1;
    int totalLen = 0, res = 0;
    while (totalLen != (signed)s.size() ) {
        while( tail >= head )  {
            int currentLeft = head, currentRight = tail, flag = 1;
            while (currentLeft <= currentRight) {
                if (s[currentLeft] == s[currentRight]) {
                    currentLeft ++;
                    currentRight --;
                } else {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                totalLen += tail - head + 1;
                res ++;
                head = tail + 1;
                tail = s.size() - 1;
                break;
            } else tail --;
        }
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
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str2("abcdcbaeedf");
    cout << str2 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str2)  << "   expected    " << 3 << endl;
    gettimeofday(&second, NULL);
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str3("abcdefghijklmnn");
    cout << str3 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str3) << "    expected    " << 13 << endl;
    gettimeofday(&second, NULL);
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    // corner case
    string str4("aaabaa");
    cout << str4 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str4) << "    expected    " << 1 << endl;
    gettimeofday(&second, NULL);
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str5("ab");
    cout << str5 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str5) << "    expected    " << 1 << endl;
    gettimeofday(&second, NULL);
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str6("ababbbabbaba");
    cout << str6 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str6) << "    expected    " << 3 << endl;
    gettimeofday(&second, NULL);
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;

    string str7("ccaacabacb");
    cout << str7 << endl;
    gettimeofday(&first, NULL);
    cout << s.minCut(str7) << "    expected    " << 3 << endl;
    gettimeofday(&second, NULL);
    cout << 10000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
	return 1;
}
