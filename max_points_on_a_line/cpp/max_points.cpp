/*
 * The cpp implentation of max points on a line
 * Caveat:
 *	boundary condition:
 *		points with same x value;
 *		points with same x an y value;
 *		to be continued 
 *		Its very complicated
 */
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <math.h>
#include <stdlib.h>
#define DEBUG
using namespace std;

struct Point {
	int x;
	int y;
	Point(): x(0), y(0){}
	Point(int a, int b): x(a), y(b){}
};
typedef struct Point Point;
struct Node {
	Point p;
	int num;
	Node(): num(0){}
	Node():(int a, int b, int c): num(a){
		p.x = a;
		p.y = b;
	}
};
typedef struct Node Node;

class Solution{
	public:
		int maxPoints(vector<Point> &points);
		int maxPointsErr(vector<Point> &points);
};
int Solution::maxPoints(vector<Point> &points){
	int max = 0;
	//in these special cases, we can get results immediately
	int size = points.size();
	if ( size == 0 ) return 0;
	if ( size == 1 ) return 1;
	if ( size == 2 ) return 2;

	
	map<int, map<int, Node*> > p_map;
	list<Node*> p_list;

	Point first, second;
	for(int i = 0; i < size; i ++){
		first = points[i];
		for(int j = 0; j < size; j ++){
			second = points[j];
			if( (first.x == second.x) && (first.y == second.y) )
		}
	}
	size = sim_p.size();	
	int inc = 0;
	for ( map<int, map<int, int> >::itertor f_iter = sim_p.begin();
			f_iter != sim_p.end(); f_iter++) {
		inc = (f_iter->second)
		for ( map<int, map<int, int> >::iterator s_iter = sim_p.begin();
				s_iter != sim_p.end(); s_iter ++) {
			for ( map<int, map<int, int> >::itertor t_iter = sim_p.begin();
					t_iter != sim_p.end(); t_iter ++) {

			}
			max = (max>=inc)?max:inc;
		}
	}

	return max;
}
//error
//the double accrracy affects the correctness of hashmap
int Solution::maxPointsErr(vector<Point> &points){
	int size = points.size();
	if ( size == 0 ) return 0;
	if ( size == 1 ) return 1;
	if ( size == 2 ) return 2;
	// function  y = kx + b
	double k = 0, b = 0;
	Point p,q;

	map<double, int> b_map;
	map<double, map<double, int> > k_map;

	map<int, map<int, int> > x_map;
	map<int, int> y_map;

	map<int, bool> repeated_flag;
	for (int i = 0; i < size; i ++){
		p = points[i];
		if(repeated_flag[i])
		   	continue;
		for ( int j = 0; j < size; j ++) {
			if ( i == j )
				continue;
			q = points[j];
			if ( (p.x == q.x) && (p.y == q.y) ) {
				repeated_flag[j] = true;
			}
		}
	}

	for (int i = 0; i < size; i ++) {
		p = points[i];
		if(repeated_flag[i]){
			x_map[p.x][p.y] += x_map[p.x][p.y];
		   	continue;
		}
		for ( int j = (i + 1); j < size; j ++ ) {
			q = points[j];
#ifdef DEBUG
			cout << "p: x and y : " << p.x << " " << p.y << endl;
			cout << "q: x and y : " << q.x << " " << q.y << endl;
#endif
			if (p.x == q.x) {
				k = numeric_limits<int>::max();
				b = p.x;
				if ( p.y == q.y ) {
					map<int, int> &tmp_y_map  = x_map[p.x];
					tmp_y_map[p.y] += 1;
#ifdef DEBUG
					cout << "same count: " << tmp_y_map[p.y] << endl;
#endif
					continue;
				}
			} else {
				k = (double)(p.y - q.y)/(double)(p.x - q.x);
				b = ((int)((double)(p.y - k*p.x)*1000000 + 0.5)/1000000.0);
				k = ((int)( k * 1000000 + 0.5)/ 1000000.0);
				
			}
#ifdef DEBUG
			cout << "cal k and b : " << k << " " << b << endl;
#endif
			map<double, int> &tmp =  k_map[k];
#ifdef DEBUG
			cout << "show the original count: " << tmp[b] << endl;
#endif
			if ( b != numeric_limits<int>::max() ) tmp[b] += 1;
#ifdef DEBUG
			cout << "show the count: " << tmp[b] << endl;
#endif
		}
	}
	int max_1 = 0;
	for ( map<double, map<double, int> >::iterator k_iter = k_map.begin(); 
			k_iter != k_map.end(); ++k_iter ) {
		b_map = k_iter->second;
		for ( map<double, int>::iterator b_iter = b_map.begin(); 
				b_iter != b_map.end(); b_iter ++ ) {
			if ( max_1 < b_iter->second )	{
				k = k_iter->first;
				b = b_iter->first;
				max_1 = b_iter->second;
			}
		}
	}

#ifdef DEBUG
	cout << "max_1: " << max_1 << endl;
#endif
	max_1 = (sqrt(1+4*max_1) + 1)/2;
#ifdef DEBUG
	cout << "max_1: " << max_1 << endl;
#endif

	int max_2 = 0;
	int tmp = 0;
	for ( map<int, map<int, int> >::iterator x_iter = x_map.begin(); 
			x_iter != x_map.end(); ++x_iter ) {
		y_map = x_iter->second;
		for ( map<int, int>::iterator y_iter = y_map.begin(); 
				y_iter != y_map.end(); y_iter ++ ) {
			p.x = x_iter->first;
			p.y = y_iter->first;
			tmp = y_iter->second;
			tmp = (sqrt(1+4*tmp) + 1)/2;
#ifdef DEBUG
			cout << "x: " << p.x << endl;
			cout << "y: " << p.y << endl;
			cout << "k: " << k << endl;
			cout << "b: " << b << endl;
			cout << "tmp: " << tmp << endl;
#endif
			if ( ( (k == numeric_limits<int>::max()) && (b == p.x) ) 
					|| (fabs(p.y - (k*p.x + b)) < 0.003 )) {
				max_1 += tmp - 1;
				continue;
			} 
			if ( max_2 < tmp ) {
				max_2 = tmp;
			}
		}
	}
	max_2 += 1;
#ifdef DEBUG
	cout << "max_1: " << max_1 << endl;
	cout << "max_2: " << max_2 << endl;
#endif
	
	return (max_1 > max_2)?max_1:max_2 ;
}

