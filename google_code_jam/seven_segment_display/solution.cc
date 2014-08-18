#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define DEBUG
using namespace std;

class Solution {
    private:
        map<int, string> m_disMap;
        map< string, vector<int>> m_reversedDisMap;
    public:
        string displayNext(vector<string > &originStates);
        void process(string infPath, string outfPath);
        Solution();
};
void Solution::process(string infPath, string outPath) {
    fstream src, dst; 
    src.open(infPath);
    dst.open(outPath);

    filebuf* inbuf = src.rdbuf();
    filebuf* outbuf = dst.rdbuf();

    char c = inbuf->sbumpc();
    string caseCountStr = "";
    while (c != '\n') {
        caseCountStr += c;
        c = inbuf -> sbumpc();
    }
    int caseCount = stoi(caseCountStr); 
    c = inbuf -> sbumpc();
    for ( int i = 0; i < caseCount; i ++) {
        string line("");
        vector<string> lineContent;
        while (c != '\n') { 
            if ( c != ' ') {
                line += c;
            } else  {
                lineContent.push_back(line);
                line.clear();
            }
            c = inbuf -> sbumpc();
            if ( c == '\n') {
                lineContent.push_back(line);
                line.clear();
            }
        } 
        c = inbuf -> sbumpc();

        int stateCount = stoi(lineContent.front());
        vector<string> states = lineContent;
        states.erase(states.begin());
        assert((signed)states.size() == stateCount);
        string res = displayNext(states);
        string output(""); 
        char index[10];
        sprintf(index, "%d", i+1);
        output += "Case #"; 
        output.append(index);
        output += ": ";
        if( res == "") {
            res = "ERROR!";
        }
        output += res + "\n";
        for ( int j = 0; j < (signed)output.size(); j ++ ) {
            outbuf->sputc(output[j]);
        }
    }
    src.close();
    dst.close();
}


// ret "" means error
string Solution::displayNext( vector<string> &originStates) {
    vector<int> workable(7, 0);
    vector<string> states = originStates;
    map<int, string> disMap = m_disMap;
    map<string, vector<int>> reversedDisMap; // = m_reversedDisMap;

    for ( int i = 0; i < (signed) states.size(); i ++) {
        for ( int j = 0; j < 7; j ++) {
            if ( workable[j] == 1)  continue;
            if (states[i][j] == '1')  workable[j] = 1;
        }
    }
    for ( int i = 0; i < (signed) states.size(); i ++) {
        int j = 0;
        string::iterator iter = states[i].begin();
        while (iter != states[i].end()) {
            if (workable[j++] == 0) {
                iter = states[i].erase(iter);
            } else iter ++;
        }
    }
    for ( int i = 0; i < 10; i ++) {
        int j = 0;
        string::iterator iter = disMap[i].begin();
        while (iter != disMap[i].end()) {
            if (workable[j++] == 0) {
                iter = disMap[i].erase(iter);
            } else iter ++;
        }
    }

    for ( int i = 0; i < 10; i ++) {
        reversedDisMap[disMap[i]].push_back(i);
    }
    vector<int> current;
    for ( int i = 0; i < (signed) states.size(); i ++) {
        if (reversedDisMap.find(states[i]) == reversedDisMap.end()) {
            return "";
        }
        if (current.empty()) {
            current = reversedDisMap[states[i]];
        } else {
            vector<int> *former = &(reversedDisMap[states[i]]);
            vector<int> tmp;
            for ( int j = 0 ; j < (signed)former->size(); j ++) {
                /*
                if (((*former)[j] < current[0] - 1) || ((*former)[j] > current.back() - 1)) {
                    continue;
                }
                */
                for ( vector<int>::iterator iter = current.begin();
                        iter != current.end(); iter ++) {
                    if (*iter == (*former)[j] + 1) {
                        tmp.push_back((*former)[j]);
                        iter = current.erase(iter);
                        break;
                    }
                }
            }
            current = tmp;
        }
    }
    if (current.size() != 1)    return "";
    int next = (current[0] + 9)%10;
    for ( int j = 0; j < 7; j ++) {
        if (workable[j] == 1)   continue;
        int flag = 0;
        for ( int i = (signed)originStates.size() - 1; i >= 0; i --) {
            int num = (next + 11 + originStates.size() - i - 1 ) % 10;
            if ( originStates[i][j] != m_disMap[num][j]){
                flag = 1;
                break;
            }
        }
        if (flag == 0)  workable[j] = 1;
    }
    string res;
    for ( int i = 0; i < 7; i ++) {
        if (workable[i] == 0) {
            res += '0';
        } else {
            res += m_disMap[next][i];
        }
    }
    return res;
}


Solution::Solution() {
    // init disMap
    string str0("1111110");
    m_disMap[0] = str0;
    string str1("0110000");
    m_disMap[1] = str1;
    string str2("1101101");
    m_disMap[2] = str2;
    string str3("1111001");
    m_disMap[3] = str3;
    string str4("0110011");
    m_disMap[4] = str4;
    string str5("1011011");
    m_disMap[5] = str5;
    string str6("1011111");
    m_disMap[6] = str6;
    string str7("1110000");
    m_disMap[7] = str7;
    string str8("1111111");
    m_disMap[8] = str8;
    string str9("1111011");
    m_disMap[9] = str9;

    for ( int i = 0; i < 10; i ++) {
        m_reversedDisMap[m_disMap[i]].push_back(i);
    }
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<string> states;
    //states.push_back("1111111");
    /*
    states.push_back("0000000");
    states.push_back("0001010");
    */
    /*
    states.push_back("0100000");
    states.push_back("0000111");
    states.push_back("0000011");
    */
    /*
    states.push_back("1011011");
    states.push_back("1011111");
    states.push_back("1010000");
    states.push_back("1011111");
    states.push_back("1011011");
    string res = s.displayNext(states);
    cout << res << endl;
    */
    //s.process("A-small-attempt1.in", "./res.out");
    s.process( argv[0], argv[1]);
    return 1;
}
