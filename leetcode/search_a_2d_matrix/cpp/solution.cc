#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    bool binarySearch( vector<int> &obj, int left, int right, int target);
public:
    bool searchMatrix( vector<vector<int> > &matrix, int target);
};

bool Solution::binarySearch( vector<int> &obj, int left, int right, int target) {
    if ( left > right)  return false;
    int mid = ( left + right ) >> 1;
    if ( obj[mid] == target)    return true;
    if ( left == right) return false;
    if ( obj[mid] > target )    return binarySearch( obj, left, mid-1, target);
    return binarySearch( obj, mid + 1, right, target);
}

bool Solution::searchMatrix( vector<vector<int> > &matrix, int target) {
    int i = 0;
    for ( ; i < (signed)matrix.size(); i ++) {
        if ( matrix[i][0] > target)    break;
    }
    if ( i == 0)    return false;
    if ( i == (signed)matrix.size()) {
        if ( matrix[i-1].back() < target) return false;
    }

    return binarySearch( matrix[i-1], 0, matrix[i-1].size() - 1, target);    
}

int main(int argc, char *argv[]) {
    vector<vector<int> > matrix(1, vector<int>());
    matrix.back().push_back(1);
    matrix.back().push_back(3);
    Solution s;
    cout << s.searchMatrix(matrix, 1) << endl;
	return 1;
}