int main(int argc, char *argv[]){
	Solution s;
	int max;
	vector<Point> vp;
	vector<Point> &points = vp;
	
	max = s.maxPoints(points);
	cout << "A null point vector:" << max << endl;
	cout << "-------------------------" << endl;
	
	//Point p(0, 0);
	//Point q(-1, -1);
	//Point r(2, 2);
	Point p(1, 1);
	Point q(1, 1);
	Point r(2, 2);
	Point o(2, 2);
	//Point o(-6, -1);
	vp.insert( vp.end(), p);
	vp.insert( vp.end(), q);
	vp.insert( vp.end(), r);
	vp.insert( vp.end(), o);
	//vp.insert( vp.end(), o);
	max = s.maxPoints(points);
	cout << "res: " << max << endl;
	cout << "-------------------------" << endl;
/*
	Point a(1, 2);
	Point b(2, 2);
	Point c(2, 4);
	Point d(3, 4);
	Point e(4, 6);
	vp.clear();
	vp.insert( vp.end(), a);
	vp.insert( vp.end(), b);
	vp.insert( vp.end(), c);
	vp.insert( vp.end(), d);
	vp.insert( vp.end(), e);
	max = s.maxPoints(points);
	cout << "A null point vector:" << max << endl;
	cout << "-------------------------" << endl;
*/
	return 1;
}
