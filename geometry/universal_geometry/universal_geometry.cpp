#include <bits/stdc++.h>
//#include <ext/rope>
 
using namespace std;
//using namespace __gnu_cxx;
 
#define XD true
#define ll long long
#define ld long double
#define pb push_back
#define p push
#define f first
#define s second
#define m_p make_pair
#define op(){\
    freopen("input.txt", "r", stdin);\
    freopen("output.txt", "w", stdout);\
}
#define fast(){\
    ios_base::sync_with_stdio(0);\
    cin.tie(0);\
}

const
    ll MAXN = 2e+4 + 100,
        INF = (1 << 30)+ 1,
        P = 31;
 
struct point
{
    ld x, y;
};

struct line
{
    ld a, b, c;
};

point make_vec(point a, point b)
{
    return {b.x - a.x, b.y - a.y};
}

int dot_product(point v1, point v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

int vec_product(point v1, point v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

float len(point a, point b)
{
    point v1 = make_vec(a, b);
    return sqrt(v1.x * v1.x + v1.y * v1.y);
}

bool cir(point a, point o, int r)
{
    return ((o.x - a.x) * (o.y - a.y) == r * r);
}

vector <point> polygon;

bool checkin(point a)
{
    point v1, v2;
    float s = 0, x;

    for (int i = 0; i < polygon.size() - 1; i++)
    {
        v1 = make_vec(a, polygon[i]);
        v2 = make_vec(a, polygon[i + 1]);
        x = vec_product(v1, v2);
        s += x;
        if (x < 0)
            return false;
    }
    return true;
}

float dist(point a, point b1, point b2)
{
    point v1 = make_vec(b1, a),
          v2 = make_vec(b1, b2);
    bool ochka = (dot_product(v1, v2) > 0);
    v1 = make_vec(b2, a);
    v2 = make_vec(b2, b1);
    ochka = (ochka && dot_product(v1, v2) > 0);
    line AB;
    AB.a = b2.y - b1.y;
    AB.b = b1.x - b1.y;
    AB.c = b1.x * b2.y - b1.y * b2.x;
    if (ochka)
        return (AB.a * a.x + AB.b * a.y + AB.c) / sqrt(AB.a * AB.a + AB.b * AB.b);
    else
        return min(len(a, b1), len(a, b2));
}
