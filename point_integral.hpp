#include <cmath>

using namespace std;

typedef long long itype;
typedef long double ftype;

const ftype pi = acosl(-1); // 3.1415926535897932384626433832795l
const ftype radian = 180 / pi; // 57.295779513082320876798154814105l
const ftype eps = 1e-12l;
const int inf = 0x7f7f7f7f;
const long long infll = 0x7f7f7f7f7f7f7f7fll;
const ftype infl = 1e20l;

template <class T>
inline int sgn(const T & x)
{
	return (x > eps) - (x < -eps);
}

template <class T>
inline T non_negative(const T & x)
{
	if (x < 0)
		return 0;
	else
		return x;
}

template <class T>
inline T trigonometric(const T & x)
{
	if (x < -1)
		return -1;
	else if (x < 1)
		return x;
	else
		return 1;
}

template <class T>
inline T sqr(const T & x)
{
	return x * x;
}

#define Vector Point
#define Complex Point

template <class T, class U = ftype>
class Point
{
public:
	T x, y;

	Point(void) : x(0), y(0)
	{

	}

	Point(const T & x, const T & y) : x(x), y(y)
	{

	}

	template <class S>
	Point(const Point<S> & src) : x(src.x), y(src.y)
	{

	}

	Vector operator + (const Vector & rhs) const
	{
		return Vector(x + rhs.x, y + rhs.y);
	}

	Vector operator - (const Vector & rhs) const
	{
		return Vector(x - rhs.x, y - rhs.y);
	}

	U length(void) const
	{
		return sqrtl(x * x + y * y);
	}

	T length2(void) const
	{
		return x * x + y * y;
	}

	U distance(const Point & rhs) const
	{
		return (rhs - *this).length();
	}

	T distance2(const Point & rhs) const
	{
		return (rhs - *this).length2();
	}

	Vector operator * (const T & rhs) const
	{
		return Vector(x * rhs, y * rhs);
	}

	Vector operator / (const T & rhs) const
	{
		return Vector(x / rhs, y / rhs);
	}

	T operator * (const Vector & rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	T operator & (const Vector & rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	T cross(const Point & lhs, const Point & rhs) const
	{
		return (lhs - *this) * (rhs - *this);
	}

	T dot(const Point & lhs, const Point & rhs) const
	{
		return (lhs - *this) & (rhs - *this);
	}

	U operator ^ (const Vector & rhs) const
	{
		U l1 = length(), l2 = rhs.length();
		if (sgn(l1) == 0 || sgn(l2) == 0)
			return 0;
		int s = sgn(*this * rhs);
		U a = acosl(trigonometric(U(*this & rhs) / l1 / l2));
		return s < 0 ? -a : a;
	}

	U angle(void) const
	{
		return atan2l(y, x);
	}

	U angle(const Point & rhs) const
	{
		return (rhs - *this).angle();
	}

	U angle(const Point & lhs, const Point & rhs) const
	{
		return (lhs - *this) ^ (rhs - *this);
	}

	bool operator == (const Point & rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator != (const Point & rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	int quadrant(void) const
	{
		if (x == 0 && y == 0)
			return -1;
		else if (y < 0 || y == 0 && x > 0)
			return 0;
		else
			return 1;
	}

	bool operator < (const Vector & rhs) const
	{
		int lq = quadrant(), rq = rhs.quadrant();
		if (lq != rq)
			return lq < rq;
		else
		{
			int s = sgn(*this * rhs);
			return s != 0 ? s > 0 : length2() - rhs.length2() < 0;
		}
	}

	Vector unit(const T & n = 1) const
	{
		T l = abs(__gcd(x, y));
		return l == 0 ? Vector(n, 0) : Vector(x / l * n, y / l * n);
	}

	Vector normal(const bool & rht = false) const
	{
		return rht ? Vector(y, -x) : Vector(-y, x);
	}

	Vector moderate(void) const
	{
		return y > 0 || y == 0 && x >= 0 ? Vector(x, y) : Vector(-x, -y);
	}

	Complex conjugate(void) const
	{
		return Complex(x, -y);
	}

	Complex operator << (const Complex & rhs) const
	{
		return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
	}

	U distance_to_line(const Point & p, const Point & q) const
	{
		if (p == q)
			return distance(p);
		else
			return cross(p, q) / p.distance(q);
	}

	U distance_to_halfline(const Point & p, const Point & q) const
	{
		if (p == q)
			return distance(p);
		else if (p.dot(q, *this) < 0)
			return distance(p);
		else
			return fabsl(distance_to_line(p, q));
	}

	U distance_to_segment(const Point & p, const Point & q) const
	{
		if (p == q)
			return distance(p);
		else if (p.dot(q, *this) < 0)
			return distance(p);
		else if (q.dot(p, *this) < 0)
			return distance(q);
		else
			return fabsl(distance_to_line(p, q));
	}

	bool on_line(const Point & p, const Point & q) const
	{
		if (p == q)
			return *this == p;
		else
			return cross(p, q) == 0;
	}

	bool on_halfline(const Point & p, const Point & q, const bool & inclusive = true) const
	{
		if (*this == p)
			return inclusive;
		else
			return on_line(p, q) && p.dot(q, *this) >= 0;
	}

	bool on_segment(const Point & p, const Point & q, const bool & inclusive = true) const
	{
		if (*this == p || *this == q)
			return inclusive;
		else
			return on_line(p, q) && dot(p, q) <= 0;
	}

	bool in_triangle(const Point & u, const Point & v, const Point & w, const bool & inclusive = true) const
	{
		Point p[3] = {u, v, w};
		if (u.cross(v, w) < 0)
			reverse(p, p + 3);
		for (int i = 0; i < 3; i++)
		{
			if (on_segment(p[i], p[(i + 1) % 3]))
				return inclusive;
			else if (cross(p[i], p[(i + 1) % 3]) < 0)
				return false;
		}
		return true;
	}

	bool in_angle(const Point & o, const Point & p, const Point & q, const bool & inclusive = true) const
	{
		if (on_halfline(o, p) || on_halfline(o, q))
			return inclusive;
		else if (o.cross(p, q) == 0 && o.dot(p, q) > 0)
			return false;
		int vp = o.cross(p, *this), vq = o.cross(*this, q);
		if (o.cross(p, q) >= 0)
			return vp > 0 && vq > 0;
		else
			return vp > 0 || vq > 0;
	}
};

template <class T>
inline bool xycmp(const Point<T> & lhs, const Point<T> & rhs)
{
	if (lhs.x != rhs.x)
		return lhs.x < rhs.x;
	else
		return lhs.y < rhs.y;
}

template <class T>
inline bool yxcmp(const Point<T> & lhs, const Point<T> & rhs)
{
	if (lhs.y != rhs.y)
		return lhs.y < rhs.y;
	else
		return lhs.x < rhs.x;
}

template <class T>
inline bool azmcmp(const Vector<T> & lhs, const Vector<T> & rhs)
{
	int s = sgn(lhs * rhs);
	return s != 0 ? s > 0 : lhs.length2() - rhs.length2() < 0;
}

