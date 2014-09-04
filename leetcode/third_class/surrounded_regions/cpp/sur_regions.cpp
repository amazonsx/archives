#include <iostream>
#include <vector>
#include <stack>
#define DEBUG
using namespace std;

struct Coords {
	int y_;
	int x_;
	Coords(): y_(0), x_(0){}
	Coords(int y, int x):y_(y), x_(x){};
};

class Solution {
	private:
		void push_o(stack<Coords> &o_stack, int j, int i){
			Coords o_coords(j, i);
			o_stack.push(o_coords);
		}
	public:
		void solve(vector<vector<char> > &board);
};
void Solution::solve(vector<vector<char> > &board) {
	// identify the height and width of board
	int height = board.size();
	if (height == 0) return;
	int width = board[0].size();
	if (width == 0) return;
	// init a new two-dimensional vector to store all flags
	// Or just reflag the points in place
	// X: unchangable; O: at the beginning and changable at last; 
	// #: unchangable and should be resumed to O
	// and a queue to handle all extendable Os
	stack<Coords> o_stack;
	// traverse all the edges
	for(int i = 0; i < width; i ++) {
		if(board[0][i] == 'O')	push_o(o_stack, 0, i);
		if(board[height-1][i] == 'O')	push_o(o_stack, height-1, i);
	}
	for (int i = 1; i < height - 1; i ++) {
		if (board[i][0] == 'O')	push_o(o_stack, i, 0); 
		if (board[i][width-1] == 'O')	push_o(o_stack, i, width-1); 
	}
	//check the stack and chage
	Coords o_extendable;
	int x =0, y = 0;
	while (!o_stack.empty()) {
		o_extendable = o_stack.top();			
		o_stack.pop();
		x = o_extendable.x_;
		y = o_extendable.y_;
		if (board[y][x] == '#') continue;
		else {
			board[y][x] = '#';
			if ((x!=0) && (board[y][x-1] == 'O')) push_o( o_stack, y, x - 1);
			if ((x!=(width-1)) && (board[y][x+1] == 'O')) push_o( o_stack, y, x+1);
			if ((y!=0) && (board[y-1][x] == 'O')) push_o( o_stack, y-1, x);
			if ((y!=height-1) && (board[y+1][x] == 'O')) push_o( o_stack, y+1, x);
		}
	}
	for (int j = 0; j < height; j ++) {
		for (int i = 0; i < width; i ++) {
			if (board[j][i] == 'O') board[j][i] = 'X';
			else if (board[j][i] == '#') board[j][i] = 'O';
		}
	}
}

int main(int argc, char *argv[]) {
	//"XOXOXO","OXOXOX","XOXOXO","OXOXOX"
	vector<vector<char> > board;
	vector<char> v;
	char arr1[] = "XOXOXO";
	for (unsigned int i = 0; i < sizeof(arr1)/sizeof(char) -1; i++) { v.push_back(arr1[i]); }
	board.push_back(v);
	v.clear();
	char arr2[] = "OXOXOX";
	for (unsigned int i = 0; i < sizeof(arr2)/sizeof(char) -1; i++) { v.push_back(arr2[i]); }
	board.push_back(v);
	v.clear();
	char arr3[] = "XOXOXO";
	for (unsigned int i = 0; i < sizeof(arr3)/sizeof(char) -1; i++) { v.push_back(arr3[i]); }
	board.push_back(v);
	v.clear();
	char arr4[] = "OXOXOX";
	for (unsigned int i = 0; i < sizeof(arr4)/sizeof(char) -1; i++) { v.push_back(arr4[i]); }
	board.push_back(v);
	v.clear();
	Solution s;
	s.solve(board);
	return 1;
}
