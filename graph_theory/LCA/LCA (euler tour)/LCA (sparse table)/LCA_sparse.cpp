#include <unordered_set>
#include <unordered_map>
//#include <ext/rope>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <chrono>
#include <string>
#include <vector>
#include <bitset>
#include <cstdio>
#include <random>
#include <stack>
#include <cmath>
#include <queue>
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
#define show(x) cerr << (#x) << "=" << x << '\n'
#define ptree_node tree_node*
#define sqr(a) ((a) * (a))
#define all(x) (x).begin(), (x).end()
 
const int INF = 1e9;


#ifdef _LOCAL
    mt19937 rnd(223);
    mt19937_64 rndll(231);
#else
    mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
    mt19937_64 rndll(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

template<typename T>             istream& operator>>(istream& is,  vector<T> &v){for (auto& i : v) is >> i;                       return is;}
template<typename T>             ostream& operator<<(ostream& os,  vector<T>  v){for (auto& i : v) os << i << ' ';                return os;}
template<typename T, typename U> istream& operator>>(istream& is, pair<T, U> &p){is >> p.first >> p.second;                       return is;}
template<typename T, typename U> ostream& operator<<(ostream& os, pair<T, U>  p){os << '(' << p.first << "; " << p.second << ')'; return os;}

/*const int MAX_MEM = 1e8; 
int mpos = 0; 
char mem[MAX_MEM]; 
inline void * operator new ( size_t n ) { 
    assert((mpos += n) <= MAX_MEM); 
    return (void *)(mem + mpos - n); 
} 
inline void operator delete (void *) noexcept { } */

#define fast(){ \
    ios_base::sync_with_stdio(0); \
    cin.tie(0); \
}

/* --------------------------
    Solutions starts here!!!
   -------------------------- */

graph g;
vector <int> h, f, et;
int st[25][200005];

void dfs (int v) {
    f[v] = et.size();
    et.pb(v);
    for (auto &u : g[v]) 
        if (h[u] == 0) {
            h[u] = h[v] + 1;
            dfs(u);
            et.pb(v);
        }
}



signed main() {
    #ifdef _LOCAL
        clock_t Tsart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    fast();

    int n, m;
    cin >> n >> m;
    g.resize(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        g[x].pb(i);
    }
    
    h.resize(n);
    et.reserve(2 * n);
    f.resize(n);
    h[0] = 1;
    
    dfs(0);
    et.shrink_to_fit();
    int N = et.size();
    
    for (int i = 0; i < N; i++)
        st[0][i] = et[i];

    for (int i = 1; i <= __lg(N); i++)
        for (int j = 0; j + (1 << i) <= N; j++)
            if (h[st[i - 1][j]] < h[st[i - 1][j + (1 << (i - 1))]])
                st[i][j] = st[i - 1][j];
            else
                st[i][j] = st[i - 1][j + (1 << (i - 1))];
    
    ll a1, a2;
    cin >> a1 >> a2;
    ll x, y, z;
    cin >> x >> y >> z;

    ll sum = 0, ans = 0;
    while (m--) {
        ll l = (a1 + ans) % n, r = a2;
        l = f[l]; r = f[r];
        if (l > r)
            swap(l, r);
        ll g = __lg(r - l + 1);
        if (h[st[g][l]] < h[st[g][r - (1 << g) + 1]])
            ans = st[g][l];
        else
            ans = st[g][r - (1 << g) + 1];
        sum += ans;
        a1 = (a1 * x + a2 * y + z) % n;
        a2 = (a2 * x + a1 * y + z) % n;
    }

    cout << sum << '\n';

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
