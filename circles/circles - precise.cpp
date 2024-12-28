template <class T>
T interior_angle(const T & a, const T & b, const T & c)
{
	return acosl(trigonometric((b * b + c * c - a * a) / b / c / 2));
}

template <class T>
vector<Point<T> > circle_circle_intersection(const Point<T> & o1, const T & r1, const Point<T> & o2, const T & r2, const bool & multiple = false)
{
	vector<Point<T> > ans;
	const T d = o1.distance(o2);
	if (sgn(d) != 0)
	{
		Point<T> v = o2 - o1;
		T a = ((r1 * r1 - r2 * r2) / d + d) / 2;
		int s = sgn(fabsl(a) - r1);
		if (s == 0)
		{
			ans.push_back(o1 + v.unit(a));
			if (multiple)
				ans.push_back(ans[0]);
		}
		else if (s < 0)
		{
			T h = sqrtl(r1 * r1 - a * a);
			Point<T> u = v.unit(a);
			v = v.normal().unit(h);
			ans.push_back(o1 + u - v);
			ans.push_back(o1 + u + v);
		}
	}
	return ans;
}

template <class T>
vector<Point<T> > tangents(const Point<T> & o, const T & r, const Point<T> & p, const bool & multiple = false)
{
	const T d = p.distance(o);
	return circle_circle_intersection(o, r, (o + p) / 2, d / 2, multiple);
}

template <class T>
vector<Point<T> > circle_line_intersection(const Point<T> & o, const T & r, const Point<T> & p, const Point<T> & q, const bool & multiple = false)
{
	vector<Point<T> > ans;
	const Point<T> u = o.project(p, q);
	const T d = o.distance(u);
	const int s = sgn(d - r);
	if (s == 0)
	{
		ans.push_back(u);
		if (multiple)
			ans.push_back(ans[0]);
	}
	else if (s < 0)
	{
		const T l = sqrtl(r * r - d * d);
		const Point<T> v = p == q ? (u - o).normal().unit(l) : (q - p).unit(l);
		ans.push_back(u - v);
		ans.push_back(u + v);
	}
	return ans;
}

template <class T>
T circle_circle_intersection_area(const Point<T> & o1, const T & r1, const Point<T> & o2, const T & r2)
{
	T d = o1.distance(o2);
	if (sgn(r1 + r2 - d) <= 0)
		return 0;
	else if (sgn(fabsl(r2 - r1) - d) >= 0)
		return sqr(min(r2, r1)) * pi;
	else
	{
		T ans = 0, d2 = o1.distance2(o2), a;
		a = interior_angle(r2, r1, d); //acosl((d2 + sqr(r1) - sqr(r2)) / d / r1 / 2);
		ans += sqr(r1) * (a - sinl(a) * cosl(a));
		a = interior_angle(r1, r2, d); //acosl((d2 + sqr(r2) - sqr(r1)) / d / r2 / 2);
		ans += sqr(r2) * (a - sinl(a) * cosl(a));
		return ans;
	}
}

template <class T>
vector<pair<Point<T>, Point<T> > > circle_circle_outer_tangents(const Point<T> & o1, const T & r1, const Point<T> & o2, const T & r2, const bool & multiple = false)
{
	vector<pair<Point<T>, Point<T> > > ans;
	Point<T> v = o2 - o1;
	T d = o1.distance(o2);
	int s = sgn(fabsl(r1 - r2) - d);
	if (o1 == o2 || s > 0)
	{

	}
	else if (sgn(r1 - r2) == 0)
	{
		Point<T> n = (o2 - o1).normal();
		ans.emplace_back(o1 - n.unit(r1), o2 - n.unit(r2));
		ans.emplace_back(o1 + n.unit(r1), o2 + n.unit(r2));
	}
	else
	{
		Point<T> p = o1 + v / (r1 - r2) * r1;
		vector<Point<T> > ans1 = tangents(o1, r1, p, multiple), ans2 = tangents(o2, r2, p, multiple);
		assert(ans1.size() == ans2.size());
		for (int i = 0; i < ans1.size() && i < ans2.size(); i++)
			ans.emplace_back(ans1[i], ans2[i]);
	}
	return ans;
}

template <class T>
vector<pair<Point<T>, Point<T> > > circle_circle_inner_tangents(const Point<T> & o1, const T & r1, const Point<T> & o2, const T & r2, const bool & multiple = false)
{
	vector<pair<Point<T>, Point<T> > > ans;
	Point<T> v = o2 - o1;
	T d = o1.distance(o2);
	int s = sgn(r1 + r2 - d);
	if  (s <= 0)
	{
		Point<T> p = (o1 * r2 + o2 * r1) / (r1 + r2);
		vector<Point<T> > ans1 = tangents(o1, r1, p, multiple), ans2 = tangents(o2, r2, p, multiple);
		assert(ans1.size() == ans2.size());
		for (int i = 0; i < ans1.size() && i < ans2.size(); i++)
			ans.emplace_back(ans1[i], ans2[i]);
	}
	return ans;
}

