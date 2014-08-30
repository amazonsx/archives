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

    for ( int sum = candidates[0]+1; sum <= target; sum ++) {
        cout << " sum : " << sum << endl;
        for ( int i = 0; i < (signed)candidates.size(); i ++) {
            if ( candidates[i] > sum)   break;
            int diff = sum;
            for ( int j = 1; j <= sum/candidates[i]; j ++) {
                diff -= candidates[i];
                for ( int k = i; k < (signed)candidates.size(); k ++) {
                    vector<vector<int> > &postfix = sumMap[k][diff];
                    if ( postfix.empty() && (k == i) && (diff == 0) ) {
                        sumMap[i][sum].push_back(vector<int>());
                        for ( int n = 0; n < j; n ++) {
                            sumMap[i][sum].back().push_back(candidates[i]);
                        }
                    }
                    for ( int m = 0; m < (signed)postfix.size(); m ++) {
                        if ( (k == i) && (diff != 0) ) { 
                            if ( postfix[m][0] == postfix[m].back())    continue;
                        }
                        sumMap[i][sum].push_back(vector<int>());
                        for ( int n = 0; n < j; n ++) {
                            sumMap[i][sum].back().push_back(candidates[i]);
                        }
                        sumMap[i][sum].back().insert(sumMap[i][sum].back().end(),
                                postfix[m].begin(), postfix[m].end());
                    }
                }
            }
        }
    }
    vector<vector<int> > res;
    for (int i = 0; i < (signed)candidates.size(); i ++) {
        res.insert(res.end(), sumMap[i][target+1].begin(), sumMap[i][target+1].end());
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
