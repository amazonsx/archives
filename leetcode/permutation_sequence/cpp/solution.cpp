#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort(vector<int> &num, int start, int end);
	public:
        string getPermutation(int n, int k);
};
void Solution::quicksort(vector<int> &num, int start, int end) {
    if ( start >= end ) return;
    int i = start -1, j = start;
    int pivot = num[end];
    while ( j <= end -1) {
        if (num[j] <= pivot) {
            i ++;
            if ( i != j) {
                int tmp = num[i];
                num[i] = num[j];
                num[j] = tmp;
            }
        }
        j++;
    }
    int tmp = num[i+1];
    num[i+1] = pivot;
    num[end] = tmp;
    quicksort(num, start, i);
    quicksort(num, i + 2, end);
}
string Solution::getPermutation(int n, int k) {
    /*
    int m = 0;
    int current_factorial = 1;
    for ( int i = 1; i <= n; i ++ ) {
        current_factorial *= i;
        if ( k < current_factorial ) {
            m = i - 1;
            break;
        } else if ( k == current_factorial) {
            m = i;
            break;
        }
    }
    */
    vector<int> data_v;
    for ( int i = 0; i < n ; i ++) data_v.push_back(i+1);
    for ( int i = 0; i < k; i ++ ) {
        int start = n-1; 
        for ( int j = n-1; j >= 1; j --) {
            if (data_v[j] > data_v[j-1]) {
                int tmp = data_v[j-1];
                int min_index = n-1;
                int m = j;
                for (; m < n - 1; m ++) {
                    if ((data_v[m] > tmp) && (data_v[m+1] < tmp)) 
                        break;
                }
                /*
                if ( m == n-1) {
                    if ((data_v[n-2] > tmp) && (data_v[n-1] < tmp)) min_index = n - 2;
                    else min_index = n - 1;
                } else min_index = m;
                */
                min_index = m;

                data_v[j-1] = data_v[min_index];
                data_v[min_index] = tmp;
                start = j;
                break;
            }
        }
        quicksort(data_v, start, n-1);
    }
    string res("");
    for ( int i = 0; i < n; i ++) {
        res += (char)('0' + data_v[i]);
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    
    cout << 8 << "   " << 8590 << endl;
    string res = s.getPermutation(8, 8590);
    for ( int i = 0; i < res.size(); i ++ ) {
        cout << res[i] << "   " ;
    }
    cout << endl;
	return 1;
}
