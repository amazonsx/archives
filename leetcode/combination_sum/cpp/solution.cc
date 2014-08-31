#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort( vector<int> &v, int left, int right);
    public:
        vector<vector<int> > combinationSum( vector<int> &candidates, int target);
};

void Solution::quicksort( vector<int> &v, int left, int right) {
    if (left >= right)  return;
    int i = left - 1, j = left;
    int pivot = v[right];
    while ( j < right ) {
        if ( v[j] < pivot ) {
            int tmp =  v[j];
            v[j] = v[++i];
            v[i] = tmp;
        }
        j ++;
    }
    v[right] = v[++i];
    v[i] = pivot;
    quicksort(v, left, i - 1);
    quicksort(v, i + 1, right);
}

vector<vector<int> > Solution::combinationSum( vector<int> &candidates, int target){
    for ( vector<int>::iterator iter = candidates.begin();
            iter != candidates.end(); iter ++) {
        if ( *iter > target) {
            iter = candidates.erase(iter);
            if (iter == candidates.end())   break;
        } else if ( (iter > candidates.begin() ) && (*iter == *(iter-1) ) ) {
            iter = candidates.erase(iter);
            if (iter == candidates.end())   break;
        }
    }
    quicksort( candidates, 0, candidates.size()-1);
    vector<vector<vector<vector<int> > > >  sumMap( candidates.size(), 
            vector<vector<vector<int> > >(target+1, vector<vector<int> >()));
    for ( int sum = 0; sum <= target; sum ++) {
#ifdef DEBUG
        cout << " ---- sum : " << sum << endl;
#endif
        for ( int i = 0; i < (signed)candidates.size(); i ++ ) {
#ifdef DEBUG
            cout << "  ========== candidates " << candidates[i] << endl;
#endif
            if ( candidates[i] > sum ) {
                if ( sum == 0) {
                    sumMap[i][0].push_back(vector<int>());
                }
                continue;
            } else if ( candidates[i] == sum ) {
                sumMap[i][sum].push_back(vector<int>(1, sum ));
                continue;
            }
            int diff = sum - candidates[i];
            for ( int j = i; j < (signed)candidates.size(); j ++) {
#ifdef DEBUG
                cout << " candidates partner value and v size ^^^^^^^^^" << candidates[j] << "   " << sumMap[j][diff].size() << endl;
#endif
                for ( int k = 0; k < (signed)sumMap[j][diff].size(); k ++ ) {
                    vector<vector<int> > &sub = sumMap[j][diff];
                    sumMap[i][sum].push_back(vector<int>(1, candidates[i]));
                    sumMap[i][sum].back().insert(sumMap[i][sum].back().end(),
                            sub[k].begin(), sub[k].end() );
                }
            }
        }
    }
    vector<vector<int> > res;
    for ( int i = 0; i < (signed)candidates.size(); i ++) {
        for ( int j = 0; j < (signed)sumMap[i][target].size(); j ++) {
            res.push_back(sumMap[i][target][j]);
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    //int arr[] = {2, 3, 6, 7};
    //int arr[] = {2};
    //int arr[] = { 2, 3, 5};
    int arr[] = { 1, 2};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));
    Solution s;
    //int target = 7;
    //int target = 1;
    //int target = 8;
    int target = 4;
    vector<vector<int> > res = s.combinationSum( v, target);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 1;
}
