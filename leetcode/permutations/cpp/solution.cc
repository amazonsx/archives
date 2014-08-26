#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    void nextPermutation(vector<int> &num, vector<vector<int> > &res);
    void quicksort(vector<int> &num, int left, int right);
public:
    vector<vector<int> > permute( vector<int> &num);
};

void Solution::quicksort(vector<int> &num, int left, int right) {
    if (left >= right)  return;
    int i = left - 1, j = left;
    int pivot = num[right];
    while ( j < right ) {
        if ( num[j] <= pivot) {
            i ++;
            int tmp = num[j];
            num[j] = num[i];
            num[i] = tmp;
        }
        j ++;
    }
    num[right] = num[++i];
    num[i] = pivot;
    quicksort( num, left, i-1 );
    quicksort( num, i+1, right );
}

void Solution::nextPermutation(vector<int> &num, vector<vector<int> > &res){
    int len = num.size();
    int i = len - 1;
    for ( ; i >= 1; i --) {
        if ( num[i] > num[i-1]) break;
    }
    if ( i == 0)    return;
    int j = len - 1;
    for ( ; j >= i; j --) {
        if (num[j] > num[i-1])  break;
    }
    int tmp = num[--i];
    num[i] = num[j];
    num[j] = tmp;
    quicksort( num, i + 1, len - 1);
    res.push_back(num);
    nextPermutation(num, res);
}

vector<vector<int> > Solution::permute( vector<int> &num) {
    vector<vector<int> > res;
    quicksort( num, 0, num.size()-1);
    res.push_back(num);
    nextPermutation(num, res);
    return res;
}

int main(int argc, char *argv[]) {
    int arr[] = { 1, 2, 3, 5, 2};
    vector<int> num(arr, arr + sizeof(arr)/sizeof(int));
    Solution s;
    vector<vector<int> > res = s.permute(num);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << "  ";
        }
        cout << endl;
    }
    cout << res.size() << endl;
	return 1;
}
