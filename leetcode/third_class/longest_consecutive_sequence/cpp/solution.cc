#include <iostream>
#include <vector>
#include <map>
#define DEBUG
using namespace std;

class Solution {
private:
    void quicksort(vector<int> &num, int left, int right);
public:
    int longestConsecutiveSort( vector<int> &num);
    int longestConsecutive( vector<int> &num);
};
void Solution::quicksort(vector<int> &num, int left, int right) {
    if(left >= right)   return;
    int pivot = num[right];
    int i = left -1, j = left;
    while ( j < right) {
        if (num[j] <=pivot) {
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

int Solution::longestConsecutiveSort( vector<int> &num) {
    if ( num.empty())   return 0;
    quicksort(num, 0, num.size() - 1);
    int res = 0, tmp = 1;
    int former = num[0];
    for ( int i = 1; i < (signed)num.size(); i ++) {
        if (( num[i] - former) == 1) tmp ++;
        else if ( num[i] == former) {
            former = num[i];
            continue;
        } else {
            if (tmp > res) {
                res = tmp;
            }
            tmp = 1;
        }
        former = num[i];
    }
    if (tmp > res)  res = tmp;
    return res;
}
struct ConSeq {
    int start;
    int end;
    ConSeq():start(0), end(0){}
    ConSeq(int start, int end):start(start), end(end){}
};


int main(int argc, char *argv[]) {
    int arr[] = {1, 22, 2, 32, 4, 35, 6, 31, 34, 5, 3};
    vector<int> num(arr, arr+sizeof(arr)/sizeof(int));
    Solution s;
    cout << s.longestConsecutiveSort(num) << endl;
	return 1;
}

