#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
    private:
        void quicksort( vector<int> &num, int start, int end);
	public:
        void nextPermutation( vector<int> &num);
};
void Solution::quicksort( vector<int> &num, int start, int end) {
    if (start >= end) return;
    int pivot = num[end];
    int i = start -1, j = start;
    while(j <= end-1) {
        if ( num[j] < pivot) {
            i ++;
            if ( i != j) {
                int tmp = num[j];
                num[j] = num[i];
                num[i] = tmp;
            }
        }
        j++;
    }
    num[end] = num[i+1];
    num[i+1] = pivot;
    quicksort(num, start, i);
    quicksort(num, i + 2, end);
}

void Solution::nextPermutation( vector<int> &num) {
    //int rotate_count = 0;
    // the meaning of the init value of start and end, think about it!!!
    int start = num.size()-1, end = 0;
    for ( int i = num.size()-2; i >=0; i--) {
        if (num[i] < num[i+1]) {
            for ( int j = num.size()-1; j>=i; j --) {
                if( num[j] > num[i]) {
                    end = i;
                    start = j;
                    break;
                }
            }
            break;
        }
    }
    int tmp = num[end];
    num[end] = num[start];
    num[start] = tmp;
    quicksort( num, end+1, num.size() -1);
    /*
    unsigned int final_pos = start;
    unsigned int tmp_pos = start;
    int tmp = num[start];
    unsigned int dest = end;
    while ( dest != final_pos) {
        tmp = num[dest];
        num[dest] = num[start];
        tmp_pos = start;
        start = end;
        end = tmp_pos;
        for ( unsigned int i = start; i != end; i += flag) {
            if (num[i]*flag > tmp*flag){
                end = i;
            }
        }
        if (i == end) { 
            if (num[end-flag]*flag <= tmp*flag ) {
                num[final_pos] = tmp;
                return;
            }
            
        }
    }
    */
}

int main(int argc, char *argv[]) {
    //int arr[] = {1, 5, 2, 8, 9, 7};
    //int arr[] = {1, 2, 3};
    //int arr[] = {3, 1, 2};
    //int arr[] = {4,2,0,2,3,2,0};
    int arr[] = {100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(int));
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "    " ;
    }
    cout << endl;
    Solution s;
    s.nextPermutation(vec);
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec[i] << "    " ;
    }
    cout << endl;
	return 1;
}
