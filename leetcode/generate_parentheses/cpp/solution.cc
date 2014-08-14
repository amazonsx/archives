#include <iostream>
#include <vector>
#include <string>
#define DEBUG
using namespace std;

class Solution {
private:
    void generate( vector<string> &res, int left, int right, string &current);
public:
    vector<string> generateParenthesis(int n);
};

void Solution::generate( vector<string> &res, int left, 
        int right, string &current) {
    if ( right == 0) {
        res.push_back(current);
        return;
    }
    if (left > 0) {
        string str = current + "(";
        generate(res, left - 1, right, str);
    }
    if (left < right) {
        string str = current + ")";
        generate(res, left, right - 1, str);
    }
}

vector<string> Solution::generateParenthesis(int n) {
    vector<string> res;
    if ( n == 0) return res;
    string init = "(";
    generate(res, n-1, n, init);
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    int n = 3;
    vector<string> res = s.generateParenthesis(n);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        cout << res[i] << endl;
    }
	return 1;
}
