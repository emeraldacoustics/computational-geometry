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
	if (sgn(r1 + r2 - d) >= 0 && sgn(fabsl(r1 - r2) - d) <= 0 && sgn(d) != 0)
	{
		const Point<T> v = (o2 - o1).unit(r1);
		T phi = interior_angle(r2, r1, d); //acosl(trigonometric((r1 * r1 + d * d - r2 * r2) / (r1 * d * 2)));
		if (sgn(r1 + r2 - d) == 0 || sgn(fabsl(r1 - r2) - d) == 0)
		{
			ans.push_back(o1 + v.rotate(phi));
			if (multiple)
				ans.push_back(ans[0]);
		}
		else
		{
			ans.push_back(o1 + v.rotate(-phi));
			ans.push_back(o1 + v.rotate(phi));
		}
	}
	return ans;
}

template <class T>
vector<Point<T> > tangents(const Point<T> & o, const T & r, const Point<T> & p, const bool & multiple = false)
{
	vector<Point<T> > ans;
	const T d = p.distance(o);
	const int s = sgn(d - r);
	if (s == 0)
	{
		ans.push_back(p);
		if (multiple)
			ans.push_back(ans[0]);
	}
	else if (s > 0)
	{
		const Point<T> v = (p - o).unit(r);
		const T phi = acosl(trigonometric(r / d));
		ans.push_back(o + v.rotate(-phi));
		ans.push_back(o + v.rotate(phi));
	}
	return ans;
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
	else if (s == 0)
	{
		if (sgn(r1 - r2) < 0)
			v = v * -1;
		ans.emplace_back(o1 + v.unit(r1), o1 + v.unit(r1));
		if (multiple)
			ans.push_back(ans[0]);
	}
	else if (sgn(r1 - r2) == 0)
	{
		Point<T> n = (o2 - o1).normal();
		ans.emplace_back(o1 - n.unit(r1), o2 - n.unit(r2));
		ans.emplace_back(o1 + n.unit(r1), o2 + n.unit(r2));
	}
	else
	{
		T phi = acosl(trigonometric((r1 - r2) / d));
		ans.emplace_back(o1 + v.unit(r1).rotate(-phi), o2 + v.unit(r2).rotate(-phi));
		ans.emplace_back(o1 + v.unit(r1).rotate(phi), o2 + v.unit(r2).rotate(phi));
	}
	return ans;
}

template <class T>
vector<pair<Point<T>, Point<T> > > circle_circle_inner_tangents(const Point<T> & o1, const T & r1, const Point<T> & o2, const T & r2)
{
	vector<pair<Point<T>, Point<T> > > ans;
	Point<T> v = o2 - o1;
	T d = o1.distance(o2);
	if (sgn(r1 + r2 - d) == 0)
	{
		ans.emplace_back(o1 + v.unit(r1), o1 + v.unit(r1));
	}
	else if (sgn(r1 + r2 - d) < 0)
	{
		T phi = acosl(trigonometric((r1 + r2) / d));
		ans.emplace_back(o1 + v.unit(r1).rotate(-phi), o2 - v.unit(r2).rotate(-phi));
		ans.emplace_back(o1 + v.unit(r1).rotate(phi), o2 - v.unit(r2).rotate(phi));
	}
	return ans;
}

