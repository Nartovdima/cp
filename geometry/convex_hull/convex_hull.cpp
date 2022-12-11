#include <unordered_set>
#include <unordered_map>
//#include <ext/rope>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <bitset>
#include <cstdio>
#include <stack>
#include <cmath>
#include <ctime>
#include <queue>
#include <map>
#include <set>
//using namespace __gnu_cxx;
using namespace std;
 
/*#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")*/
 
typedef long long ll;   
typedef long double ld;
typedef pair <int, int> ii;
typedef pair <ll, ll> dl;
typedef vector <vector <int> > graph;
 
#define pb push_back
#define eb emplace_back 
#define ff first
#define ss second
#define watch(x) cerr << (#x) << "=" << x << '\n'
#define ptree_node tree_node*
 
const int INF = 1e9;
const ld EPS = 1e-8;
const ld PI = 3.14159265358979323;
const int M = 1e9;
const int MAXN = 2 * 1e5;
 
/*const int MAX_MEM = 1e8; 
int mpos = 0; 
char mem[MAX_MEM];*/ 
#define fast(){ \
    ios_base::sync_with_stdio(0); \
    cin.tie(0); \
}
/*inline void * operator new ( size_t n ) { 
    assert((mpos += n) <= MAX_MEM); 
    return (void *)(mem + mpos - n); 
} 
inline void operator delete (void *) noexcept { }*/ 

struct point {
	int x, y;	
};

point p[1005];
point ideal;
vector <point> convex_hull;

point get_vector (point a, point b) {
	return {b.x - a.x, b.y - a.y};
}

int dot_product (point a, point b) {
	return a.x * b.x + a.y * b.y;
}

int cross_product (point a, point b) {
	return a.x * b.y - a.y * b.x;
}

ld vector_lenght(point a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

int vector_lenght_cmp(point a) {
	return a.x * a.x + a.y * a.y;
}

bool cmp (point a, point b) {
	ll g = cross_product(get_vector(a, p[0]), get_vector(b, p[0]));
	if (g == 0) {
		return vector_lenght_cmp(get_vector(a, p[0])) < vector_lenght_cmp(get_vector(b, p[0]));
	}
	return g > (ll)0;
}

bool check (point a, point b, point c) {
	if (cross_product(get_vector(a, b), get_vector(a, c)) > 0)
		return 0;
	else
		return 1;
}

signed main() {
    #ifdef _LOCAL
    	clock_t Tsart = clock();
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
    fast();
 	
 	int n;
 	cin >> n;
 	point mn = {-INF, INF};
 	int id;
 	for (int i = 0; i < n; i++) {
 		int a, b;
 		cin >> a >> b;
 		p[i].x = a;
 		p[i].y = b;
 		if (mn.y > p[i].y) { 
 			mn = p[i];
 			id = i;
 		}
 		else if (mn.y == p[i].y && p[i].x < mn.x) { 
 			mn = p[i];
 			id = i;
 		}
 	}
	
 	swap(p[0], p[id]);
 	ideal = {-INF, p[0].y};
 	sort(p + 1, p + n, cmp);
 	
 	convex_hull.pb(p[0]);
 	convex_hull.pb(p[1]);

 	for (int i = 2; i < n; i++) {
 		while (check(convex_hull[convex_hull.size() - 2], convex_hull[convex_hull.size() - 1], p[i]) && convex_hull.size() > 1)
 			convex_hull.erase((convex_hull.end() - 1));
 		convex_hull.pb(p[i]);
 	}

 	ld s = 0;
 	for (int i = 1; i < convex_hull.size(); i++) {
 		s += vector_lenght(get_vector(convex_hull[i - 1], convex_hull[i]));
 	}
 	
 	s += vector_lenght(get_vector(convex_hull[convex_hull.size() - 1], convex_hull[0]));
 	cout << fixed << setprecision(1) << s << '\n';

	#ifdef _LOCAL
		cerr << "Runtime: " << (ld)(clock() - Tsart) / CLOCKS_PER_SEC << '\n';
	#endif		
    return 0;
}
 
/*     .^----^.
      (= o  O =)
       (___V__)
        _|==|_
   ___/' |--| |
  / ,._| |  | '
 | \__ |__}-|__}
  \___)`*/
