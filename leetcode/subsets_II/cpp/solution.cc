#include <iostream>
#include <unordered_map>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort(vector<int> &S, int left, int right);
    public:
        vector<vector<int> > subsetsWithDup(vector<int> &S);
};

void Solution::quicksort( vector<int> &S, int left, int right) {
    if (left >= right)  return;
    int i = left - 1, j = left;
    int pivot = S[right];
    while ( j < right) {
        if ( S[j] <= pivot) {
            i ++;
            int tmp = S[i];
            S[i] = S[j];
            S[j] = tmp;
        }
        j ++;
    }
    S[right] = S[++i];
    S[i] = pivot;
    quicksort(S, left, i - 1);
    quicksort(S, i + 1, right);
}

vector<vector<int> > Solution::subsetsWithDup(vector<int> &S) {     
    vector<vector<int> > res(1, vector<int>());
    quicksort(S, 0, S.size()-1);
    vector<vector<vector<vector<int> > > > subsets(S.size(), 
            vector<vector<vector<int> > >(S.size()+1, vector<vector<int> >()));
    for ( int i = 0; i < (signed)S.size(); i ++) {
        subsets[i][1].push_back(vector<int>(1, S[i]));
        if ( i > 0 ) {
            if ( S[i] == S[i-1])    continue;
        }
        res.push_back(subsets[i][1].back());
    }
    for ( int i = 2; i <= (signed)S.size(); i ++) {
        for ( int j = 0; j < (signed)S.size(); j ++) {
            for ( int k = j+1; k < (signed)S.size(); k ++) {
                if ( (k > j+1) && (S[k] == S[k-1]))    continue;
                for ( int m = 0; m < (signed)subsets[k][i-1].size(); m ++) {
                    subsets[j][i].push_back(vector<int>(1, S[j]));
                    subsets[j][i].back().insert(subsets[j][i].back().end(), 
                            subsets[k][i-1][m].begin(), subsets[k][i-1][m].end());
                    if ( j > 0) {
                        if ( S[j] == S[j-1])    continue;
                    }
                    res.push_back(subsets[j][i].back());
                }
            }
        }
    }
    return res;
}


int main(int argc, char *argv[]) {
    int arr[] = {2, 1, 2, 1};
    vector<int> S(arr, arr + sizeof(arr)/sizeof(int));
    Solution s;
    vector<vector<int> > res = s.subsetsWithDup(S);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 1;
}
