template <class T>
void convex_hull(Point<T> * first, Point<T> * last, vector<Point<T> > & ans)
{
	Point<T> * & p = first;
	const int n = last - first;
	Point<T> o = *min_element(p, p + n, yxcmp<T>);
	for (int i = 0; i < n; i++)
		p[i] = p[i] - o;
	sort(p, p + n);
	for (int i = 0; i < n; i++)
		p[i] = o + p[i];

	ans.resize(n);
	int sz = 0;
	ans[sz++] = p[0];
	for (int i = 1; i < n; i++)
	{
		for (; sz > 1 && sgn(ans[sz - 2].cross(ans[sz - 1], p[i])) <= 0; sz--);
		ans[sz++] = p[i];
	}
	ans.resize(sz);

	/*	if you want a hull with all possible points on its border
	vector<Point<T> > arr;
	for (int i = 0, k = 0; p[i] != ans[sz - 1]; i++) {
		if (p[i].on_line(ans[k], ans[(k + 1) % sz]))
			arr.push_back(p[i]);
		if (p[i] == ans[(k + 1) % sz])
			k = (k + 1) % sz;
	}
	for (int i = n - 1; i > 0 && p[i].on_segment(ans[0], ans[sz - 1]); i--)
		arr.push_back(p[i]);
	cerr << arr.size() << endl;
	ans = arr;*/
}

template <class T>
vector<Point<T> > convex_hull(Point<T> * first, Point<T> * last)
{
	vector<Point<T> > ans;
	convex_hull(first, last, ans);
	return ans;
}

template <class T>
Point<T> * convex_hull(Point<T> * first, Point<T> * last, Point<T> * q)
{
	vector<Point<T> > ans;
	convex_hull(first, last, ans);
	for (int i = 0; i < ans.size(); i++)
		q[i] = ans[i];
	return q + ans.size();
}

template <class T>
void convex_hull(vector<Point<T> > & p, vector<Point<T> > & ans)
{
	const int n = p.size();
	Point<T> o = *min_element(p.begin(), p.end(), yxcmp<T>);
	for(int i = 0; i < n; i++)
		p[i] = p[i] - o;
	sort(p.begin(), p.end());
	for (int i = 0; i < n; i++)
		p[i] = o + p[i];

	ans.resize(n);
	int sz = 0;
	ans[sz++] = p[0];
	for (int i = 1; i < n; i++)
	{
		for (; sz > 1 && sgn(ans[sz - 2].cross(ans[sz - 1], p[i])) <= 0; sz--);
		ans[sz++] = p[i];
	}
	ans.resize(sz);

	/*	if you want a hull with all possible points on its border
	vector<Point<T> > arr;
	for (int i = 0, k = 0; p[i] != ans[sz - 1]; i++) {
		if (p[i].on_line(ans[k], ans[(k + 1) % sz]))
			arr.push_back(p[i]);
		if (p[i] == ans[(k + 1) % sz])
			k = (k + 1) % sz;
	}
	for (int i = n - 1; i > 0 && p[i].on_segment(ans[0], ans[sz - 1]); i--)
		arr.push_back(p[i]);
	cerr << arr.size() << endl;
	ans = arr;*/
}

template <class T>
vector<Point<T> > convex_hull(vector<Point<T> > & p)
{
	vector<Point<T> > ans;
	convex_hull(p, ans);
	return ans;
}

template <class T>
Point<T> * convex_hull(vector<Point<T> > & p, Point<T> * q)
{
	vector<Point<T> > ans;
	convex_hull(p, ans);
	for (int i = 0; i < ans.size(); i++)
		q[i] = ans[i];
	return q + ans.size();
}
