#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#define DEBUG
using namespace std;

class Solution {
    private:
        bool search(vector<vector<char> > &board, string &word, int index, 
                int posI, int posJ,
                vector<vector<char> > &accessed) {
            if ( board[posI][posJ] != word[index] ) return false;
            if (index+1 == (signed)word.size())   return true;
            bool flag = false;
            accessed[posI][posJ] = '1';
            int nextI = posI;
            int nextJ = (posJ+1)%board[posI].size();
            if ( accessed[nextI][nextJ] == '0') {
                flag |= search(board, word, index+1, nextI, nextJ, accessed);
                if (flag)  return true;
            }
            nextI = (posI+1)%board.size();
            nextJ = posJ;
            if ( accessed[nextI][nextJ] == '0') {
                flag |= search(board, word, index+1, nextI, nextJ, accessed);
                if(flag) return true;
            }
            nextI = (posI-1)%board.size();
            nextJ = posJ;
            if ( accessed[nextI][nextJ] == '0') {
                flag |= search(board, word, index+1, nextI, nextJ, accessed);
                if (flag)  return true;
            }
            nextI = posI;
            nextJ = (posJ-1)%board[posI].size();
            if ( accessed[nextI][nextJ] == '0') {
                flag |= search(board, word, index+1, nextI, nextJ, accessed);
                if (flag)  return true;
            }
            accessed[posI][posJ] = '0';
            return false;
        }
    public:
        bool exist(vector<vector<char> > &board, string word) {
            if (word.empty() )  return true;

            vector<vector<char> > accessed(board.size(), vector<char>(board[0].size(), '0'));
            for ( int i = 0; i < board.size(); i ++) {
                for ( int j = 0; j < board[i].size(); j ++ ){
                    if (word[0] == board[i][j]) {
                        bool flag = search(board, word, 0, i, j, accessed);
                        if (flag)   return true;
                    }
                }
            }
            return false;
        }
};

int main(int argc, char *argv[]) {
    Solution s;
    string total("ABCESFCSADEE");
    struct timeval first;
    struct timeval second;
    /*
    vector< vector<char>> board;
    for ( int i = 0; i < (signed)total.size(); i ++) {
        vector<char> tmp;
        for ( int j = 0; j < 4; j ++) {
            tmp.push_back(total[i*4 + j]);
        }
        board.push_back(tmp);
    }
    string word1("ABCCED");
    gettimeofday(&first, NULL);
    cout << s.exist(board, word1) << "---------expected-----" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;

    string word2("SEE");
    gettimeofday(&first, NULL);
    cout << s.exist(board, word2) << "---------expected-----" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;

    string word3("ABCB");
    gettimeofday(&first, NULL);
    cout << s.exist(board, word3) << "---------expected------" << 0 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;


    string a("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    vector< vector<char> > board1;
    for ( int i = 0; i < 29; i ++ ) {
        vector<char> tmp('a', a.size());
        board1.push_back(tmp);
    }
    string b("aaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
    vector<char> tmp1;
    for ( int i = 0; i < (signed)b.size(); i ++) {
        tmp1.push_back(b[i]);
    }
    board1.push_back(tmp1);
    string word4("baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    cout << "word len    " << word4.size() << endl;
    cout << s.exist(board1, word4) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;

    string word5("ba");
    char arr[] = {'a', 'b'};
    vector<char> tmpabc(arr, arr + sizeof(arr)/sizeof(char));
    vector< vector<char> > board2;
    board2.push_back(tmpabc);
    gettimeofday(&first, NULL);
    cout << s.exist(board2, word5) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;

    string word6("ABCESEEEFS");
    string str1[] = {"ABCE", "SFES", "ADEE"};
    vector< vector<char> > board3;
    for ( int i = 0; i < 3; i ++) {
        vector<char> tmp;
        for ( int j = 0; j < 4; j ++) {
            tmp.push_back(str1[i][j]);
        }
        board3.push_back(tmp);
    }
    gettimeofday(&first, NULL);
    cout << s.exist(board3, word6) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;
    */
    string word7("aabaaaabbb");
    string str2[] = {"aaa","abb","abb","bbb","bbb","aaa","bbb","abb","aab","aba"};
    vector< vector<char> > board4;
    for ( int i = 0; i < 3; i ++) {
        vector<char> tmp;
        for ( int j = 0; j < 4; j ++) {
            tmp.push_back(str2[i][j]);
        }
        board4.push_back(tmp);
    } 
    gettimeofday(&first, NULL);
    cout << s.exist(board4, word7) << "---------expected------" << 0 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;
    
	return 1;
}
