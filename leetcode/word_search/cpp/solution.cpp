#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#define DEBUG
using namespace std;

struct Letter {
    int i;
    int j;
    Letter(): i(-1),j(-1){}
    Letter(int i, int j): i(i),j(j){}
};

class Solution {
private:
    // TODO(shixiao):
    // There are some bugs in the brute force method;
    bool searchBruteForce(map<char, vector<Letter> > &letterMap, string &word, 
            int start, int width, vector<int> &usageMap, 
            map<int, map <int,map<int, int>> > &resMap, Letter *last);
    // NOTE(shixiao):
    // this method cannot use the resMap, because there is a chance that the current value,
    // which may be in the right order to be accessed, was accessed in the right order with 
    // a wrong path, which would record the misleading false result in resMap, making the 
    // right path misunderstand that there is no way following this path.
    //bool search(vector<vector<char>> &board, int curI, int curJ, int start, string &word,
    //        vector<int> &usageMap, map<int, map<int, map<int, int>>> &resMap);
    bool search(vector<vector<char>> &board, int curI, int curJ, int start, string &word,
            vector<int> &usageMap);
public:
    bool existBruteForce(vector<vector<char> > &board, string word);
    bool exist(vector<vector<char> > &board, string word);
};

bool Solution::search(vector<vector<char>> &board, int curI, int curJ, int start, string &word,
        vector<int> &usageMap) {
    //char current = word[start];
    //cout << curI << "    " << curJ << endl;
    if (start == (signed)(word.size()-1))
        return true;
    char next = word[start + 1];
    int height = board.size(), width = board[0].size();
    vector<Letter> neighbors;
    Letter neighbor;
    if ((curI+1) < height) {
        if ((board[curI+1][curJ] == next) && (usageMap[(curI + 1)*width + curJ] == 0)) {
            neighbor.i = curI + 1;
            neighbor.j = curJ;
            neighbors.push_back(neighbor);
        }
    }else {
        if ((curI+1) != curI) {
            if ((board[0][curJ] == next) && (usageMap[(0)*width + curJ] == 0)){
                neighbor.i = 0;
                neighbor.j = curJ;
                neighbors.push_back(neighbor);
            }
        }
    }
    if ((curI-1) >= 0) {
        if ((board[curI - 1][curJ] == next) && (usageMap[(curI - 1)*width + curJ] == 0)){
            neighbor.i = curI - 1;
            neighbor.j = curJ;
            neighbors.push_back(neighbor);
        }
    } else {
        if ((curI-1) != curI) {
            if ((board[height-1][curJ] == next) && (usageMap[(height - 1)*width + curJ] == 0)){
                neighbor.i = height - 1;
                neighbor.j = curJ;
                neighbors.push_back(neighbor);
            }
        }
    }
    if ((curJ+1) < width) {
        if ((board[curI][curJ + 1] == next) && (usageMap[ curI * width + curJ + 1] == 0)) {
            neighbor.i = curI;
            neighbor.j = curJ + 1;
            neighbors.push_back(neighbor);
        }
    } else {
        if ((curJ+1) != curJ) {
            if ((board[curI][0] == next) && (usageMap[ curI * width + 0] == 0)) {
                neighbor.i = curI;
                neighbor.j = 0;
                neighbors.push_back(neighbor);
            }
        }
    }
    if ((curJ-1) >= 0) {
        if ((board[curI][curJ - 1] == next) && (usageMap[curI * width + curJ - 1] == 0)) {
            neighbor.i = curI;
            neighbor.j = curJ - 1;
            neighbors.push_back(neighbor);
        }
    } else {
        if ((curJ-1) != curJ) {
            if ((board[curI][width-1] == next) && (usageMap[ curI * width + width -1] == 0)) {
                neighbor.i = curI;
                neighbor.j = width - 1;
                neighbors.push_back(neighbor);
            }
        }
    }
    if (neighbors.empty()) {
        return false;
    }
    bool flag = false;
    for ( int i = 0; i < (signed)neighbors.size(); i ++) {
        usageMap[curI * width + curJ] = 1;
        flag  = search(board, neighbors[i].i, neighbors[i].j, start+1, word, usageMap);
        if (flag) {
            break;
        } else {
            usageMap[curI * width + curJ] = 0;
        }
    }
    return flag;
}

