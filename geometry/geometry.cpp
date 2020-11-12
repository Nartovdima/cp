#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <map>
#include <set>

using namespace std;

#define fast() ios_base::sync_with_stdio(false); cin.tie(0)

#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define sqr(a) ((a) * (a))
#define vout(a) cout << #a << ": " << (a) << '\n'

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

const int INF = 0x7fffffff; //MAX_INT
const ll MOD = (1 << 30) + 1;
const ld EPS = 1e-8;
const ld PI = 3.14159265358979323;
const int MAXN = 1e5 + 1000;

struct point { //структура которая хранит наши точки
    long double x;
    long double y;
    point(): x(0), y(0) {}; //создание точки 0; 0
    point(ld _x, ld _y): x(_x), y(_y) {}; //создание точки с координатами x, y
    friend istream& operator>>(istream& in, point& p) { //перегрузка ввода
        in >> p.x >> p.y;
        return in;
    }
    friend ostream& operator<<(ostream& out, point& p) { //перегрузка вывода
        out << p.x << ' ' << p.y << '\n';
        return out;
    }
};

struct vec { //структура для хранения и работы с векторами
    long double x;
    long double y;
    vec(): x(0), y(0) {}; //создание вектора с координатами 0; 0
    vec(ld _x, ld _y): x(_x), y(_y) {}; //создание вектора с координатами x, y
    vec(const point& A, const point& B) { //создание вектора из 2-х точек
        x = B.x - A.x;
        y = B.y - A.y;
    }
    long double length() { //длина вектора
        return hypotl(x, y);
    }
    vec operator+(const vec& v) { //перегрузка сложения вектора и числа
        return vec(x + v.x, y + v.y);
    }
    vec operator-(const vec& v) { //перегрузка вычитание из вектора числа
        return vec(x - v.x, y - v.y);
    }
    friend vec operator*(long double k, const vec& v) { //перегрузка умножения вектора и числа
        return vec(k * v.x, k * v.y);
    }
    vec norm() { //норма вектора
        long double leng = length();
        return vec(x / leng, y / leng);
    }
    vec normal() { //вектор нормали
        return vec(-y, x);
    }
    long double operator*(const vec& v) { //перегрузка умножения на скалярное произведение
        return x * v.x + y * v.y;
    }
    long double operator%(const vec& v) { //перегрузка умножения на векторное произведение
        return x * v.y - y * v.x;
    }
};

ld len(point a, point b) { //расстояние между 2-мя точками
    vec v = vec(a, b);
    return v.length();
}

int pt_in_cr(point a, point o, int r) { //принадлежность точки окружности
	if ((o.x - a.x) * (o.y - a.y) == r * r)
		return 0;
	if ((o.x - a.x) * (o.y - a.y) < r * r)
		return -1;
	if ((o.x - a.x) * (o.y - a.y) > r * r)
		return 1;
}

bool pt_in_ob(int n, point *p, point a) //принадлежность точки многоугольнику
{
    bool flag = false;
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        if ((p[i].y < a.y && p[j].y >= a.y || p[j].y < a.y && p[i].y >= a.y) &&
        (p[i].x + (a.y - p[i].y) / (p[j].y - p[i].y) * (p[j].x - p[i].x) < a.x) )
            flag = !flag;
        j = i;
    }
	return flag;
}

ld pt_to_sg(point b1, point b2, point a) { //расстояние от точки до отрезка
	vec v = vec(b1, b2);
	vec v1 = vec(a, b1);
	vec v2 = vec(a, b2);
	if (v1 * v <= 0 && v2 * v >= 0)
		return abs(v.y * a.x - b1.x * v.y - v.x * a.y + v.x * b1.y) / v.length();
	else
		return min(v2.length(), v1.length());
}

int main() {
    #ifdef _LOCAL
    	clock_t Rtime = clock();
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
    fast();

	//Write your code here

	#ifdef _LOCAL
		cerr << "Runtime: " << (ld)(clock() - Rtime) / CLOCKS_PER_SEC << '\n';
	#endif		
    return 0;
}