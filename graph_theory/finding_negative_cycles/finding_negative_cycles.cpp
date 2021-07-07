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
const ld EPS = 1e-8;
const ld PI = atan2(0.0, -1.0);
const int M = 1e9;
const int MAXN = 2 * 1e5;

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

struct edge {
    ll v, u, w;
};

vector <edge> e;
vector <ll> d, parent, ans;
vector <bool> used;

signed main() {
    #ifdef _LOCAL
        clock_t Tsart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    fast();

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 100000)
                continue;
            edge tmp;
            tmp.v = i; tmp.u = j; tmp.w = x;
            e.pb(tmp);
        }
    /*for (auto i : e)
        cout << i.v << ' ' << i.u << ' ' << i.w << '\n';*/
    bool flag;
    d.resize(n, INF);
    parent.resize(n, INF);
    for (int t = 0; t < n; t++) {
        if (d[t] != INF) continue;
        d[t] = 0;
        parent[t] = t;
        int relax;
        for (int i = 0; i < n; i++) {
            flag = 0;
            for (auto i : e) {
                if (d[i.v] == INF)
                    continue;
                if (d[i.u] > d[i.v] + i.w) {
                    d[i.u] = d[i.v] + i.w;
                    parent[i.u] = i.v;
                    flag = 1;
                    relax = i.u;
                }
            }
        }
        if (flag) {
            cout << "YES" << '\n';
            used.resize(n, 0);
            int v = relax;
            while (!used[v]) {
                used[v] = 1;
                v = parent[v];
            }
            used.clear();
            used.resize(n, 0);
            while (used[v] == 0) {
                used[v] = 1;
                ans.pb(v + 1);
                v = parent[v];
            }
            ans.pb(v + 1);
            reverse(all(ans));
            cout << ans.size() << '\n';
            cout << ans << '\n';
            return 0;
        }
    }
    cout << "NO" << '\n';
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
