#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#define DEBUG

using namespace std;

class WordVertice{
	public:
		string word;
		vector<int> parent;
		int distance;
		int mark;
		WordVertice(string word, int distance){
			this->word = word;
			this->distance = distance;
			this->mark = 0;
		}
};

class WordGraph{
	public:
		int **matrix;
		WordGraph(string start, string end, unordered_set<string> &dict, vector<WordVertice> *vertices);

		vector<WordVertice>* calShortestPath(vector<WordVertice> *vertices);
		vector<vector<string>>& printPath(vector<WordVertice> *vertices, vector<vector<string>> &path, int current_path, int current_vertice);
		
};

WordGraph::WordGraph(string start, string end, unordered_set<string> &dict, vector<WordVertice> *vertices){
	int v_count = 2 + dict.size();
	this->matrix = (int **)malloc(sizeof(int*)*v_count);
	for(int i = 0; i < v_count; i ++){
		int **sub_matrix = this->matrix + i;
		int *new_matrix  = (int *)malloc( sizeof(int)*v_count );
		*sub_matrix = new_matrix;
		for(int j = 0; j < v_count; j ++)
			*(new_matrix + j) = v_count;
	}
	unordered_set<string>::iterator iter;
	vector<WordVertice>::iterator v_iter = vertices->begin();

	WordVertice *start_wv = new WordVertice(start, 0); 
	vertices->insert( v_iter, *start_wv);
	WordVertice *end_wv = new WordVertice(end, v_count); 
	vertices->insert( vertices->end(), *end_wv);
	v_iter = vertices->begin() + 1;

	string word;
	int same_with_end = v_count;
	int pos = 1;

	for(iter = dict.begin(); iter != dict.end(); ++iter){
		word = *iter;
		WordVertice *mid_wv = new WordVertice(word, v_count);
		v_iter = vertices->insert( v_iter, *mid_wv);
		v_iter ++;
		if( ! word.compare(end_wv->word)){
			same_with_end = pos;
		}
		pos ++;
	}
	v_iter = vertices->begin();
	string s;
	string d;
	int diff = 0;
	int i = 0, j = 0;
	for(i = 0; i < v_count; i ++){
		s = (*vertices)[i].word;
#ifdef DEBUG
		cout << "compare " << s << " with ";
#endif
		for(j = i; j < v_count; j ++){
			d = (*vertices)[j].word;
			diff = 0;
#ifdef DEBUG
			cout << " " << d;
#endif
			for(unsigned int k = 0; k < s.size(); k ++){
				if ( s[k] != d[k])
					diff ++;
			}
			if (diff == 1) {
				this->matrix[i][j] = 1;
				this->matrix[j][i] = 1;
			}
		}
#ifdef DEBUG
		cout << endl;
#endif
	}
	matrix[0][v_count - 1] = v_count;
	matrix[v_count - 1][0] = v_count;
	if(same_with_end != v_count){
		for(i = 0; i < v_count; i ++){
			if(this->matrix[same_with_end][i] == 1){
				this->matrix[i][v_count - 1] = v_count;
			}
		}
	}

}
vector<WordVertice>* WordGraph::calShortestPath(vector<WordVertice> *vertices){
	int v_count = vertices->size();
	vector<WordVertice>::iterator iter = vertices->begin();
	int sp_v_index = v_count;
	int sp_distance = v_count;
	for(int i = 0; i < v_count; i ++){
		sp_v_index = v_count;
		sp_distance = v_count;
		int j = 0;
		for(iter = vertices->begin(); iter != vertices->end(); ++iter, j++){
			//WordVertice *wv = iter !!!! this is wrong! why
			if(iter->mark == 1)
				continue;
			if(iter->distance < sp_distance){
				sp_v_index = j;
				sp_distance = iter->distance;
			}	
		}
		if (sp_v_index == v_count)
			break;
		(*vertices)[sp_v_index].mark = 1;
		for(j = 0; j < v_count; j ++){
			if(this->matrix[sp_v_index][j] == 1){
				if(((*vertices)[sp_v_index].distance + this->matrix[sp_v_index][j]) < (*vertices)[j].distance){
					(*vertices)[j].distance = (*vertices)[sp_v_index].distance + this->matrix[sp_v_index][j];
					(*vertices)[j].parent.clear();
					(*vertices)[j].parent.insert((*vertices)[j].parent.end(), sp_v_index);
				}else if(((*vertices)[sp_v_index].distance + this->matrix[sp_v_index][j]) == (*vertices)[j].distance){
					(*vertices)[j].parent.insert((*vertices)[j].parent.end(), sp_v_index);
				}
			}
		}
	}
	for(int i = 0; i < v_count; i ++){
		free(this->matrix[i]);
	}
	free(this->matrix);
	this->matrix = NULL;
	return vertices;
}

