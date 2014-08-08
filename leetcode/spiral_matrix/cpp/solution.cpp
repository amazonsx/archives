#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
private:
    void spiralTraversal(vector< vector<int> > &matrix, 
            int top, int bottom, int left, int right, vector<int> &res);
public:
    vector<int> spiralOrder(vector< vector<int> > &matrix);
};

void Solution::spiralTraversal(vector< vector<int> > &matrix, 
        int top, int bottom, int left, int right, vector<int> &res) {
    if (top > bottom)   return;
    if (left > right)   return;
    // horizonal cursor, vertical cursor
    int h_cursor = left, v_cursor = top;
    
    while(h_cursor <= right)
        res.push_back(matrix[v_cursor][h_cursor++]);
    if (top == bottom)  return;
    h_cursor --;
    v_cursor ++;

    while(v_cursor <= bottom)
        res.push_back(matrix[v_cursor++][h_cursor]);
    if (left == right)  return;
    h_cursor --;
    v_cursor --;

    while(h_cursor >= left)
        res.push_back(matrix[v_cursor][h_cursor--]);
    h_cursor ++;
    v_cursor --;

    while(v_cursor > top)
        res.push_back(matrix[v_cursor--][h_cursor]);
    spiralTraversal(matrix, top+1, bottom -1, left + 1, right -1, res);
}

vector<int> Solution::spiralOrder(vector< vector<int> > &matrix) {
    vector<int> res;    
    if (matrix.empty()) return res;
    int top = 0, bottom = matrix.size() - 1;
    if (matrix[0].empty())  return res;
    int left = 0, right = matrix[0].size() - 1;
    spiralTraversal( matrix, top, bottom, left, right, res);
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    vector < vector<int> >  matrix;

    int height = rand()%10;
    int width = rand()%10;
    for ( int i = 0; i < height; i ++)  {
        vector<int> line;
        for ( int j = 0; j < width; j ++) {
            int num = rand()%20;
            line.push_back(num);
            cout << num << "  ";
        }
        cout << endl;
        matrix.push_back(line);
    }
    
    struct timeval first, second;
    gettimeofday(&first, NULL);
    vector<int> res = s.spiralOrder(matrix); 
    gettimeofday(&second, NULL);
    for (int i = 0; i < (signed)res.size(); i ++)
        cout << res[i] <<  "  " ; 

    cout << endl;
    cout << "The time cost is ---- "
        << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;

	return 1;
}
