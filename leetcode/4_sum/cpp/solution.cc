#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sys/time.h>
#define DEBUG
using namespace std;

struct Sum {
    bool flag;
    vector< vector<int> > members;
    Sum():flag(false){}
};

class Solution {
    private:
        void quicksort(vector<int> &num, int left, int right);
        bool sumMatch( vector<int> &num, int count, int target, int index,
                map<int, map<int, map<int, Sum> > > &sumStat);
        void sumMatchFaster( vector<int> &num, int count, int target, int index,
                map<int, map<int, map<int, vector< vector<int> > > > > &sumStat,
                map<int, map<int, set<int> > > &keySet);
    public:
        vector<vector<int> > fourSum(vector<int> &num, int target);
};
void Solution::sumMatchFaster( vector<int> &num, int count, int target, int index, 
        map<int, map<int, map<int, vector<vector<int>>> > > &sumStat, map<int, map<int, set<int>>> &keySet) {
    if (keySet.find(count) != keySet.end()) {
        if (keySet[count].find(target) != keySet[count].end()) {
            if (keySet[count][target].find(index) != keySet[count][target].end()){
                return;
            }
        }
    }
    if (count == 2) {
        int begin = index, end = num.size() - 1;
        while ( begin < end) {
            int sum = num[begin] + num[end];
            if ( sum == target) {
                bool flag = true;
                if (keySet[count][target].find(begin) != keySet[count][target].end())
                    flag = false;
                if (flag) {
                    vector<int> sumGroup;
                    sumGroup.push_back(num[begin]);
                    sumGroup.push_back(num[end]);
                    sumStat[count][target][begin].push_back(sumGroup);
                    keySet[count][target].insert(begin);
                }
                begin ++;
                while (num[begin] == num[begin - 1]) {
                    begin ++;
                }
                end --;
                while (num[end] == num[end + 1]) {
                    end --;
                }
            } else if ( sum > target) {
                end --;
                while (num[end] == num[end + 1]) {
                    end --;
                }
            } else {
                begin ++;
                while (num[begin] == num[begin - 1]) {
                    begin ++;
                }
            }
        }
        return;
    }
    int former = num[index];
    vector< vector<int> > *current = NULL;
    vector<int> *subsMems = NULL;
    for ( int i = index; i <= (signed)num.size()-count; i ++) {
        if ( (num[i] == former) && ( i != index))   continue;
        sumMatchFaster( num, count-1, target-num[i], i+1, sumStat, keySet);
        if ( !keySet[count-1][target-num[i]].empty()) {
            current = &(sumStat[count][target][i]);
            map<int, vector<vector<int> > > &subSumMap = sumStat[count-1][target-num[i]];
            map<int, vector<vector<int> > >::iterator iter = subSumMap.begin();
            vector<int> tmp;
            tmp.push_back(num[i]);
            int formerNext = iter->first;
            for ( ; iter != subSumMap.end(); iter ++) {
                if (iter->first <= i)    continue;
                if ((num[iter->first] == num[formerNext]) && (iter != subSumMap.begin())) {
                    continue;
                }
                for ( int j = 0; j < (signed)iter->second.size(); j ++) {
                    subsMems = &(iter->second[j]);
                    current->push_back(tmp);
                    current->back().insert(current->back().end(), subsMems->begin(), subsMems->end());
                }
                formerNext = iter->first;
            }
            if (current->size() > 0) {
                keySet[count][target].insert(i);
            }
        }
        former = num[i];
    }
}

