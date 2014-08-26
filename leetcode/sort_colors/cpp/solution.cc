#include <iostream>
#define DEBUG
using namespace std;

class Solution {
private:
    void quicksort(int A[], int left, int right);
public:
    void sortColors(int A[], int n);
};

void Solution::quicksort( int A[], int left, int right) {
    if (left >= right) { return; }
    int i = left-1, j = left;
    int pivot = A[right];
    while (j < right) {
        if (A[j] <= pivot) {
            i ++;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
        j ++;
    }
    A[right] = A[++i];
    A[i] = pivot;
    quicksort(A, left, i - 1);
    quicksort(A, i + 1, right);
}

void Solution::sortColors(int A[], int n) {
   quicksort( A, 0, n-1); 
}

int main(int argc, char *argv[]) {
	return 1;
}