bool Solution::exist(vector<vector<char> > &board, string word){
    if (board.empty() && word.size() != 0)  return false;  
    int iSum = (signed)board.size(), jSum = (signed)board[0].size();
    if (iSum*jSum < (signed)word.size())   return false;
    vector<Letter> beginPos;
    for ( int i = 0; i < iSum; i ++) {
        for ( int j = 0; j < jSum; j ++) {
            if (board[i][j] == word[0]) {
                Letter letter(i, j);
                beginPos.push_back(letter);
            }
        }
    }
    vector<int> usageMap( iSum*jSum, 0);

    bool res = false;
    for ( int i = 0; i < (signed)beginPos.size(); i ++) {
        res |= search(board, beginPos[i].i, beginPos[i].j, 0, word, usageMap);
        if (res)    break;
    }
    return res;
}

bool Solution::searchBruteForce(map<char, vector<Letter> > &letterMap, string &word, 
        int start, int width, vector<int> &usageMap, map<int, map<int, map<int, int>>>  &resMap,
        Letter *last) {
    //if ( start == word.size())  return true;
    if (letterMap.find(word[start]) == letterMap.end()) {return false; }
    bool flag = false;
    vector<Letter> letters = letterMap[word[start]];
    for ( vector<Letter>::iterator iter = letters.begin();
            iter != letters.end(); iter ++) {
        Letter letter = *iter;
        if ( usageMap[ letter.i * width + letter.j ] == 1)  continue;
        if (resMap.find(start) != resMap.end())
            if (resMap[start].find(letter.i) != resMap[start].end())
                if (resMap[start][letter.i].find(letter.j) != resMap[start][letter.i].end())
                    continue;
        if (last != NULL) {
            if (!(((abs(last->i - letter.i) == 1) && ( last->j == letter.j)) 
                        ||((abs(last->j - letter.j) == 1) && ( last->i == letter.i))))
                continue;
        }
        usageMap[ letter.i * width + letter.j ] = 1;
        if (start == (signed)word.size())   return true;
        flag |= searchBruteForce( letterMap, word, start+1, width, usageMap, resMap, &letter);
        if (flag) {
            break;
        } else {
            resMap[start][letter.i][letter.j] = 1;
            usageMap[ letter.i * width + letter.j ] = 0;
        }
    }
    return flag;
}

bool Solution::existBruteForce(vector<vector<char> > &board, string word){
    if (board.empty() && word.size() != 0)  return false;  
    int iSum = (signed)board.size(), jSum = (signed)board[0].size();
    if (iSum*jSum < (signed)word.size())   return false;
    map< char, vector<Letter>> letterMap;
    for ( int i = 0; i < iSum; i ++) {
        for ( int j = 0; j < jSum; j ++) {
            Letter letter(i, j);
            letterMap[board[i][j]].push_back(letter);
        }
    }
    vector<int> usageMap( iSum*jSum, 0);
    map<int, map<int, map<int, int> > > resMap;

    bool res = false;
    res = searchBruteForce(letterMap, word, 0, jSum, usageMap, resMap, NULL);
    return res;
}

int main(int argc, char *argv[]) {
    Solution s;
    string total("ABCESFCSADEE");
    vector< vector<char>> board;
    for ( int i = 0; i < (signed)total.size(); i ++) {
        vector<char> tmp;
        for ( int j = 0; j < 4; j ++) {
            tmp.push_back(total[i*4 + j]);
        }
        board.push_back(tmp);
    }
    string word1("ABCCED");
    struct timeval first;
    gettimeofday(&first, NULL);
    cout << s.existBruteForce(board, word1) << "---------expected-----" << 1 << endl;
    struct timeval second;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
    gettimeofday(&first, NULL);
    cout << s.exist(board, word1) << "---------expected-----" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;

    string word2("SEE");
    gettimeofday(&first, NULL);
    cout << s.existBruteForce(board, word2) << "---------expected-----" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
    gettimeofday(&first, NULL);
    cout << s.exist(board, word2) << "---------expected-----" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;

    string word3("ABCB");
    gettimeofday(&first, NULL);
    cout << s.existBruteForce(board, word3) << "---------expected------" << 0 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
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
    gettimeofday(&first, NULL);
    cout << s.existBruteForce(board1, word4) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
    gettimeofday(&first, NULL);
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
    cout << s.existBruteForce(board2, word5) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
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
    cout << s.existBruteForce(board3, word6) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl << endl;
    gettimeofday(&first, NULL);
    cout << s.exist(board3, word6) << "---------expected------" << 1 << endl;
    gettimeofday(&second, NULL);
    cout << "The time cost is ----"  << 1000000*(second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
    cout << "---------------------------------------------------" << endl << endl;
    
	return 1;
}
