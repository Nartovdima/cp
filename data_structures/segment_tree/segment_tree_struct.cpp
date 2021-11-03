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
    Solution starts here!!!
   -------------------------- */
 
struct Node {
    ll sum = 0, am;
    int push = -1;
};
 
struct ST {
    int sz = 2;
    vector <Node> tree;
 
    ST (int n) {
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1, Node());
 
        build(1, 0, n);
    }
 
    /*void print (int v, int l, int r) {
        cout << v << ' ' << l << ' ' << r << ' ' << tree[v].am << '\n';
        if (r - l == 1) 
            return;
        int m = (l + r) / 2;
        print(v * 2, l, m);
        print(v * 2 + 1, m, r);
    }*/
 
    ll get_sum (int v) {
        if (tree[v].push == -1)
            return tree[v].sum;
        else
            return tree[v].push * tree[v].am;
    }
 
    void relax (int v) {
        if (v < sz) 
            tree[v].sum = get_sum(v * 2) + get_sum(v * 2 + 1);
    }
 
    void push (int v) {
        if (v < sz && tree[v].push != -1) {
            tree[v * 2].push = tree[v * 2 + 1].push = tree[v].push;
            tree[v].push = -1;
            relax(v);
        }
    }
 
    void build (int v, int l, int r) {
        if (r - l == 1) {
            tree[v].am = 1;
            //tree[v].sum = a[l];
            return;
        }
        push(v);
        int m = (l + r) / 2;
        build(v * 2, l, m);
        build(v * 2 + 1, m, r);
        tree[v].am = tree[v * 2].am + tree[v * 2 + 1].am;
        //relax(v);
    }
 
    void change (int v, int l, int r, int &pos, ll &x) {
        if (r - l == 1 && pos == l) {
            tree[v].sum = x;
            return;
        }
        push(v);
        int m = (l + r) / 2;
        if (pos < m)
            change(v * 2, l, m, pos, x);
        else
            change(v * 2 + 1, m, r, pos, x);
        relax(v);
    }
 
    void update (int v, int l, int r, int L, int R, ll &x) {
        if (R <= l || r <= L)
            return;
        if (L <= l && r <= R) {
            tree[v].push = x;
            return;
        }
        push(v);   
        int m = (l + r) / 2;
        update(v * 2, l, m, L, R, x);
        update(v * 2 + 1, m, r, L, R, x);
        relax(v);
    }
 
    ll get_f (int v, int l, int r, int L, int R) {
        if (R <= l || r <= L)
            return 0;
        if (L <= l && r <= R)
            return get_sum(v);
        push(v);
        int m = (l + r) / 2;
        return get_f(v * 2, l, m, L, R) + get_f(v * 2 + 1, m, r, L, R);
    } 
 
};
 
signed main() {
    #ifdef _LOCAL
        clock_t Tsart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    fast();
 
    int n, m;
    cin >> n >> m;
    ST tmp(n);
    while (m--) {
        char c;
        cin >> c;
        if (c == 'A') {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            tmp.update(1, 0, n, l - 1, r, x);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << tmp.get_f(1, 0, n, l - 1, r) << '\n';
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
