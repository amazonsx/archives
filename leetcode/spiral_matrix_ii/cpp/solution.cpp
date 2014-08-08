#include <iostream>
#include <vector>
#include <math.h>
#define DEBUG
using namespace std;

class Solution {
private:
    void spiralTraversal(vector<vector<int> > &matrix, 
            int left, int right, int top, int bottom, int start);
public:
    vector< vector<int> > generateMatrix(int n);
};

void Solution::spiralTraversal(vector<vector<int> > &matrix, 
        int left, int right, int top, int bottom, int start) {
    if (left > right)   return;
    if (top > bottom)   return;
    // vertical cursor, horizontal cursor
    int v_cursor = top, h_cursor = left;
    while (h_cursor <= right) {
        matrix[v_cursor][h_cursor] = start ++;
        h_cursor ++;
    }
    if (top == bottom)  return;
    v_cursor ++;
    h_cursor --;

    while (v_cursor <= bottom) {
        matrix[v_cursor][h_cursor] = start ++;
        v_cursor ++;
    }
    if (left == right)  return;
    h_cursor --;
    v_cursor --;

    while (h_cursor >= left) {
        matrix[v_cursor][h_cursor] = start ++;
        h_cursor --;
    }
    v_cursor --;
    h_cursor ++;

    while (v_cursor > top) {
        matrix[v_cursor][h_cursor] = start ++;
        v_cursor --;
    }
    spiralTraversal(matrix, left + 1, right - 1, top + 1, bottom - 1, start);
}

vector<vector<int> > Solution::generateMatrix(int n) {
    vector<vector<int>> res;
    if (n == 0)  return res;
    for (int i = 0; i < n; i ++) {
        vector<int> subMatrix(n, 0);
        res.push_back(subMatrix);
    }
    spiralTraversal(res, 0, n - 1, 0, n - 1, 1);
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    int num = 0;
    vector<vector<int> > res = s.generateMatrix(num);
    for (int i = 0; i < num; i ++) {
        for (int j = 0; j < num; j ++) {
            cout << res[i][j] << "   ";
        }
        cout << endl;
    }
	return 1;
}
