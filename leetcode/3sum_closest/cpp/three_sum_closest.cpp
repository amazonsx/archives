#include <iostream>
#include <vector>
//#define DEBUG
#define SORTDEBUG
using namespace std;

class Solution {
    private:
        void quicksort( vector<int> &num, int start, int end);
        int binarySearch ( vector<int> &num, int front, int back, int obj);
	public:
        int threeSumClosest(vector<int> &num, int target);
};

int Solution::binarySearch ( vector<int> &num, int front, int back, int obj) {
    int mid = -1;
    int pos = -1, flag = 0;
    while ( front <= back ) {
        mid = (front + back) >> 1;
        if ( num[mid] > obj ) {
            back = mid - 1;
            flag = 1;
        } else if (num[mid] < obj) {
            front = mid + 1;
            flag = -1;
        } else {
            pos = mid;
            return pos;
        }
    }
    pos = mid;
    int step = 1, diff = flag*(num[mid]-obj);
    int min_diff = diff, left_flag = 1, right_flag = 1; //if its still has a decrease tendency on the left or right
    while ((((mid+step) <= back ) || ((mid-step) >= front) )) {
        if ( ((mid+step) <= back) && right_flag) {
            diff = num[mid+step] - obj;
            if (diff < 0) diff = -1*diff;
            if (diff <= min_diff) {
                min_diff = diff;
                pos = mid + step;
            } else {
                right_flag = 0;
            }
        }
        if ( ((mid-step) >= front) && left_flag) {
            diff = num[mid-step] - obj;
            if (diff < 0) diff = -1*diff;
            if (diff <= min_diff) {
                min_diff = diff;
                pos = mid - step;
            } else {
                left_flag = 0;
            }
        }
        if (right_flag || left_flag) break;
        step ++;
    }

    return pos;
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

int Solution::threeSumClosest(vector<int> &num, int target) {
    int len = num.size();
    int res = -1;
    quicksort(num, 0, len - 1);
    
    int obj = 0;
    int min_diff = -1;
    int front = -1, back = -1;
    for ( int i = 0; i <= len - 3; i ++ ) {
        // why do this line and line 79, think about it ?
        if ( (i > 0) && (num[i-1] == num[i]) ) continue;
        for ( int j = len - 1; j > i; j -- ) {
            if ( (j < (len - 1)) && (num[j+1] == num[j]) ) continue;
            obj = target - num[j] - num[i];
            if ( i >= 1 ) front = i - 1;
            else front = i + 1;
            if ( j <= len - 2) back = j + 1;
            else back = j - 1;
            int pos = binarySearch(num, front, back, obj);
            if ( (pos == i) || (pos == j)) continue;
            int tmp_diff =  obj - num[pos];
            if (tmp_diff < 0) tmp_diff *= -1;
            if ((min_diff == -1) || (tmp_diff < min_diff)) {
                min_diff = tmp_diff;
                res = num[i] + num[j] + num[pos];
                cout << "front back " << front << " " << back << " " << endl;
                cout << "Tmp Result " << i << " " << j << " " << pos << endl;
            }
        }
    }

    return res;
}

int main(int argc, char *argv[]) {
    cout << "target    res" << endl;
    Solution s;
    int arr[] = {-1,2,1,-4};
    vector<int> num(arr, arr + sizeof(arr)/sizeof(int));
    int target = 1;
    int res = s.threeSumClosest(num, target);
    cout << target << "        "  << res << endl;

    int arr1[] = {0, 0, 0, 0};
    vector<int> num1(arr1, arr1 + sizeof(arr1)/sizeof(int));
    target = 1;
    res = s.threeSumClosest(num1, target);
    cout << target << "        "  << res << endl;

    int arr2[] = {0, 0, 0};
    vector<int> num2(arr2, arr2 + sizeof(arr2)/sizeof(int));
    target = 1;
    res = s.threeSumClosest(num2, target);
    cout << target << "        "  << res << endl;

    int arr3[] = {3,0,-2,-1,1,2};
    vector<int> num3(arr3, arr3 + sizeof(arr3)/sizeof(int));
    target = 1;
    res = s.threeSumClosest(num3, target);
    cout << target << "        "  << res << endl;
	return 1;
}
