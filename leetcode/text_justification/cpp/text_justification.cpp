#include <iostream>
#include <string>
#include <vector>
#include <map>
#define DEBUG
using namespace std;

class Solution {
	private:
		void mergesort(vector<unsigned int> &v_len);
	public:
		vector<string> fullJustify(vector<string> &words, int L);
};
void Solution::mergesort(vector<unsigned int> &v_len) {
	if (!v_len.size()) return;
	int len = v_len.size();
	vector<unsigned int> tmp;
	for (int i = 1; i < len/2 +1; i *= 2) {
		int merge_count = i << 1;
		for ( int j = 0; j < len; j++) {
			int left = j;
			int mid = j + merge_count; //start of next
			if ( mid >= len) continue;
			int right = mid + merge_count - 1;
			if (right >= len) right = len - 1;
			int m = left, n = mid;
			while((m < mid) && (n <= right)) {
				if ( v_len[m] >= v_len[n] )
					tmp.push_back(v_len[m++]);
				else 
					tmp.push_back(v_len[n++]);
			}
			while ((m) < mid) tmp.push_back(v_len[m++]);
			while ((n) <= right) tmp.push_back(v_len[n++]);
			int l = 0;
			for ( int k = left; k <= right; k ++ ) {
				v_len[k] = tmp[l++];	
			}
			tmp.clear();
		}
	}	
} 

vector<string> Solution::fullJustify(vector<string> &words, int L) {
	vector<string> res;
	if (L<0) return res;
	if (!L && ((words.size() != 1) || ((words.size() == 1) && (words[0].size() != 0)))) return res;
	if (!words.size()) {
		string s;
		for (int i = 0; i < L; i ++) s += ' ';
		res.push_back(s);
		return res;
	}
	vector<unsigned int> v_len;
	map<unsigned int, vector<int> > len_map;
	for (unsigned int i = 0; i < words.size(); i ++)  {
		int len = words[i].size();
		v_len.push_back(len);
		len_map[len].push_back(i);
	}
	//mergesort(v_len);

	unsigned int count = 0; 	
	vector<int> container;	
	while (count < words.size()) {
		int remain = L;
		for (int i = 0; i < v_len.size(); i ++ ) {
			if ( v_len[i] == -1) continue;
			if ( v_len[i] <= remain ) {
				container.push_back(len_map[v_len[i]].front());
				len_map[v_len[i]].erase(len_map[v_len[i]].begin());
				remain -= v_len[i];
				v_len[i] = -1;
				count ++;
				continue;
			}
		}
		int pad = 0;
		int extra_add_one = 0;
		// divide 0, floating point exception
		//if (count != v_len.size()) {
		if (container.size() != 1) {
			pad = remain/(container.size() -1);
			extra_add_one = remain%(container.size() -1);
		} else {
			pad =remain;
		}
		//} else {
		//	pad = 1;
		//	extra_add_one = 0;
		//}
		string line;
		for ( int i = 0; i < container.size(); i ++) {
			line += words[container[i]];
			if ( count == v_len.size()) continue;
			if ( i == container.size() - 1) break;
			for (int j = 0; j < (pad + extra_add_one); j ++) {
				line += ' ';	
			}
			if (extra_add_one > 0) extra_add_one --;
		}	
		if ((count == words.size()) && (remain>0)) {
			for (int j = 0; j < remain; j ++) {
				line += ' ';	
			}
		}
		container.clear();
		res.push_back(line);
	}
	return res;
}

int main(int argc, char *argv[]){
	Solution s;
	string word_list[] = {"This", "is", "an", "example", "of", "text", "justification"};
	//string word_list[] = {"Give", "me", "a", "new", "TEST", "text", "justification"};
	vector<string> words;
	for ( int i = 0; i < 7; i ++ ) {
		words.push_back(word_list[i]);
	}
	vector<string> res = s.fullJustify(words, 16);
	for (unsigned int i = 0; i < res.size(); i ++) {
		cout << "\""<< res[i] <<"\""<< endl;	
	}

	string word_list_l[] = {""};
	//string word_list[] = {"Give", "me", "a", "new", "TEST", "text", "justification"};
	words.clear();
	for ( int i = 0; i < 1; i ++ ) {
		words.push_back(word_list_l[i]);
	}
	res = s.fullJustify(words, 16);
	for (unsigned int i = 0; i < res.size(); i ++) {
		cout << "\""<< res[i] <<"\""<< endl;	
	}

	string word_list_ll[] = {"a", "b", "c", "d", "e"};
	//string word_list[] = {"Give", "me", "a", "new", "TEST", "text", "justification"};
	words.clear();
	for ( int i = 0; i < 5; i ++ ) {
		words.push_back(word_list_ll[i]);
	}
	res = s.fullJustify(words, 1);
	for (unsigned int i = 0; i < res.size(); i ++) {
		cout << "\""<< res[i] <<"\""<< endl;	
	}

	string word_list_lll[] = {"a\0", "b\0", "c\0", "d\0", "e\0"};
	//string word_list[] = {"Give", "me", "a", "new", "TEST", "text", "justification"};
	words.clear();
	for ( int i = 0; i < 5; i ++ ) {
		words.push_back(word_list_lll[i]);
	}
	res = s.fullJustify(words, 3);
	for (unsigned int i = 0; i < res.size(); i ++) {
		cout << "\""<< res[i] <<"\""<< endl;	
	}
	return 1;
}
