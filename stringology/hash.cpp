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
 
const int INF = 1e9+7;
const ld EPS = 1e-8;
const ld PI = 3.14159265358979323;
//const int M = 1e9+7;
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

const ll P = 197, M = 1e9 + 7;
ll h[MAXN], p[MAXN];
string s;

ll add (ll a, ll b) {
	if (a + b >= M)
		return a + b - M;
	else
		return a + b;
}

ll sub (ll a, ll b) {
	if (a - b < 0)
		return a - b + M;
	else
		return a - b;
}

ll mul (ll a, ll b) {
	return (a * b) % M;
}

void hash1 (string s) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++)
		h[i] = add(mul(h[i - 1], P), s[i]);
}


void iniz (int n) {
	p[0] = 1;
	for (int i = 1; i < n; i++)
		p[i] = mul(p[i - 1], P);
}

ll subhash (ll l, ll r) {
	ll k;
	if (l == 0)
		k = 0;
	else
		k = h[l - 1];
	
	return sub(h[r], mul(k, p[r - l + 1]));
}

signed main()
{
    #ifdef _LOCAL
    	clock_t Tsart = clock();
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
    fast();
 
 	cin >> s;
 	int n = s.size();
 	iniz(MAXN);
 	hash1(s);
 	

 	
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
