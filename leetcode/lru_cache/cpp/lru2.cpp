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
	public:
		CacheUnit *next_;
		CacheUnit *prev_;
		CacheUnit():key_(0),value_(0){}
		void set(int key, int value){
			key_ = key;
			value_ = value;
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
			return value_;
		}
		void sentinelInit(){
			next_ = this;
			prev_ = this;
		}
		// insert after this element
		// return the inserted pointer 
		CacheUnit* insert(int key, int value) {
			CacheUnit *cu = new CacheUnit();
			cu->set(key, value);
			cu->next_ = next_;
			cu->prev_ = this;
			next_->prev_ = cu;
			next_ = cu;
			return next_;
		}
		CacheUnit* insert(CacheUnit *pro) {
			CacheUnit *cu = pro;
			cu->next_ = next_;
			cu->prev_ = this;
			next_->prev_ = cu;
			next_ = cu;
			return next_;
		}
		// replace before this element
		// return the setinel
		CacheUnit* replace(int key, int value) {
			set(key, value);
			return prev_;
		}
};

class LRUCache{
	private:
		int capacity_;
	    int length_; 	
		//sentinel
		CacheUnit *cache_list_;
		map<int, CacheUnit*> cache_map_;
		void insert(int key, int value);
		void replace(int key, int value);
		void promote(CacheUnit *pro);
	public:
	    LRUCache(int capacity):capacity_(capacity),length_(0){ 
			if (capacity_>0){
				cache_list_ = new CacheUnit();
				cache_list_->sentinelInit();
			}
		}
		int getCapacity() {
			return capacity_;
		}
		int getLength() {
			return length_;
		}
		CacheUnit* getCacheTable() {
			return cache_list_;
		}
	    int get(int key);
	   	void set(int key, int value); 
};

int LRUCache::get(int key) {
	if (!length_) return -1;
	map<int, CacheUnit*>::iterator i_res = cache_map_.find(key);
	if (i_res == cache_map_.end()) return -1;
	// else
	CacheUnit* p_res = i_res->second;	
	promote(p_res);
	return p_res->getValue();
}
void LRUCache::insert (int key, int value) {
	CacheUnit *inserted = cache_list_->insert(key, value);
	cache_map_[inserted->getKey()] = inserted;
	length_ ++;
}
void LRUCache::replace (int key, int value) {
	cache_list_ = cache_list_->replace(key, value);
	cache_map_.erase(cache_list_->getKey());
	cache_map_[cache_list_->next_->getKey()] = cache_list_->next_;
}
void LRUCache::promote (CacheUnit *pro) {
	CacheUnit *tmp = pro->prev_;
	tmp->next_ = pro->next_;
	pro->next_->prev_ = tmp;
	cache_list_->insert(pro);
}
void LRUCache::set(int key, int value) {
	map<int, CacheUnit*>::iterator i_res = cache_map_.find(key);
	if (i_res == cache_map_.end()) {
		if (length_ < capacity_) insert(key, value);
		else replace(key, value);
	} else {
		CacheUnit* p_res = i_res->second;	
		p_res->setValue(value);
		promote(p_res);
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
		cout << "set key :" << key << " set value: "  << value << endl;
		if (gets[i] != -1) {
			int res = lc.get(gets[i]);
			cout << "get result---------------: " << res << endl;
		}
		length = lc.getLength();
		CacheUnit *init = lc.getCacheTable()->next_;
		for (int j = 0; j < length; j ++) {
			cout << init->getKey() << "   " << init->getValue() << endl;
			init = init->next_;
		}
		cout << endl;
		
	}	
	int length = lc.getLength();
	cout << "The length is : " << length << endl;
	return 1;
}
