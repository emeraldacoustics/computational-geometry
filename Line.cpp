template <class T>
class Line
{
public:
	Point<T> u, v;

	Line(void)
	{

	}

	Line(const Point<T> & u, const Point<T> & v) : u(u), v(v)
	{

	}

	Line(const T & px, const T & py, const T & qx, const T & qy) : u(px, py), v(qx, qy)
	{

	}

	T operator * (const Line & rhs) const
	{
		return (v - u) * (rhs.v - rhs.u);
	}

	T operator & (const Line & rhs) const
	{
		return (v - u) & (rhs.v - rhs.u);
	}

	bool operator < (const Line & rhs) const
	{
		int vs = sgn((v - u) * (rhs.v - rhs.u)), ss = sgn((v - u) & (rhs.v - rhs.u));
		if (vs == 0 && ss > 0)
			return on_left(rhs.u, false);
		else
			return v - u < rhs.v - rhs.u;
	}

	bool on_left(const Point<T> & p, const bool & inclusive = true) const
	{
		int s = sgn(p.cross(u, v));
		return s == 0 ? inclusive : s > 0;
	}

	bool on_right(const Point<T> & p, const bool & inclusive = true) const
	{
		int s = sgn(p.cross(u, v));
		return s == 0 ? inclusive : s < 0;
	}
};
