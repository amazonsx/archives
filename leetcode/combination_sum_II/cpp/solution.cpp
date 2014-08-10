#include <iostream>
#include <vector>
#include <map>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
private:
    void quicksort(vector<int> &num, int left, int right);
    bool matchSum(vector<int> &num, map<int, map<int, vector<vector<int> >>> &targetMap, 
            int start, int target);
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target);
};

void Solution::quicksort(vector<int> &num, int left, int right) {
    if (left >= right) return;
    int i = left-1, j = left;
    int pivot = num[right];
    while(j < right) {
        if ( num[j] <= pivot) {
            i ++;
            int tmp = num[j];
            num[j] = num[i];
            num[i] = tmp;
        }
        j ++;
    }
    int tmp = num[right];
    num[right] = num[++i];
    num[i] = tmp;
    quicksort(num, left, i-1);
    quicksort(num, i+1, right);
}

bool Solution::matchSum(vector<int> &num, map<int, map<int, vector<vector<int>>>> &targetMap, 
        int start, int target) {
    if (target < num[start]) return false;
    if (target == num[start]) {
        vector<vector<int> > tmp;
        vector<int> subTmp;
        subTmp.push_back(target);
        tmp.push_back(subTmp);
        targetMap[start][target] = tmp;
        return true;
    }

    if (targetMap.find(start) != targetMap.end()) {
        if (targetMap[start].find(target) != targetMap[start].end()) {
            if (targetMap[start][target].size() == 0) return false;
            else  return true; 
        }
    }
    int flag = false;
    for (int i = start + 1; i < (signed)num.size(); i ++) {
        if ( i > (start+1)) {
            if (num[i] == num[i-1]) continue;
        }
        bool nextFlag = matchSum(num, targetMap, i, target-num[start]);
        flag |= nextFlag;
        if(nextFlag) {
            vector<vector<int> > sub = targetMap[i][target-num[start]];
            for (int j = 0; j < (signed)sub.size(); j ++) {
                vector<int> element; 
                element.push_back(num[start]);
                element.insert(element.end(), sub[j].begin(), sub[j].end());
                targetMap[start][target].push_back(element);
            }
        }
    }
    if (!flag) {
        vector<vector<int> > tmp;
        targetMap[start][target] = tmp;
    }
    return flag;
}


vector<vector<int> > Solution::combinationSum2(vector<int> &num, int target) {
    for ( vector<int>::iterator iter = num.begin(); iter != num.end(); iter ++) {
        if (*iter > target) {
            iter = num.erase(iter);
            if (iter == num.end()) break;
        }
    }

    quicksort(num, 0, num.size() - 1);

    map<int, map<int, vector<vector<int> > > >  targetMap;
    vector<vector<int> > res;
    for ( int i = 0; i < (signed)num.size(); i ++) {
        bool flag = matchSum(num, targetMap, i, target);
        if ((flag) && (num[i] != num[i-1])) {
            res.insert(res.end(), targetMap[i][target].begin(), targetMap[i][target].end());
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    int arr[] = {10,1,2,7,6,1,5};
    //int arr[] = {2};
    //int arr[] = {2, 2, 2};
    vector<int> num(arr, arr+sizeof(arr)/sizeof(int));
    struct timeval first, second;
    Solution s;
    gettimeofday(&first, NULL);
    vector<vector<int> > res = s.combinationSum2(num, 8);
    //vector<vector<int> > res = s.combinationSum2(num, 1);
    //vector<vector<int> > res = s.combinationSum2(num, 4);
    gettimeofday(&second, NULL);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] <<  "   ";
        }
        cout << endl;
    }

    cout << "The total time cost is ---- "  
         << 1000000*(second.tv_sec - first.tv_sec) + (second.tv_usec - first.tv_usec) 
         << endl;

	return 1;
}


