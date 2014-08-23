#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#define DEBUG
using namespace std;

class Solution {
    public:
        bool isPalindrome( string &s, int left, int right);
        vector<vector<string> > partition(string s);
        vector<vector<string> > partitionLessSpace(string s);
        void recognizeNext( vector<vector<string> > &res, vector<string> &path, 
                string &s, vector<vector<int> > &palindromes, int start);
        void recNextPal( vector<vector<string> > &res, vector<string> &path, string &s, int start);
};

void Solution::recNextPal( vector<vector<string> > &res, vector<string> &path, string &s, int start) {
    if ( start == (signed)s.size()) {
        res.push_back(path);
        return;
    }
    for ( int i = start; i < (signed)s.size(); i ++) {
        if (isPalindrome(s, start, i) ) {
            path.push_back(s.substr(start, i-start+1));
            recNextPal(res, path, s, i+1);
            path.pop_back();
        }
    }
}

bool Solution::isPalindrome( string &s, int left, int right) {
    while (left <= right) {
        if (s[left++] != s[right--])   return false;
    }
    return true;
}

void Solution::recognizeNext( vector<vector<string> > &res, vector<string> &path, 
        string &s, vector<vector<int> > &palindromes, int start) {
    if (start == (signed)s.size()) {
        res.push_back(path);
        return;
    }
    for ( int i = 0; i < (signed) palindromes[start].size(); i ++) {
        path.push_back(s.substr(start, palindromes[start][i]-start+1));
        recognizeNext(res, path, s, palindromes, palindromes[start][i] + 1);
        path.pop_back();
    }
}
vector<vector<string> > Solution::partitionLessSpace(string s) {
    vector<vector<string> > res;
    vector<string> path;
    recNextPal(res, path, s, 0);

    return res;
}

vector<vector<string> > Solution::partition(string s) {
    vector<vector<string> > res;
    vector<vector<int> > palindromes(s.size(), vector<int>());

    for ( int i = 0; i < (signed) s.size(); i ++) {
        palindromes[i].push_back(i);
        int odd_left = i, odd_right = i;
        int even_left = i, even_right = i;
        bool oddPal = true, evenPal = true;
        for ( int j = 1; j < (signed) s.size(); j ++) {
            if ( (i + j) >= (signed)s.size())    break;
            if ( (i - j + 1) < 0 )  break;
            if ( evenPal) {
                even_right ++;
                if ( s[even_left] == s[even_right]) {
                    palindromes[even_left].push_back(even_right);
                    even_left --;
                }
            } else evenPal = false;
            if ( (i - j ) < 0) break;
            if ( oddPal ) {
                odd_left --;
                odd_right ++;
                if ( s[odd_left] == s[odd_right]) {
                    palindromes[odd_left].push_back(odd_right);
                } else oddPal = false;
            }
        }
    }

    /*
    stack<int> pathStack, locStack;
    vector<string> path;
    pathStack.push(0);
    locStack.push(0);
    while ( !pathStack.empty()) {
        int curLeft = pathStack.top();
        int curRIndex = locStack.top();
        int curEnd = palindromes[curLeft][curRIndex];
        int nextLeft = curEnd + 1;
        path.push_back(s.substr(curLeft, curEnd-curLeft+1));
        int nextRIndex = 0;
        if (nextLeft == (signed)s.size()) {
            res.push_back(path);
            bool flag = false;
            while ( !pathStack.empty()) {
                curLeft = pathStack.top();
                curRIndex = locStack.top();
                if ( (curRIndex + 1) < (signed)palindromes[curLeft].size()) {
                    nextLeft = curLeft;
                    nextRIndex = curRIndex + 1;
                    flag = true;
                }
                pathStack.pop();
                locStack.pop();
                path.pop_back();
                if (flag)   break;
            }
            if (nextLeft == (signed)s.size())   break;
        }
        pathStack.push(nextLeft);
        locStack.push(nextRIndex);
    }
    */
    vector<string> path;
    recognizeNext(res, path, s, palindromes, 0);

    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    //string str("aab");
    //string str("cdd");
    string str("aabadddf");
    vector<vector<string> > res = s.partitionLessSpace(str);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << "   " ;
        }
        cout << endl;
    }
    return 1;
}
