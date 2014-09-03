#include <iostream>
#include <unordered_set>
#include <stack>
#include <map>
#include <vector>
#define DEBUG
using namespace std;

class Solution {
	public:
		bool wordBreak(string s, unordered_set<string> &dict);
};

bool Solution::wordBreak(string s, unordered_set<string> &dict) {
	if (dict.size() == 0) return false;
	if ( (s == "")) {
		if ( dict.find("") != dict.end()) return true;
		else return false;
	}
	stack<int> s_index;
	s_index.push(0);
	int start = 0;
	map<char, vector<string> > dict_map; //classified dict
	dict.erase("");
	unordered_set<string>::iterator d_iter = dict.begin();
	vector<string> tmp;
	for ( ; d_iter != dict.end(); d_iter ++) {
#ifdef DEBUG
		if ( *d_iter == "fohhemkka") {
			cout << *d_iter << endl;
		}
#endif
		tmp = dict_map[(*d_iter)[0]];
		// redundant flag
		int flag = 0;
		for ( int i = 0; i < tmp.size(); i ++) {
			int j = 0; 
			if (( d_iter->size()%(tmp[i].size()) ) != 0) continue;
			while ( j != d_iter->size()) {
				if ( d_iter->substr(j, tmp[i].size()) != tmp[i] ) {
					break;
				} else {
					j = j + tmp[i].size();
				}
			}
			if ( j == d_iter->size()) {
				flag = 1;
				break;
			}
		}
		if (flag) continue;
		if ( tmp.size() == 0 ) {
			dict_map[(*d_iter)[0]].push_back( *d_iter);
			continue;
		}
		vector<string>::iterator new_iter;
		int o_size = dict_map[(*d_iter)[0]].size();
		vector<string>::iterator v_iter = dict_map[(*d_iter)[0]].begin();
		for ( ;v_iter != dict_map[(*d_iter)[0]].end(); v_iter ++) {
			if ( v_iter->size() >= d_iter->size()) {
				new_iter = dict_map[(*d_iter)[0]].insert( v_iter, *d_iter);
				break;
			} 
		}
		if (dict_map[(*d_iter)[0]].size() == o_size )
			new_iter = dict_map[(*d_iter)[0]].insert( dict_map[(*d_iter)[0]].end(), *d_iter);

		tmp = dict_map[(*d_iter)[0]];
		int new_index = 0;
		int count = 0;
		for (int i = 0; i < tmp.size(); i ++) {
			if (tmp[i] == *new_iter) new_index = i;
			if (tmp[i].size() <= new_iter->size()) continue;
			if ( (tmp[i].size() % tmp[new_index].size()) != 0) continue;
			int j = 0;
			while ( j != tmp[i].size()) {
				if ( tmp[i].substr(j, tmp[new_index].size()) != tmp[new_index] ) {
					break;
				} else {
					j = j + tmp[new_index].size();
				}
			}
			if ( j == tmp[i].size()) {
#ifdef DEBUG
				if ( tmp[i] == "fohhemkka") 
					cout << "wanna to remove !!!!!" << endl;
#endif
				dict_map[(*d_iter)[0]].erase(dict_map[(*d_iter)[0]].begin() + i - count);
				count ++;
			}
		}
	}
	vector<string> d_list; // dict list stared with specified char
	string d_word;
	while( !s_index.empty()) {
		start = s_index.top();
		s_index.pop();
		if (start == s.size()) return true;
		d_list = dict_map[s[start]];	
		for ( int i = 0; i < d_list.size(); i ++ ) {
			d_word = d_list[i];
			if (s.substr(start, d_word.size()) == d_word) s_index.push( start+d_word.size() );
		}
	}
	
	return false;
}
int main(int argc, char *argv[]) {
	Solution s;
	string str("a");
	string dict_s[] = {"a"};
	unordered_set<string> dict;
	for ( int i = 0; i < 1; i ++)
		dict.insert(dict_s[i]);
	cout << s.wordBreak(str, dict) << endl;

	string dict_si[] = {"leet"};
	unordered_set<string> dicti;
	for ( int i = 0; i < 1; i ++)
		dicti.insert(dict_si[i]);
	cout << s.wordBreak(str, dicti) << endl;

	string str1("catsanddog");
	string dict_sii[] = {"cat", "cats", "and", "sand", "dog"};
	unordered_set<string> dictii;
	for ( int i = 0; i < 5; i ++)
		dictii.insert(dict_sii[i]);
	cout << s.wordBreak(str1, dictii) << endl;

	string str2("");
	unordered_set<string> dictiii;
	dictiii.insert("");
	cout << s.wordBreak(str2, dictiii) << endl;

	// coner cases
	string str3("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
	string dict_siiii[] = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
	unordered_set<string> dictiiii;
	for ( int i = 0; i < 5; i ++)
		dictiiii.insert(dict_siiii[i]);
	cout << s.wordBreak(str3, dictiiii) << endl;

	string str4("fohhemkkaecojceoaejkkoedkofhmohkcjmkggcmnami");
	string dict_siiiii[] = {"kfomka","hecagbngambii","anobmnikj","c","nnkmfelneemfgcl","ah","bgomgohl","lcbjbg","ebjfoiddndih","hjknoamjbfhckb","eioldlijmmla","nbekmcnakif","fgahmihodolmhbi","gnjfe","hk","b","jbfgm","ecojceoaejkkoed","cemodhmbcmgl","j","gdcnjj","kolaijoicbc","liibjjcini","lmbenj","eklingemgdjncaa","m","hkh","fblb","fk","nnfkfanaga","eldjml","iejn","gbmjfdooeeko","jafogijka","ngnfggojmhclkjd","bfagnfclg","imkeobcdidiifbm","ogeo","gicjog","cjnibenelm","ogoloc","edciifkaff","kbeeg","nebn","jdd","aeojhclmdn","dilbhl","dkk","bgmck","ohgkefkadonafg","labem","fheoglj","gkcanacfjfhogjc","eglkcddd","lelelihakeh","hhjijfiodfi","enehbibnhfjd","gkm","ggj","ag","hhhjogk","lllicdhihn","goakjjnk","lhbn","fhheedadamlnedh","bin","cl","ggjljjjf","fdcdaobhlhgj","nijlf","i","gaemagobjfc","dg","g","jhlelodgeekj","hcimohlni","fdoiohikhacgb","k","doiaigclm","bdfaoncbhfkdbjd","f","jaikbciac","cjgadmfoodmba","molokllh","gfkngeebnggo","lahd","n","ehfngoc","lejfcee","kofhmoh","cgda","de","kljnicikjeh","edomdbibhif","jehdkgmmofihdi","hifcjkloebel","gcghgbemjege","kobhhefbbb","aaikgaolhllhlm","akg","kmmikgkhnn","dnamfhaf","mjhj","ifadcgmgjaa","acnjehgkflgkd","bjj","maihjn","ojakklhl","ign","jhd","kndkhbebgh","amljjfeahcdlfdg","fnboolobch","gcclgcoaojc","kfokbbkllmcd","fec","dljma","noa","cfjie","fohhemkka","bfaldajf","nbk","kmbnjoalnhki","ccieabbnlhbjmj","nmacelialookal","hdlefnbmgklo","bfbblofk","doohocnadd","klmed","e","hkkcmbljlojkghm","jjiadlgf","ogadjhambjikce","bglghjndlk","gackokkbhj","oofohdogb","leiolllnjj","edekdnibja","gjhglilocif","ccfnfjalchc","gl","ihee","cfgccdmecem","mdmcdgjelhgk","laboglchdhbk","ajmiim","cebhalkngloae","hgohednmkahdi","ddiecjnkmgbbei","ajaengmcdlbk","kgg","ndchkjdn","heklaamafiomea","ehg","imelcifnhkae","hcgadilb","elndjcodnhcc","nkjd","gjnfkogkjeobo","eolega","lm","jddfkfbbbhia","cddmfeckheeo","bfnmaalmjdb","fbcg","ko","mojfj","kk","bbljjnnikdhg","l","calbc","mkekn","ejlhdk","hkebdiebecf","emhelbbda","mlba","ckjmih","odfacclfl","lgfjjbgookmnoe","begnkogf","gakojeblk","bfflcmdko","cfdclljcg","ho","fo","acmi","oemknmffgcio","mlkhk","kfhkndmdojhidg","ckfcibmnikn","dgoecamdliaeeoa","ocealkbbec","kbmmihb","ncikad","hi","nccjbnldneijc","hgiccigeehmdl","dlfmjhmioa","kmff","gfhkd","okiamg","ekdbamm","fc","neg","cfmo","ccgahikbbl","khhoc","elbg","cbghbacjbfm","jkagbmfgemjfg","ijceidhhajmja","imibemhdg","ja","idkfd","ndogdkjjkf","fhic","ooajkki","fdnjhh","ba","jdlnidngkfffbmi","jddjfnnjoidcnm","kghljjikbacd","idllbbn","d","mgkajbnjedeiee","fbllleanknmoomb","lom","kofjmmjm","mcdlbglonin","gcnboanh","fggii","fdkbmic","bbiln","cdjcjhonjgiagkb","kooenbeoongcle","cecnlfbaanckdkj","fejlmog","fanekdneoaammb","maojbcegdamn","bcmanmjdeabdo","amloj","adgoej","jh","fhf","cogdljlgek","o","joeiajlioggj","oncal","lbgg","elainnbffk","hbdi","femcanllndoh","ke","hmib","nagfahhljh","ibifdlfeechcbal","knec","oegfcghlgalcnno","abiefmjldmln","mlfglgni","jkofhjeb","ifjbneblfldjel","nahhcimkjhjgb","cdgkbn","nnklfbeecgedie","gmllmjbodhgllc","hogollongjo","fmoinacebll","fkngbganmh","jgdblmhlmfij","fkkdjknahamcfb","aieakdokibj","hddlcdiailhd","iajhmg","jenocgo","embdib","dghbmljjogka","bahcggjgmlf","fb","jldkcfom","mfi","kdkke","odhbl","jin","kcjmkggcmnami","kofig","bid","ohnohi","fcbojdgoaoa","dj","ifkbmbod","dhdedohlghk","nmkeakohicfdjf","ahbifnnoaldgbj","egldeibiinoac","iehfhjjjmil","bmeimi","ombngooicknel","lfdkngobmik","ifjcjkfnmgjcnmi","fmf","aoeaa","an","ffgddcjblehhggo","hijfdcchdilcl","hacbaamkhblnkk","najefebghcbkjfl","hcnnlogjfmmjcma","njgcogemlnohl","ihejh","ej","ofn","ggcklj","omah","hg","obk","giig","cklna","lihaiollfnem","ionlnlhjckf","cfdlijnmgjoebl","dloehimen","acggkacahfhkdne","iecd","gn","odgbnalk","ahfhcd","dghlag","bchfe","dldblmnbifnmlo","cffhbijal","dbddifnojfibha","mhh","cjjol","fed","bhcnf","ciiibbedklnnk","ikniooicmm","ejf","ammeennkcdgbjco","jmhmd","cek","bjbhcmda","kfjmhbf","chjmmnea","ifccifn","naedmco","iohchafbega","kjejfhbco","anlhhhhg"};
	unordered_set<string> dictiiiii;
	for ( int i = 0; i < sizeof(dict_siiiii)/sizeof(string); i ++)
		dictiiiii.insert(dict_siiiii[i]);
	cout << s.wordBreak(str4, dictiiiii) << endl;
	return 1;
}
