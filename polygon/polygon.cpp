template <class T>
T polygon_area(const Point<T> * first, const Point<T> * last)
{
	const Point<T> * & p = first;
	const int n = last - first;
	T ans = 0;
	for (int i = 0; i < n; i++)
		ans += p[i] * p[(i + 1) % n];
	ans /= 2;
	return ans;
}

template <class T>
T polygon_area2(const Point<T> * first, const Point<T> * last)
{
	const Point<T> * & p = first;
	const int n = last - first;
	T ans = 0;
	for (int i = 0; i < n; i++)
		ans += p[i] * p[(i + 1) % n];
	return ans;
}

template <class T>
T polygon_area(const vector<Point<T> > & p)
{
	const int n = p.size();
	T ans = 0;
	for (int i = 0; i < n; i++)
		ans += p[i] * p[(i + 1) % n];
	ans /= 2;
	return ans;
}

template <class T>
T polygon_area2(const vector<Point<T> > & p)
{
	const int n = p.size();
	T ans = 0;
	for (int i = 0; i < n; i++)
		ans += p[i] * p[(i + 1) % n];
	return ans;
}

template <class T>
T perimeter(const Point<T> * first, const Point<T> * last)
{
	const Point<T> * & p = first;
	const int n = last - first;
	T ans = 0;
	for (int i = 0; i < n; i++)
		ans += p[i].distance(p[(i + 1) % n]);
	return ans;
}

template <class T>
T perimeter(const vector<Point<T> > & p)
{
	const int n = p.size();
	T ans = 0;
	for (int i = 0; i < n; i++)
		ans += p[i].distance(p[(i + 1) % n]);
	return ans;
}

template <class T>
Point<T> center_of_gravity(const Point<T> * first, const Point<T> * last)
{
	const Point<T> * & p = first;
	const int n = last - first;
	Point<T> ans;
	T s = 0;
	for (int i = 0; i < n; i++)
	{
		T v = p[i] * p[(i + 1) % n];
		ans += (p[i] + p[(i + 1) % n]) / 3 * v;
		s += v;
	}
	return ans / s;
}

template <class T>
Point<T> center_of_gravity(const vector<Point<T> > & p)
{
	const int n = p.size();
	Point<T> ans;
	T s = 0;
	for (int i = 0; i < n; i++)
	{
		T v = p[i] * p[(i + 1) % n];
		ans += (p[i] + p[(i + 1) % n]) / 3 * v;
		s += v;
	}
	return ans / s;
}

// time comlexity: log(n)
template <class T>
bool point_in_convex_polygon(const Point<T> * first, const Point<T> * last, const Point<T> & q, const bool & inclusive = true)
{
	const Point<T> * & p = first;
	const int n = last - first;
	if (n == 1)
		return inclusive && p[0] == q;
	else if (n == 2)
		return inclusive && q.on_segment(p[0], p[1]);
	else if (!q.in_angle(p[0], p[1], p[n - 1]))
		return false;
	else if (q.on_line(p[0], p[1]) || q.on_line(p[0], p[n - 1]))
		return inclusive && (q.on_segment(p[0], p[1]) || q.on_segment(p[0], p[n - 1]));
	else
	{
		int low = 1, high = n - 1;
		for (; low < high - 1; )
		{
			int mid = low + (high - low) / 2;
			(sgn(q.cross(p[0], p[mid])) < 0 ? high : low) = mid;
		}
		if (q.on_segment(p[low], p[high]))
			return inclusive;
		else
			return q.in_triangle(p[0], p[low], p[high]);
	}
}

// time comlexity: log(n)
template <class T>
bool point_in_convex_polygon(const vector<Point<T> > & p, const Point<T> & q, const bool & inclusive = true)
{
	const int n = p.size();
	if (n == 1)
		return inclusive && p[0] == q;
	else if (n == 2)
		return inclusive && q.on_segment(p[0], p[1]);
	else if (!q.in_angle(p[0], p[1], p[n - 1]))
		return false;
	else if (q.on_line(p[0], p[1]) || q.on_line(p[0], p[n - 1]))
		return inclusive && (q.on_segment(p[0], p[1]) || q.on_segment(p[0], p[n - 1]));
	else
	{
		int low = 1, high = n - 1;
		for (; low < high - 1; )
		{
			int mid = low + (high - low) / 2;
			(sgn(q.cross(p[0], p[mid])) < 0 ? high : low) = mid;
		}
		if (q.on_segment(p[low], p[high]))
			return inclusive;
		else
			return q.in_triangle(p[0], p[low], p[high]);
	}
}

template <class T>
bool point_in_polygon(const Point<T> * first, const Point<T> * last, const Point<T> & q, const bool & inclusive = true)
{
	const Point<T> * & p = first;
	const int n = last - first;
	int k, d1, d2, wn = 0;
	for (int i = 0; i < n; i++)
	{
		if (q.on_segment(p[i], p[(i + 1) % n], true))
			return inclusive;
		k = sgn(p[i].cross(p[(i + 1) % n], q));
		d1 = sgn(p[i].y - q.y);
		d2 = sgn(p[(i + 1) % n].y - q.y);
		if (k > 0 && d1 <= 0 && d2 > 0)
			wn++;
		else if (k < 0 && d2 <= 0 && d1 > 0)
			wn--;
	}
	return wn != 0;
}

template <class T>
bool point_in_polygon(const vector<Point<T> > & p, const Point<T> & q, const bool & inclusive = true)
{
	const int n = p.size();
	int k, d1, d2, wn = 0;
	for (int i = 0; i < n; i++)
	{
		if (q.on_segment(p[i], p[(i + 1) % n], true))
			return inclusive;
		k = sgn(p[i].cross(p[(i + 1) % n], q));
		d1 = sgn(p[i].y - q.y);
		d2 = sgn(p[(i + 1) % n].y - q.y);
		if (k > 0 && d1 <= 0 && d2 > 0)
			wn++;
		else if (k < 0 && d2 <= 0 && d1 > 0)
			wn--;
	}
	return wn != 0;
}

template <class T>
void cut_polygon(const Point<T> * first, const Point<T> * last, const Point<T> & a, const Point<T> & b, vector<Point<T> > & ans)
{
	/*	if you are NOT sure that p is given in counter-clockwise order
	if (sgn(polygon_area2(p)) < 0)
		reverse(p.begin(), p.end());*/
	const Point<T> * & p = first;
	const int n = last - first;
	ans.clear();
	for (int i = 0; i < n; i++)
	{
		const Point<T> & u = p[i], & v = p[(i + 1) % n];
		if (sgn(a.cross(b, u)) >= 0)
			ans.push_back(a);
		if (sgn((b - a) * (v - u)) != 0)
		{
			Point<T> c = line_line_intersection(a, b, u, v);
			if (c.on_segment(u, v, false))
				ans.push_back(c);
		}
	}
}

template <class T>
void cut_polygon(const vector<Point<T> > & p, const Point<T> & a, const Point<T> & b, vector<Point<T> > & ans)
{
	/*	if you are NOT sure that p is given in counter-clockwise order
	if (sgn(polygon_area2(p)) < 0)
		reverse(p.begin(), p.end());*/
	const int n = p.size();
	ans.clear();
	for (int i = 0; i < n; i++)
	{
		const Point<T> & u = p[i], & v = p[(i + 1) % n];
		if (sgn(a.cross(b, u)) >= 0)
			ans.push_back(a);
		if (sgn((b - a) * (v - u)) != 0)
		{
			Point<T> c = line_line_intersection(a, b, u, v);
			if (c.on_segment(u, v, false))
				ans.push_back(c);
		}
	}
}

