#include <iostream>
#include <vector>
#include <string>
#define DEBUG
using namespace std;

class Solution {
    private:
        // somewhere wrong
        int convert( string &word1, string &word2, int index1, int index2,
                vector< vector<int> > &distance, int depth);
        int convertFaster( string &word1, string &word2);
    public:
        int minDistance(string word1, string word2);
};

int Solution::convertFaster( string &word1, string &word2) {
    int m = word1.size();
    int n = word2.size();
    if (n == 0) return m;
    if (m == 0) return n;
    vector< vector<int> > distance(m+1, vector<int>(n+1, 0));
    for ( int i = 0; i <= m; i ++) {
        distance[i][0] = i;
    }
    for ( int i = 0; i <= n; i ++) {
        distance[0][i] = i;
    }

    for ( int i = 1; i <= m; i ++) {
        for ( int j = 1;  j <= n; j ++) {
            int min = distance[i-1][j-1];
            if (word1[i-1] != word2[j-1]) {
                min = min +1;
            }
            //insert
            if (min > distance[i][j-1]+1) {
                min = distance[i][j-1] + 1;
            }
            //delete
            if (min > distance[i-1][j]+1) {
                min = distance[i-1][j] + 1;
            }
            distance[i][j] = min;
        }
    }

    return distance[m][n];
}


int Solution::convert( string &word1, string &word2, int index1, int index2,
        vector< vector<int> > &distance, int depth) {
    if (distance[index2][index1] != -1) {
        return distance[index2][index1];
    }
    if (depth > (signed)word1.size()) {
        distance[index2][index1] = (signed)word1.size()+1;
        return (signed)word1.size()+1;
    }
    if ( word1.substr(index1) == word2.substr(index2)) {
        distance[index2][index1] = 0;
        return 0;
    } else if (index2 == (signed)word2.size() - 1) {
        int count = 0;
        if (word1[index1] == word2[index2]) { 
            if (index1 == (signed) word1.size()-1) {
                distance[index2][index1] = count;
                return count;
            } else {
                count += (signed)word1.size() - index1 - 1;
                distance[index2][index1] = count;
                return count;
            }
        } else { 
            if ( index1 == (signed)word1.size()-1) {
                count += 1; 
                distance[index2][index1] = count;
                return count;
            }
        }
    } else if (index1 == (signed)word1.size() - 1) {
        int count = 0;
        if (word1[index1] != word2[index2]) { count += 1; }
        if ( index2 != (signed)word2.size() - 1) {
            count += (signed)word2.size() - index2 - 1;
        }
        distance[index2][index1] = count;
        return count;
    }
    int count = 0;
    if (word1[index1] == word2[index2]) {
        count = convert(word1, word2, index1+1, index2+1, distance, depth);
    } else {
        //replace
        int replaceCount = word2.size();
        if ( index2 < (signed)word2.size() - 1) {
            replaceCount = convert(word1, word2, index1 + 1, index2+1, distance, depth+1);
        } else {
            replaceCount = (signed)word1.size() - index1 - 2;
        }
        //insert
        int insertCount = word2.size();
        if ( index2 < (signed)word2.size()-1) {
            insertCount = convert(word1, word2, index1, index2+1, distance, depth+1);
        } else {
            insertCount = (signed)word1.size() - index1 - 1;
        }
        //delete
        int deleteCount = convert(word1, word2, index1 + 1, index2, distance, depth+1);
        if (insertCount > deleteCount) {
            count = deleteCount;  
        } else {
            count = insertCount;
        }
        if ( count > replaceCount) {
            count = replaceCount;
        }
        count ++;
    }
    distance[index2][index1] = count;
    return count;
}

int Solution::minDistance(string word1, string word2) {
    /*
    int m = word1.size();
    int n = word2.size();
    if (n == 0) return m;
    if (m == 0) return n;
    vector< vector<int> > distance(n, vector<int>(m, -1));
    int minCount = convert( word1, word2, 0, 0, distance, 0);
    return minCount;
    */
    return convertFaster( word1, word2);
}

int main(int argc, char *argv[]) {
    Solution s;
    /*
    string str1("abcdefg");
    string str2("a2d");
    */
    /*
    string str1("mart");
    string str2("karma");
    */
    /*
    string str1("trinitrophenylmethylnitramine");
    string str2("dinitrophenylhydrazine");
    */
    string str1("pneumonoultramicroscopicsilicovolcanoconiosis");
    string str2("ultramicroscopically");
    cout << s.minDistance( str1, str2) << endl;
    return 1;
}
