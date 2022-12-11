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

template <typename T> struct point {
    T x, y;

    point () : x(0), y(0) {}; // стандартный конструктор

    point (T x1, T y1) : x(x1), y(y1) {}; // создание точки (x, y)

    friend istream& operator >> (istream& is, point& p) { // перегрузка ввода
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator << (ostream& os, point p) { // перегрузка вывода
        os << p.x << ' ' << p.y;
        return os;
    }
};

template <typename T> struct Vector {
    T x, y;

    Vector () : x(0), y(0) {}; // стандартный конструктор

    Vector (T x1, T y1) : x(x1), y(y1) {}; // создание вектора (x, y)

    Vector (point <T> a, point <T> b) { // создание вектора по двум точкам. а - точка начала, b - точка конца
        x = b.x - a.x;
        y = b.y - a.y;
    }

    friend istream& operator >> (istream& is, Vector& v) { // перегрузка ввода
        is >> v.x >> v.y;
        return is;
    }

    friend ostream& operator << (ostream& os, Vector v) { // перегрузка вывода
        os << v.x << ' ' << v.y;
        return os;
    }

    Vector operator + (const Vector& v) { // сложение векторов
        return Vector(v.x + x, v.y + y);
    } 

    Vector operator - (const Vector& v) { // вычитание векторов
        return Vector(x - v.x, y - v.y);
    }

    friend Vector operator * (T k, const Vector& v) { // умножение вектора на число
        return Vector(k * v.x, k * v.y);
    }

    T operator * (const Vector& v) { // скалярное произведение
        return v.x * x + v.y * y;
    }

    T operator % (const Vector& v) { // векторное произведение
        return x * v.y - y * v.x;
    }

    ld length () { // длина вектора
        return sqrt(x * x + y * y);
    }

    T square_length () { // квадрат длины вектора
        return x * x + y * y;
    }

    Vector norm () { // нормирование вектора
        ld l = length();
        return Vector(x / l, y / l);
    }

    Vector rotate (T fi) { // поворот вектора на угол fi 
        return Vector(x * cos(fi) - y * sin(fi), y * cos(fi) + x * sin(fi));
    }

    Vector normal () { // вектор-нормаль
        return Vector(-y, x);
    }
};

template <typename T> struct line {
    T a, b, c;

    line () : a(0), b(0), c(0) {}; // стандартный конструктор

    line (T a1, T b1, T c1) : a(a1), b(b1), c(c1) {}; // создание прямой a * x + b * y + c = 0

    line (point <T> m1, point <T> m2) { // создание прямой по двум точкам
        a = m1.y - m2.y;
        b = m2.x - m1.x;
        c = m1.x * m2.y - m2.x * m1.y;
    }

    Vector <T> norm () { // вектор-нормаль 
        return Vector <T> (a, b);
    }

    Vector <T> direct () { // направляющий вектор
        return Vector <T> (-b, a);
    }

    T dist (point <T> p) { // расстояние от точки до прямой
        return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }
};

/* --------------------------
    Solutions starts here!!!
   -------------------------- */

vector <point <ld>> pol;

signed main() {
    #ifdef _LOCAL
        clock_t Tsart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    fast();

    int n;
    cin >> n;
    pol.resize(n);
    cin >> pol;
    pol.pb(*pol.begin());
    n++;
    point <ld> p(0, 0);

    ld s = 0;
    for (int i = 1; i < n; i++) {
        Vector <ld> a (p, pol[i - 1]), b (p, pol[i]);
        s += a % b;
    }

    cout << fixed << setprecision(3) << abs(s) / 2 << '\n';
    
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
