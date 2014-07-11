#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort(vector<int> &num, int start, int end);
        vector<int> getPermutationInBinaryWay(vector<int> num, int k);
        void identifySubSequence( vector<int> num, int n, int k, vector<int> &flag, vector<int> &res);
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

void Solution::identifySubSequence( vector<int> num, int n, int k, 
        vector<int> &flag, vector<int> &res) {
    int subscript = -1;
    int factorial = 1, count = -1;
    for ( int i = 2; i <= (n-1); i ++) factorial *= i;
    for ( int i = 0; i < n; i ++ ) {
        subscript = k / factorial;
        k = k % factorial;
        if ( k == 0) {
            subscript -= 1;
            k = factorial;
        }
        factorial /= n - i - 1>=1?(n - i - 1):1;
        count = -1;
        int j = 0;
        for (; j < num.size(); j ++) {
            if (flag[j] == 0) {
                count ++;
            }
            if ( count == subscript) {
                flag[j] = 1;
                break;
            }
        }
        res.push_back(num[j]);
    }
}

// k accumulates from 1 ---- the least value of k is 1
vector<int> Solution::getPermutationInBinaryWay(vector<int> num, int k) {
    int m = 0;
    int current_factorial = 1, n = num.size();
    for ( int i = 1; i <= n; i ++ ) {
        current_factorial *= i;
        if ( k < current_factorial ) {
            m = i - 1;
            current_factorial /= i;
            break;
        } else if ( k == current_factorial) {
            m = i;
            break;
        }
    }
#ifdef DEBUG
    cout << "The partition of left and right is (The count of right part nums)  " << m << endl;
    cout << "The current factorial is  " << current_factorial << endl;
#endif 
    vector<int> res;
    if (m == 0) return  res;
    //first part & second part, the following command is wrong!!!!!!!!!
    int first_k = k / current_factorial , second_k = k % current_factorial ;
    int first_n = n - m, second_n = m;
    // choose the integers belong to the first part
    vector<int> flags( n, 0);
    identifySubSequence(num, first_n, first_k, flags, res);
    identifySubSequence(num, second_n, second_k, flags, res);
    return res;
}

string Solution::getPermutation(int n, int k) {
    vector<int> num;
    for ( int i = 0; i < n; i ++ ) num.push_back(i+1);
    vector<int> flags(n, 0), res;
    identifySubSequence(num, n, k, flags, res);
    string str("");
    for ( int i = 0; i < n; i ++) {
        str += (char)('0' + res[i]);
    }
    return str;
    /*
    vector<int> num;
    for ( int i = 0; i < n; i ++ ) num.push_back(i+1);
    vector<int> res = getPermutationInBinaryWay(num, k);
    string str("");
    for ( int i = 0; i < n; i ++) {
        str += (char)('0' + res[i]);
    }
    return str;
    */
    /*
    vector<int> data_v;
    for ( int i = 0; i < n ; i ++) data_v.push_back(i+1);
    // ATTENTION: this should run k -1 times, 
    // because the sorted list shoud be the first one, not the zeroth one
    for ( int i = 0; i < k-1; i ++ ) {
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
    */
}

int main(int argc, char *argv[]) {
    Solution s;
    
    cout << 8 << "   " << 8590 << endl;
    string res = s.getPermutation(8, 8590);
    //cout << 4 << "   " << 6 << endl;
    //string res = s.getPermutation(4, 6);
    for ( int i = 0; i < res.size(); i ++ ) {
        cout << res[i] << "   " ;
    }
    cout << endl;
	return 1;
}
