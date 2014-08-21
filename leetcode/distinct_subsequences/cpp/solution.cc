#include <iostream>
#include <sys/time.h>
#include <map>
#include <unordered_set>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
private:
    bool matchSubseq(string &S, string &T, int posS, int posT, 
            map<int, unordered_set<int> > &unmatchSet,
            map<int, map<int, vector<vector<int> > > > &seqMap);
    bool matchSubseqFaster(string &S, string &T, int posS, int posT, 
            map<int, unordered_set<int> > &unmatchSet,
            map<int, map<int, int > > &seqMap);
    int matchSubseqFasterer(string &S, string &T);
    int matchSubseqFastest(string &S, string &T);
public:
    int numDistinct( string S, string T);
};

int Solution::matchSubseqFastest(string &S, string &T) {
    int m = S.size();
    int n = T.size();
    vector<int> path(n+1, 0);
    path[0] = 1;
    for ( int i = 1; i <= m; i ++) {
        for ( int j = n; j >=1; j --) {
            path[j] = path[j] + ((S[i-1] == T[j-1])?path[j-1]: 0);
        }
    }
    return path[n];
}

int Solution::matchSubseqFasterer( string &S, string &T) {
    int m = S.size();
    int n = T.size();
    vector< vector<int> > path(n+1, vector<int>(m+1, 0));
    for ( int i = 0; i <= m; i ++) {
        path[0][i] = 1;
    }
    for ( int i = 1; i <= m; i ++) {
        for ( int j = 1;  j <= n; j ++) {
            path[j][i] = path[j][i-1] + ((S[i-1] == T[j-1])?path[j-1][i-1]: 0);
        }
    }
    return path[n][m];
}


bool Solution::matchSubseqFaster(string &S, string &T, int posS, int posT, 
        map<int, unordered_set<int> > &unmatchSet,
        map<int, map<int, int> >  &seqMap) {
    int len = T.size() - posT;
    if ( unmatchSet[len].find(posS) != unmatchSet[len].end()) {
        return false;
    }
    if (seqMap[len].find(posS) != seqMap[len].end()) {
        if (seqMap[len][posS] > 0)  return true;
    }
    if ( S[posS] != T[posT]) {
        unmatchSet[len].insert(posS);
        return false;
    }
    if ( posT == (signed)T.size() - 1) {
        seqMap[1][posS] ++;
        return true;
    }
    bool ret_flag = false;
    for ( int i = posS+1; i <= (signed)(S.size() + posT - T.size() + 1); i ++) {
        if ( S[i] != T[posT+1]) {
            unmatchSet[len-1].insert(i);
            continue;
        }
        bool flag = matchSubseqFaster( S, T, i, posT+1, unmatchSet, seqMap);
        ret_flag |= flag;
        if (flag) {
            seqMap[len][posS] += seqMap[len-1][i];
        }
    }
    return ret_flag;
}

bool Solution::matchSubseq(string &S, string &T, int posS, int posT, 
        map<int, unordered_set<int> > &unmatchSet,
        map<int, map<int, vector<vector<int> > > >  &seqMap) {
    int len = T.size() - posT;
    if ( unmatchSet[len].find(posS) != unmatchSet[len].end()) {
        return false;
    }
    if (seqMap[len].find(posS) != seqMap[len].end()) {
        if (!seqMap[len][posS].empty())  return true;
    }
    if ( S[posS] != T[posT]) {
        unmatchSet[len].insert(posS);
        return false;
    }
    vector<int> tmp;
    if ( posT == (signed)T.size() - 1) {
        seqMap[1][posS].push_back(tmp);
        return true;
    }
    bool ret_flag = false;
    for ( int i = posS+1; i <= (signed)(S.size() + posT - T.size() + 1); i ++) {
        if ( S[i] != T[posT+1]) {
            unmatchSet[len-1].insert(i);
            continue;
        }
        bool flag = matchSubseq( S, T, i, posT+1, unmatchSet, seqMap);
        ret_flag |= flag;
        if (flag) {
            for ( int j = 0; j < (signed)seqMap[len-1][i].size(); j ++) {
                tmp.clear();
                tmp.push_back(S[i]);
                seqMap[len][posS].push_back(tmp);
                seqMap[len][posS].back().insert( seqMap[len][posS].back().end(),
                        seqMap[len-1][i][j].begin(), seqMap[len-1][i][j].end());
            }
        }
    }
    return ret_flag;
}

int Solution::numDistinct( string S, string T) {
    if (S.size() < T.size())    return 0;
    if (S.size() == T.size()) {
        if (S == T) return 1;
        else    return 0;
    }
    /*
    map<int, map<int, vector< vector<int> > >> seqMap;
    map<int, unordered_set<int> > unmatchSet;
    for ( int i = 0; i <= (signed)(S.size()-T.size()); i ++) {
        matchSubseq( S, T, i, 0, unmatchSet, seqMap);
    }
    int count = 0;
    map<int, vector< vector<int> > > ::iterator iter = seqMap[T.size()].begin();
    for ( ; iter != seqMap[T.size()].end(); iter ++) {
        count += (signed)iter->second.size();
    }
    */

    /*
    map<int, map<int, int >> seqMap;
    map<int, unordered_set<int> > unmatchSet;
    for ( int i = 0; i <= (signed)(S.size()-T.size()); i ++) {
        matchSubseqFaster( S, T, i, 0, unmatchSet, seqMap);
    }
    int count = 0;
    map<int, int> ::iterator iter = seqMap[T.size()].begin();
    for ( ; iter != seqMap[T.size()].end(); iter ++) {
        count += (signed)iter->second;
    }
    return count;
    */
    //return matchSubseqFasterer(S, T);
    return matchSubseqFastest(S, T);
}

int main(int argc, char *argv[]) {
    Solution s;
    /*
    string S("rabbbit");
    string T("rabbit");
    */
    /*
    string S("aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe");
    string T("bddabdcae");
    */
    string S("xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo");
    string T("rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys");
    timeval first, second;
    gettimeofday(&first, NULL);
    int count = s.numDistinct(S, T);
    gettimeofday(&second, NULL);
    cout << "time cost ---- " << 1000000*(second.tv_sec - first.tv_sec) + (second.tv_usec - first.tv_usec) << endl;
    cout << count << endl;
	return 1;
}
