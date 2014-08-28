#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
	public:
        int maximalRectangle( vector<vector<char> > &matrix);
};

int Solution::maximalRectangle( vector<vector<char> > &matrix) {
    if ( matrix.empty() ) return 0;
    int area = 0;
    int height = (signed)matrix.size(), width = (signed)matrix[0].size();
    vector<vector<vector<int> > > rows(height, vector<vector<int> >());
    for ( int i = 0; i < height; i ++) {
        int j = 0;
        while ( j < width ) {
            if (matrix[i][j] == '1') {
                rows[i].push_back(vector<int>(1, j));
                while ( (j < width) && (matrix[i][j] == '1')){
                    j ++;
                }
                rows[i].back().push_back(--j);
            }
            j ++;
        }
    }
    vector<vector<vector<int> > > columns(width, vector<vector<int> >());
    for ( int i = 0; i < width; i ++) {
        int j = 0;
        while ( j < height ) {
            if (matrix[j][i] == '1') {
                columns[i].push_back(vector<int>(1, j));
                while ( (j < height) && (matrix[j][i] == '1')){
                    j ++;
                }
                columns[i].back().push_back(--j);
            }
            j ++;
        }
    }
    vector<vector<int> > *row = NULL, *column = NULL;
    for ( int i = 0; i < height; i ++) {
        for ( int j = 0; j < width; j ++) {
            if (matrix[i][j] == '0')    continue;
            row = &rows[i];
            int left = j, right = j;
            for ( int k = 0; k < (signed)row->size(); k ++) {
                if ( (*row)[k][0] > j) break;
                if ( (*row)[k][0] <= j && (*row)[k][1] >= j) {
                    right = (*row)[k][1];
                    break;
                }
            }
            int minHeight = height; 
            for ( int k = left; k <= right; k ++) {
                column = &columns[k];
                int tmpHeight = 1;
                for ( int m = 0; m < (signed)column->size(); m ++) {
                    if ( (*column)[m][0] > i )  break;
                    if ( ((*column)[m][0] <= i) && ( (*column)[m][1] >= i) ) {
                        tmpHeight = (*column)[m][1] - i + 1;
                        break;
                    }
                }
                if (minHeight > tmpHeight) minHeight = tmpHeight;
                int tmparea = ( k - j + 1)*minHeight; 
                if (tmparea > area) area = tmparea;
                if (tmpHeight == 1) {
                    tmparea = right - left + 1;
                    if ( tmparea > area)    area = tmparea;
                    break;
                }
            }
        }
    }
    return area;
}

int main(int argc, char *argv[]) {
    vector<vector<char> > matrix(1, vector<char>(1, '0'));
    //matrix.back().push_back('1');
    Solution s;
    cout << s.maximalRectangle( matrix) << endl;
	return 1;
}
