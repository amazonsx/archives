#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
private:
    void matrixEdgeTraversal(vector< vector<int> > &matrix, 
            int &top, int &bottom, int &left, int &right, vector<int> &res);
public:
    vector<int> spiralOrder(vector< vector<int> > &matrix);
};
void Solution::matrixEdgeTraversal(vector< vector<int> > &matrix, 
        int &top, int &bottom, int &left, int &right, vector<int> &res) {
    if ((left > right) || (top > bottom))   return;
    if ((left == right) && (top == bottom)) {
        res.push_back(matrix[top][left]);
        return;
    }
    int i = top, j = left;
    while (j <= right) 
        res.push_back(matrix[i][j++]);
    i ++; 
    j --;
    right --;
    if (top == bottom)   return;
    while (i <= bottom)
        res.push_back(matrix[i++][j]);
    j --;
    i --;
    bottom --;
    if (left == right)   return;
    while (j >= left)
        res.push_back(matrix[i][j--]);
    i --;
    j ++;
    left ++;
    if (top == bottom)  return;
    while (i > top)
        res.push_back(matrix[i--][j]);
    j ++;
    i ++;
    top ++;
    if (left == right) return;
    matrixEdgeTraversal(matrix, top, bottom, left, right, res);
}

vector<int> Solution::spiralOrder(vector< vector<int> > &matrix) {
    vector<int> res;    
    if (matrix.empty()) return res;
    int top = 0, bottom = matrix.size() - 1;
    if (matrix[0].empty())  return res;
    int left = 0, right = matrix[0].size() - 1;
    matrixEdgeTraversal( matrix, top, bottom, left, right ,res);
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
