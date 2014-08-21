#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort( vector<int> &num, int begin, int end);
        bool nextPermutation(vector<int> &num, int &left);
    public:
        vector<vector<int> > permuteUnique( vector<int> &num);
};

void Solution::quicksort( vector<int> &num, int begin, int end) {
    if (begin >= end)   return;
    int i = begin-1, j = begin;
    int pivot = num[end];
    while ( j < end) {
        if (num[j] <= pivot) {
            i ++;
            int tmp = num[i];
            num[i] = num[j];
            num[j] = tmp;
        }
        j ++;
    }
    num[end] = num[++i];
    num[i] = pivot;
    quicksort(num, begin, i -1 );
    quicksort(num, i + 1, end);
}


bool Solution::nextPermutation(vector<int> &num, int &left){
    int i = 0;
    for ( i = num.size() - 1; i > 0; i --) {
        if (num[i-1] < num[i]) {
            break;
        }
    }
    int pos = num.size() - 1;
    if ( i <= left) {
        if ( i == 0)    return false;
        pos = num.size() - 1;
        //while ( num[pos] <= num[i-1] ) pos --;
        for (; pos > i-1; pos --) {
            if ( num[pos] > num[i-1])   break;
        }
        left = i - 1;
    } else {
        while (num[pos] <= num[i-1]) pos --;
    }
    int tmp = num[i-1];
    num[i-1] = num[pos];
    num[pos] = tmp;
    quicksort(num, i, num.size() - 1);
    return true;
}

vector<vector<int> > Solution::permuteUnique( vector<int> &num) {
    vector<vector<int> > res;
    if (num.size() < 1 ) return res;
    quicksort(num, 0, num.size()-1);
    res.insert(res.end(), num);
    int left = num.size() - 1;
    while (true) {
        bool flag = nextPermutation(num, left);
        if (flag) {
            res.insert( res.end(), num);
        } else {
            break;
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    //int arr[] = { 1, 3, 2, 1, 5, 2 };
    int arr[] = { 1, 3, 2, 1, 2, 5 };
    vector<int> num(arr, arr+sizeof(arr)/sizeof(int));
    Solution s;
    vector< vector<int> > res = s.permuteUnique(num);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed) res[i].size(); j ++) {
            cout << res[i][j] << "    ";
        }
        cout << endl;
    }
    cout << res.size() << endl;
    return 1;
}
