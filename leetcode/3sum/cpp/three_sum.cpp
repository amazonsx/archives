#include <iostream>
#include <vector>
//#define DEBUG
#define SORTDEBUG
using namespace std;

class Solution {
    private:
        void quicksort( vector<int> &num, int start, int end);
        bool binarySearch ( vector<int> &num, int front, int back, int obj, int &pos);
	public:
        vector<vector<int> > threeSum(vector<int> &num);
};

bool Solution::binarySearch ( vector<int> &num, int front, int back, int obj, int &pos) {
    int mid = -1;
    while ( front <= back ) {
        mid = (front + back) >> 1;
#ifdef DEBUG
        cout << "mid is " << mid << endl;
        cout << "the mid value is " << num[mid] << endl;
#endif
        if ( num[mid] > obj ) {
            back = mid - 1;
        } else if (num[mid] < obj) {
            front = mid + 1;
        } else {
            pos = mid;
            return 1;
        }
    }
    return 0;
}

void Solution::quicksort(vector<int> &num, int start, int end) {
    if (start >= end) return;
    int pivot = num[end];
    int i = start - 1, j = start;
    for (j = start; j <= end-1; j ++) {
        if (num[j] <= pivot) {
            i ++;
            int tmp = num[j];
            num[j] = num[i];
            num[i] = tmp;
        }
    }
    int tmp = num[i+1]; 
    num[i+1] = pivot;
    num[end] = tmp;
    quicksort(num, start, i);
    quicksort(num, i + 2, end);
}

vector<vector<int> > Solution::threeSum(vector<int> &num) {
    int len = num.size();
    vector<vector<int> >  res;
    // why do this from line 57 to 65, think about it ? Acctually, this is unnecessory, it give a duplicate answer
    /*int z_count = 0;
    for ( int i = 0; i < len; i ++ ) {
        if (num[i] == 0) z_count ++;
    }
    // why not use >=, think about it ?
    if (z_count > 3) {
        vector<int> tmp(3, 0);
        res.push_back(tmp);
    } */
    quicksort(num, 0, len - 1);
#ifdef SORTDEBUG
    cout << "The sorted num vector " << endl;
    for ( int i = 0; i < len; i ++) {
        cout << num[i] << "  " ;
    }
    cout << endl;
#endif
    int pos = -1, obj = 0;
    for ( int i = 0; i <= len - 3; i ++ ) {
        // why do this line and line 79, think about it ?
        if ( (i > 0) && (num[i-1] == num[i]) ) continue;
        for ( int j = len - 1; j > i; j -- ) {
            if ( (j < (len - 1)) && (num[j+1] == num[j]) ) continue;
            obj = 0 - num[j] - num[i];
            if (obj < num[i]) continue; 
            if (obj > num[j]) continue; 
#ifdef DEBUG
            cout << "the obj value is " << obj << endl;
            cout << "front is " << i+1 << endl;
            cout << "end is " << j-1 << endl;
#endif
            if (binarySearch(num, i + 1, j - 1, obj, pos)) {
                vector<int> tmp;
                tmp.push_back(num[i]);
                tmp.push_back(obj);
                tmp.push_back(num[j]);
                res.push_back(tmp);
            }
        }
    }

    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    int arr[] = {-1,0,1,2,-1,-4};
    vector<int> num(arr, arr + sizeof(arr)/sizeof(int));
    vector<vector<int> > res = s.threeSum(num);
    cout << "res size:" << res.size() << endl;
    for ( int i = 0; i < res.size(); i ++ ) {
        for ( int j = 0; j < 3; j ++ ) {
            cout <<  res[i][j] << "  " ;
        }
        cout << endl;
    }

    int arr1[] = {0, 0, 0, 0};
    vector<int> num1(arr1, arr1 + sizeof(arr1)/sizeof(int));
    res = s.threeSum(num1);
    cout << "res size:" << res.size() << endl;
    for ( int i = 0; i < res.size(); i ++ ) {
        for ( int j = 0; j < 3; j ++ ) {
            cout <<  res[i][j] << "  " ;
        }
        cout << endl;
    }

    int arr2[] = {0, 0, 0};
    vector<int> num2(arr2, arr2 + sizeof(arr2)/sizeof(int));
    res = s.threeSum(num2);
    cout << "res size:" << res.size() << endl;
    for ( int i = 0; i < res.size(); i ++ ) {
        for ( int j = 0; j < 3; j ++ ) {
            cout <<  res[i][j] << "  " ;
        }
        cout << endl;
    }

    int arr3[] = {3,0,-2,-1,1,2};
    vector<int> num3(arr3, arr3 + sizeof(arr3)/sizeof(int));
    res = s.threeSum(num3);
    cout << "res size:" << res.size() << endl;
    for ( int i = 0; i < res.size(); i ++ ) {
        for ( int j = 0; j < 3; j ++ ) {
            cout <<  res[i][j] << "  " ;
        }
        cout << endl;
    }
	return 1;
}
