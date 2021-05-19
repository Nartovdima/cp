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
 
const int MAX_MEM = 1e8; 
int mpos = 0; 
char mem[MAX_MEM]; 
#define fast(){ \
    ios_base::sync_with_stdio(0); \
    cin.tie(0); \
}
inline void * operator new ( size_t n ) { 
    assert((mpos += n) <= MAX_MEM); 
    return (void *)(mem + mpos - n); 
} 
inline void operator delete (void *) noexcept { } 

graph g;
bool used[MAXN];
int n, s;

void dfs (int v) {
	used[v] = 1;
	for (auto it : g[v])
		if (!used[it])
			dfs(it);
}

signed main() {
    #ifdef _LOCAL
    	clock_t Tsart = clock();
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
    fast();
 	
 	cin >> n >> s;
 	g.resize(n);
 	for (int i = 0; i < n; i++)
 		for (int j = 0; j < n; j++) {
 			int x;
 			cin >> x;
 			if (x)
 				g[i].pb(j);
 		}
 	
 	for (int i = 0; i < n; i++)
 		if (!used[i])
 			dfs(i);

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
