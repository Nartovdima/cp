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
 
int n, m;
vector <vector <dl>> g;
vector <ll> d;
 
void dijkstra (int v) {
    d.resize(n, INF);
    d[v] = 0;
    priority_queue <dl, vector <dl>, greater <dl>> q;
    q.push({d[v], v});
    while (!q.empty()) {
        auto [w, u] = q.top();
        q.pop();
        if (w > d[u]) continue;
        for (auto [to, dist] : g[u]) {
            if (d[u] + dist < d[to]) {
                d[to] = d[u] + dist;
                q.push({d[to], to});
            }
        }
    }
}
 
signed main() {
    #ifdef _LOCAL
        clock_t Tsart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    fast();
     
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    
    dijkstra(0);

    cout << d[n - 1] << '\n';
    
    #ifdef _LOCAL
        cerr << "Runtime: " << (ld)(clock() - Tsart) / CLOCKS_PER_SEC << '\n';
    #endif      
    return 0;
}