bool Solution::sumMatch( vector<int> &num, int count, int target, int index, 
        map<int, map<int, map<int, Sum> > > &sumStat) {
    if (sumStat[count].find(target) != sumStat[count].end()) {
        if (sumStat[count][target].find(index) != sumStat[count][target].end()) {
            return sumStat[count][target][index].flag;
        }
    }
    if ( count == 1) {
        if (target == num[index]) {   
            vector<int> tmp;
            tmp.push_back(target);
            sumStat[1][target][index].flag = true;
            sumStat[1][target][index].members.push_back(tmp);
            return true;
        } else {
            sumStat[1][target][index].flag = false;
            return false;
        }
    }
    int former = num[index];
    bool ret_flag = false;
    vector<int> indexV;
    for ( int i = index + 1; i < (signed) num.size(); i ++) {
        if ((num[i] == former) && (i > (index+1)))   continue;
        if ( (i+count-1) > (signed)num.size())  break;
        bool flag = sumMatch(num, count-1, target-num[index], i, sumStat);
        if (flag) {
            ret_flag = true;
            indexV.push_back(i);
        }
        former = num[i];
    }
    if (ret_flag) {
        vector< vector<int> > *subsMems = NULL, *current = NULL;
        sumStat[count][target][index].flag = true;
        current = &(sumStat[count][target][index].members);

        for ( int i = 0; i < (signed) indexV.size(); i ++) {
            subsMems = &( sumStat[count-1][target-num[index]][indexV[i]].members);
            for ( int j = 0; j < (signed) subsMems->size(); j ++) {
                vector<int> &tmp = (*subsMems)[j];
                current->push_back(tmp);
                current->back().insert(current->back().begin(), num[index]);
            }
        }
    } else {
        sumStat[count][target][index].flag = false;
    }
    return ret_flag;
}

void Solution::quicksort(vector<int> &num, int left, int right) {
    if (left >= right)  return;
    int i = left -1, j = left;
    int pivot = num[right];
    while (j < right) {
        if ( num[j] <= pivot) {
            i ++;
            int tmp = num[i];
            num[i] = num[j];
            num[j] = tmp;
        }
        j ++;
    }
    num[right] = num[++i];
    num[i] = pivot;
    quicksort(num, left, i - 1);
    quicksort(num, i + 1, right);
}

vector<vector<int> > Solution::fourSum(vector<int> &num, int target) {
    /*
       quicksort(num, 0, num.size() - 1);
       vector<vector<int> > res;
       map<int, map<int, map<int, Sum> > > sumStat;
       for ( int i = 0; i < (signed)num.size(); i ++) {
       if ( (i+4) > (signed)num.size())    break;
       sumMatch(num, 4, target, i, sumStat);
       }
       for ( map<int, Sum>::iterator iter = sumStat[4][target].begin();
       iter != sumStat[4][target].end(); iter ++) {
       if (iter->second.flag) {
       res.insert(res.end(), iter->second.members.begin(), iter->second.members.end());
       }
       }
       */
    vector<vector<int> > res;
    if (num.size() < 4) return res;
    quicksort(num, 0, num.size() - 1);
    map<int, map<int, map<int, vector<vector<int> > > > > sumStat;
    map<int, map<int, set<int> > > keySet;
    sumMatchFaster(num, 4, target, 0, sumStat, keySet);
    for ( map<int, vector<vector<int> > >::iterator iter = sumStat[4][target].begin();
            iter != sumStat[4][target].end(); iter ++) {
        res.insert(res.end(), iter->second.begin(), iter->second.end());
    }
    return res;
}

int main(int argc, char *argv[]) {
    //int arr[] = {1, 0, -1, 0, -2, 2};
    //int arr[] = {-493,-482,-482,-456,-427,-405,-392,-385,-351,-269,-259,-251,-235,-235,-202,-201,-194,-189,-187,-186,-180,-177,-175,-156,-150,-147,-140,-122,-112,-112,-105,-98,-49,-38,-35,-34,-18,20,52,53,57,76,124,126,128,132,142,147,157,180,207,227,274,296,311,334,336,337,339,349,354,363,372,378,383,413,431,471,474,481,492};
    //int arr[] = {-500,-495,-489,-472,-466,-449,-439,-435,-435,-413,-406,-381,-369,-353,-335,-311,-306,-260,-258,-231,-205,-189,-180,-165,-165,-164,-146,-141,-126,-121,-116,-100,-83,-23,-17,18,53,65,91,124,139,140,164,168,200,202,211,216,221,224,249,251,280,282,300,314,323,348,355,373,401,416,428,443,443,445,462,491,497};
    int arr[] = {-3,-2,-1,0,0,1,2,3};
    vector<int> num(arr, arr+sizeof(arr)/sizeof(int));
    Solution s;
    timeval first, second;
    gettimeofday(&first, NULL);
    vector<vector<int> > res = s.fourSum( num, 0); //-1864); //6189);
    gettimeofday(&second, NULL);
    cout << "Time cost is ---- " << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << "  ";
        }
        cout << endl;
    }
    return 1;
}
