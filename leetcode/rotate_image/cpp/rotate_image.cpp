#include <iostream>
#include <vector>
#include <stdlib.h>
#define DEBUG
using namespace std;

class Solution {
	public:
		void rotate(vector< vector<int> > &matrix);
};

void Solution::rotate(vector<vector<int> > &matrix) {
	int n = matrix.size();
	if (n == 0) return;
	int tmp = 0;
	int a = 0, b = 0;
	int c = 0, d = 0;
	int e = 0, f = 0;
	int g = 0, h = 0;
	for (int i = 0; i < n - 1; i ++) {
		for ( int j = i; j < n - 1 - i; j ++) {
			a = i; b = j;
			c = b; d = n - 1 - a;
			e = d; f = n - 1 - c;
			g = f; h = n - 1 - e;
			tmp  = matrix[a][b];
			matrix[a][b] =  matrix[g][h];
			matrix[g][h] =  matrix[e][f];
			matrix[e][f] =  matrix[c][d];
			matrix[c][d] =  tmp;
		}
	}
}

int main(int argc, char *argv[]) {
	Solution s;
	int n = 5;
	vector<vector<int> >  total;
	for (int i = 0; i < 5; i ++) {
		vector<int> line;
		for (int j = 0; j < 5; j ++) {
			line.push_back(rand()%100);
			cout << line[j] << "  ";
		}
		cout << endl;
		total.push_back(line);
	}
	cout << endl;
	cout << endl;
	cout << endl;
	s.rotate(total);
	for (int i = 0; i < 5; i ++) {
		for (int j = 0; j < 5; j ++) {
			cout << total[i][j] << "  " ;
		}
		cout << endl;
	}

	return 1;
}
