template <class T>
Point<T> line_line_intersection(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2)
{
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	return q1 * (-pv2 / (pv1 - pv2)) + q2 * (pv1 / (pv1 - pv2));
}

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
		return p.cross(u, v) > 0;
	}

	bool on_right(const Point<T> & p, const bool & inclusive = true) const
	{
		return p.cross(u, v) < 0;
	}
};

template <class T>
Point<T> line_line_intersection(const Line<T> & lhs, const Line<T> & rhs)
{
	return line_line_intersection(lhs.u, lhs.v, rhs.u, rhs.v);
}

template <class T>
bool half_plane_intersection(vector<Line<T> > L, vector<Point<T> > & ans)
{
	const int n = L.size();
	sort(L.begin(), L.end());
	int first = 0, last = 0;
	vector<Point<T> > p(n);
	vector<Line<T> > q(n);
	q[last++] = L[0];
	for (int i = 1; i < n; i++)
	{
		for (; first + 1 < last && L[i].on_right(p[last - 2]); last--);
		for (; first + 1 < last && L[i].on_right(p[first]); first++);
		q[last++] = L[i];
		if (sgn(q[last - 2] * q[last - 1]) == 0)
		{
			last--;
			if (q[last - 1].on_left(L[i].u))
				q[last - 1] = L[i];
		}
		if (first + 1 < last)
			p[last - 2] = line_line_intersection(q[last - 2], q[last - 1]);
	}
	for (; first + 1 < last && q[first].on_right(p[last - 2]); last--);
	if (last - first <= 2)
		return false;
	p[last - 1] = line_line_intersection(q[first], q[last - 1]);
	ans.clear();
	for (int i = first; i < last; i++)
		ans.push_back(p[i]);
	return true;
}

