#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <stdlib.h> //rand
#define DEBUG 
using namespace std;

class CacheUnit{
	private:
		int key_;
		int value_;
		int valid_;
		int counter_;
	public:
		CacheUnit():key_(0),value_(0),valid_(0),counter_(1){}
		void set(int key, int value){
			key_ = key;
			value_ = value;
			valid_ = 1;
		}
		void setValue(int value) {
			value_ = value;
		}
		int getKey() {
			return key_;
		}
		int identifyKey(int key) {
			//if (this.valid && (key == this.key)) return 1;
			if (key == key_) return 1;
			return 0;
		}
		int getValue(){
			if(!valid_) return -1;
			return value_;
		}
		int getCounter(){
			if(!valid_) return -1;
			return counter_;
		}
		int getValid(){
			return valid_;
		}
		int getValid(int val) {
			if ((val == -1) && (!valid_))
				return 0;
			return 1;
		}
		void setValid(int valid){
			valid_ = valid;
			if(!valid_)	counter_ = 0;
		}
		void increaseCounter(){
			counter_ ++;
		}
		void initCounter(){
			counter_ = 1;
		}
};

class LRUCache{
	private:
		int capacity_;
	    int length_; 	
		//minimum stack
		vector<CacheUnit> cache_table_;
		map<int, int> cache_map_;
		void heapify(int i);
		void insert(int key, int value);
		void increase(int i);
		void decrease(int i);
	public:
	    LRUCache(int capacity):capacity_(capacity),length_(0){ }
		int getCapacity() {
			return capacity_;
		}
		int getLength() {
			return length_;
		}
		vector<CacheUnit> getCacheTable() {
			return cache_table_;
		}
	    int get(int key);
	   	void set(int key, int value); 
};
/*
 * increase a counter by 1
 */
void LRUCache::increase(int i) {
	cache_table_[i].increaseCounter();
	heapify(i);
}
/*
 * default to init a infinite counter to 1
 */
void LRUCache::decrease(int i) {
	int index = i;
	int parent = (index-1) >> 1;	
	CacheUnit tmp_cu;
	while((parent >= 0) && (cache_table_[parent].getCounter() > cache_table_[index].getCounter())) {
		tmp_cu = cache_table_[index];	
		cache_table_[index] = cache_table_[parent];
		cache_table_[parent] = tmp_cu;
		cache_map_[cache_table_[index].getKey()] = index;
		cache_map_[cache_table_[parent].getKey()] = parent;
		index = parent;
		parent = (index-1) >> 1;
	}
}
void LRUCache::insert(int key, int value) {
	if (length_ == capacity_) return;
	length_ ++;
	CacheUnit cu;
	cu.set(key, value);
	cache_table_.push_back(cu);
	cache_map_[key] = length_ - 1;
	decrease(length_ - 1);
}
/*
 * keep the validation of the cache_table as a minimum heap
 */
void LRUCache::heapify(int i) {
	// exit entry of recursion
	if (i == length_) return;
	// init some flags
	int min = i; // index of min counter of cache unit 
	int min_c = cache_table_[i].getCounter(); // counter of the min element
	int l_int = (i>>1) + 1;			// left child
	int flag = (l_int<=(length_-1))?1:0; // flag of child existense
	if (flag) { // handle the left child
		if(cache_table_[l_int].getCounter() <= min_c){
			min = l_int;	
			min_c = cache_table_[l_int].getCounter(); 
		}	
		int r_int = (i+1) >> 1;			// right child
		flag = (r_int<=length_-1)?1:0;
		if (flag) { // handle the right child
			if(cache_table_[r_int].getCounter() <= min_c){
				min = r_int;	
				min_c = cache_table_[r_int].getCounter(); 
			}	
		}
	}
	// swap the min and i
	if (min != i) {
		CacheUnit tmp = cache_table_[min];							
		cache_table_[min] = cache_table_[i];
		cache_table_[i] = tmp;
		cache_map_[cache_table_[min].getKey()] = min;
		cache_map_[cache_table_[i].getKey()] = i;
		// recursion
		heapify(min);	
	} 
	cache_table_[min].initCounter();
	return;
}
/*
 * get the value by key
 */
int LRUCache::get(int key) {
	if (!length_) return -1;
	map<int, int>::iterator it;
	it = cache_map_.find(key);
	if (it == cache_map_.end()) return -1;
	else {
		int index = it->second;
		int res = cache_table_[index].getValue();
#ifdef DEBUG
		cout << "GET BEGIN----------------------"  << endl;
		for (int j = 0; j < length_; j ++) {
			cout << cache_table_[j].getCounter() << "    " << cache_table_[j].getKey() << "    " << cache_table_[j].getValue() << endl;
		}
		cout << endl;
#endif 
		increase(index);
#ifdef DEBUG
		for (int j = 0; j < length_; j ++) {
			cout << cache_table_[j].getCounter() << "    " << cache_table_[j].getKey() << "    " << cache_table_[j].getValue() << endl;
		}
		cout << endl;
		cout << "GET END----------------------"  << endl;
#endif
		return res;
	}
}

void LRUCache::set(int key, int value) {
	int presence = -1;
	if (!length_) presence = -1;
	map<int, int>::iterator it;
	it = cache_map_.find(key);
	if (it == cache_map_.end()) {}
	else {
		int index = it->second;
		cache_table_[index].setValue(value);
		cache_table_[index].initCounter();
		heapify(index);
		return;
	}
	if (length_ == capacity_) {
		CacheUnit cu;
		cu.set(key, value);
		cache_map_.erase(cache_table_[0].getKey());
		cache_table_[0] = cu;
		cache_map_[key] = 0;
		return;
	} else {
		insert(key, value);
	}
}

int main(int argc, char *argv[]){
	LRUCache lc(2);
	cout << "the capacity is :" << lc.getCapacity() << endl;
	int keys[] = {2, 2, 1, 4};
	int vals[] = {1, 2, 1, 1};
	int gets[] = {-1, 2, -1, 2};
	for (int i = 0; i < 4; i ++) {
		//int key = rand()%100;
		//int value = rand()%100;
		int key = keys[i];
		int value = vals[i];
		int length = lc.getLength();
		lc.set(key, value);
		cout << "SET BEGIN--------------------"  << endl;
		cout << "set key :" << key << " set value: "  << value << endl;
		if (gets[i] != -1) {
			int res = lc.get(gets[i]);
			cout << "get result---------------: " << res << endl;
		}
		length = lc.getLength();
		/*
		for (int j = 0; j < length; j ++) {
			cout << lc.getCacheTable()[j].getCounter() << "   " << lc.getCacheTable()[j].getKey() << endl;
		}
		*/
		cout << "SET END--------------------" << endl;
	}	
	int length = lc.getLength();
	cout << "The length is : " << length << endl;
	return 1;
}
