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

const int INF = INT_MAX;
const ld EPS = 1e-8;
const ld PI = 3.14159265358979323;
const int M = INT_MAX;
const int MAXN = 2 * 1e5;
const ll NEUTRAL = 0;

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

ll t[MAXN * 4], a[MAXN], t2[4 * MAXN];

void push(int v, int l, int r){
	if (t2[v] != -INF){
		t[v] = t2[v] * (r - l);
		if (v * 2 < 4 * MAXN)
			t2[v * 2] = t2[v];
		if (v * 2 + 1 < 4 * MAXN)
			t2[v * 2 + 1] = t2[v];
		t2[v] = -INF;
	}
}

void relax(int v, int l, int r, int m){
	push(v * 2, l, m);
	push(v * 2 + 1, m, r);
	t[v] = t[v * 2] + t[v * 2 + 1];
}

void build(int v, int l, int r){
	t2[v] = -INF;
	if (r - l == 1)
		t[v] = a[l];
	else{
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		relax(v, l, r, m);
	}
}

ll function_sum(int v, int l, int r, int L, int R){
	push(v, l, r);
	if (R <= l || r <= L)
		return NEUTRAL;
	if (L <= l && r <= R)
		return t[v];
	int m = (l + r) / 2;
	return function_sum(v * 2, l, m, L, R) + function_sum(v * 2 + 1, m, r, L, R);

}		

void change(int v, int l, int r, int position, int value){
	push(v, l, r);
	if (l == r && l == position)
		t[v] = value;
	else{
		int m = (l + r) / 2;
		if (position < m)
			change(v * 2, l, m, position, value);
		else
			change(v * 2 + 1, m, r, position, value);
		relax(v, l, r, m);
	}
}

void update(int v, int l, int r, int L, int R, int x)
{
    push(v, l, r);
    if (R <= l || r <= L)
        return;
    if (L <= l && r <= R){
        t2[v] = x;
    }
    else{
        //push(v, tl, tr);
        int m = (l + r) / 2;
        update(v * 2, l, m, L, R, x);
        update(v * 2 + 1, m, r, L, R, x);
        relax(v, l, r, m);
    }
}

signed main()
{
    #ifdef _LOCAL
    	clock_t Tsart = clock();
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
    fast();

    int n;
    cin >> n;
    int q;
    cin >> q;
   /* for(int i = 0; i < n; i++)
    	cin >> a[i];*/

   	build(1, 0, n);
    while(q--){
    	char c;
    	cin >> c;
    	if (c == 'A'){
    		int l, r, x;
    		cin >> l >> r >> x;
    		/*watch(l);
    		watch(r);*/
    		update(1, 0, n, l - 1, r, x);
    	}
    	else{
    		int l, r;
    		cin >> l >> r;
    		cout << function_sum(1, 0, n, l - 1, r) << '\n';
    	}
    }

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