vector<vector<string>>& WordGraph::printPath(vector<WordVertice> *vertices, vector<vector<string>> &path, int current_path, int current_vertice){
	string current = (*vertices)[current_vertice].word;	
	if(!current.compare((*vertices)[0].word)){
		vector<string> &sub_path = path[current_path];
		sub_path.insert(sub_path.begin(), current);
#ifdef DEBUG
		cout << current << endl;
		cout << path.size() << endl;
		for(unsigned int i = 0; i < path.size(); i ++){
			cout << "    " << path[i].size() << endl;
		}
#endif
	}else if((*vertices)[current_vertice].parent.size() == 0){
#ifdef DEBUG
		cout << "no path\n";
#endif
		if(current_path < (int)path.size()){
			path.erase(path.begin() + current_path);
		}
	}else{
		if (path.size() == 0){
			vector<string> *first_path = new vector<string>();
			path.insert(path.begin(), *first_path);
		}
		vector<string> &sub_path = path[current_path];
		sub_path.insert(sub_path.begin(), current);
		vector<int>::iterator p_iter = (*vertices)[current_vertice].parent.begin();
		for(p_iter = (*vertices)[current_vertice].parent.begin(); 
				p_iter != (*vertices)[current_vertice].parent.end(); ++p_iter){
			vector<string> *new_path = new vector<string>();

			vector<string>::iterator record_head;
			for( record_head = sub_path.begin(); record_head != sub_path.end(); record_head ++){
				if (!(record_head->compare(current))){
						break;
				}
			}

			new_path->insert(new_path->begin(), record_head, sub_path.end());

			int current_path_next = current_path, current_vertice_next = *p_iter;

			if(p_iter != (*vertices)[current_vertice].parent.begin()){
				path.insert(path.end(), *new_path);		
				current_path_next = path.size() - 1;
			}
#ifdef DEBUG
			cout << current << " " ;
#endif
			printPath(vertices, path, current_path_next, current_vertice_next); 
		}
		
	}
	return path;	  
}

class Solution{
	public:
		vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict);
};

vector<vector<string>> Solution::findLadders(string start, string end, unordered_set<string> &dict){
	int v_count = 2 + dict.size();	
	vector<WordVertice> *vertices = new vector<WordVertice>;
	WordGraph wg(start, end, dict, vertices);
	wg.calShortestPath(vertices);
	vector<vector<string>> *path = new vector<vector<string>>();
	vector<vector<string>>& path_res = *path;
	path_res = wg.printPath(vertices, path_res, 0, v_count - 1);
	free(vertices);
	return *path;
}


int main(){
	Solution s;
	string start("hit");
	string end("cog");
	unordered_set<string> dict({"hot", "dot", "dog", "lot", "log"});
	//string start("hot");
	//string end("dog");
	//unordered_set<string> dict({"hot", "dog"});
	unordered_set<string>& dict_ref = dict;
	vector<vector<string>> path;
	path = s.findLadders(start, end, dict_ref);
	vector<vector<string>>::iterator iter;
	vector<string>::iterator inner_iter;
	for(iter= path.begin(); iter != path.end(); iter ++){
		vector<string> tmp = *iter;
		for(inner_iter = tmp.begin(); inner_iter != tmp.end(); inner_iter++){
			string word = *inner_iter;
			cout << word << " ";
		}
		cout <<endl;
	}
	return 0;
}
