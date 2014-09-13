#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#define DEBUG
using namespace std;

class Solution {
    private:
        int convert(string str);
        void subCode(vector<int> &res, string &str, int left, int n);
    public:
        vector<int> grayCode(int n);
        vector<int> grayCode2(int n);
};

vector<int> Solution::grayCode2(int n ) {
    vector<int> res;
    if (n ==0) {
        res.push_back(0);
        return res;
    }
    if ( n == 1) {
        res.push_back(1);
        res.push_back(1);
        return res;
    }
    vector<int> former = grayCode2(n-1);
    int msd = 0; // most significant digit
    for ( int i = 0; i < (signed)former.size(); i ++) {
        int current = former[i] << 1;
        res.push_back(current + msd);
        res.push_back(current + 1 - msd);
        msd = 1 - msd;
    }
    return res;
}

int Solution::convert(string str) {
    int res = 0;
    for (int i = 0; i < (signed)str.size(); i ++){
        int current = stoi(str.substr(i, 1));
        res = (res << 1) + current;
    }
    return res;
}

// left means the distance from the highest bit/least significant bit
void Solution::subCode(vector<int> &res, string &str, int left, int n) {
    if (left == (n-1)) {
        res.push_back(convert(str));
        if (str[left] == '1')   str[left] = '0';
        else    str[left] = '1';
        res.push_back(convert(str));
        return;
    }
    subCode(res, str, left + 1, n); 
    if (str[left] == '1')   str[left] = '0';
    else    str[left] = '1';
    subCode(res, str, left + 1, n);
}

vector<int> Solution::grayCode(int n) {
    vector<int> res;
    if (n == 0) {
        res.push_back(0);
        return res;
    }
    string str("");
    for ( int i = 0; i < n; i ++){
        str += '0';
    }
    subCode(res, str, 0, n);
    /*
    res.push_back(0);
    for ( int i = n-1; i >= 0; i -- ){
        int currnet = n - 1;
        int direction =  -1;
        for ( int j = 0; j < pow(2, n - i - 1) - 1; j ++) {
            if (str[current] == '1')    str[current] = '0';
            else    str[current] = '1';
            res.push_back(convert(str));
            if (current == (i+1))   direction = 1;
            else if ( current == (n - 1))   direction  = -1;
            current += direction;
        }
    }
    */
    return res;
}
int main(int argc, char *argv[]) {
    Solution s;
    vector<int> res = s.grayCode(4);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        cout << res[i] << endl;
    }
    cout << endl;
    return 1;
}
