template <class T>
pair<Point<T> *, Point<T> *> closest_pair_dfs(Point<T> * first, Point<T> * last)
{
	Point<T> * & p = first;
	const int n = last - first;
	long double mn, d;
	pair<Point<T> *, Point<T> *> ans;
	if (n < 4)
	{
		mn = infl;
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				d = p[i].distance2(p[j]);
				if (sgn(mn - d) > 0)
				{
					mn = d;
					ans = make_pair(p + i, p + j);
				}
			}
		}
	}
	else
	{
		int m = n / 2;
		pair<Point<T> *, Point<T> *> lft = closest_pair_dfs(p, p + m), rht = closest_pair_dfs(p + m, p + n);
		long double lmn = lft.first->distance2(*lft.second), rmn = rht.first->distance2(*rht.second);
		mn = min(lmn, rmn);
		ans = sgn(lmn - rmn) <= 0 ? lft : rht;
		vector<Point<T> *> vec;
		for (int i = m - 1; i >= 0 && sgn(sqr(p[i].y - p[m].y) - mn) < 0; i--)
			vec.push_back(p + i);
		for (int i = m; i < n && sgn(sqr(p[i].y - p[m - 1].y) - mn) < 0; i++)
			vec.push_back(p + i);
		sort(vec.begin(), vec.end(), [& ](const Point<T> *lhs, const Point<T> *rhs)
		{
			return xycmp(*lhs, *rhs);
		});
		for (int i = 0; i < vec.size(); i++)
		{
			for (int j = i + 1; j < vec.size() && sgn(sqr(vec[j]->x - vec[i]->x) - mn) < 0; j++)
			{
				d = vec[i]->distance2(*vec[j]);
				if (sgn(mn - d) > 0)
				{
					mn = d;
					ans = make_pair(min(vec[i], vec[j]), max(vec[i], vec[j]));
				}
			}
		}
	}
	return ans;
}

template <class T>
pair<Point<T> *, Point<T> *> closest_pair(Point<T> * first, Point<T> * last)
{
	sort(first, last, yxcmp);
	return closest_pair_dfs(first, last);
}
