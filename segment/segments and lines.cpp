template <class T>
bool seg_seg_intersect(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2, const bool & inclusive = true)
{
	if (p1 == p2)
		return inclusive && p1.on_segment(q1, q2);
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	int pv1s = sgn(pv1), pv2s = sgn(pv2);
	T qv1 = q1.cross(q2, p1), qv2 = q1.cross(q2, p2);
	int qv1s = sgn(qv1), qv2s = sgn(qv2);
	if (pv1s == 0 && pv2s == 0)
	{
		Point<T> v = p2 - p1;
		T qs[2] = {v & q1, v & q2};
		if (qs[0] > qs[1])
			swap(qs[0], qs[1]);
		T mns = max(v & p1, qs[0]), mxs = min(v & p2, qs[1]);
		int s = sgn(mns - mxs);
		return s == 0 ? inclusive : s < 0;
	}
	else
	{
		if (pv1s * pv2s > 0 || qv1s * qv2s > 0)
			return false;
		else if (pv1s * pv2s == 0 || qv1s * qv2s == 0)
			return inclusive;
		else
			return true;
	}
}

template <class T>
bool seg_seg_intersection(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2, Point<T> & ans, const bool & inclusive = true)
{
	if (p1 == p2)
	{
		if (inclusive && p1.on_segment(q1, q2))
		{
			ans = p1;
			return true;
		}
		else
			return false;
	}
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	int pv1s = sgn(pv1), pv2s = sgn(pv2);
	T qv1 = q1.cross(q2, p1), qv2 = q1.cross(q2, p2);
	int qv1s = sgn(qv1), qv2s = sgn(qv2);
	if (pv1s == 0 && pv2s == 0)
	{
		Point<T> v = p2 - p1;
		Point<T> pa[2] = {p1, p2}, qa[2] = {q1, q2};
		if ((v & q1) - (v & q2) > 0)
			swap(qa[0], qa[1]);
		Point<T> mn = (v & pa[0]) - (v & qa[0]) > 0 ? pa[0] : qa[0], mx = (v & pa[1]) - (v & qa[1]) < 0 ? pa[1] : qa[1];
		ans = (mn + mx) / 2;
		int s = sgn((v & mn) - (v & mx));
		return s == 0 ? inclusive : s < 0;
	}
	else
	{
		ans = q1 * (pv2 / (pv1 + pv2)) + q2 * (pv1 / (pv1 + pv2));
		if (pv1s * pv2s > 0 || qv1s * qv2s > 0)
			return false;
		else if (pv1s * pv2s == 0 || qv1s * qv2s == 0)
			return inclusive;
		else
			return true;
	}
}

template <class T>
T seg_seg_distance(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2)
{
	if (segment_segment_intersect(p1, p2, q1, q2, true))
		return 0;
	else
		return min(min(p1.distance_to_segment(q1, q2), p2.distance_to_segment(q1, q2)),
				   min(q1.distance_to_segment(p1, p2), q2.distance_to_segment(p1, p2)));
}

/*
 * 0	parallel
 * 1	cross
 * 2	collinear
 */
template <class T>
int line_line_intersection(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2, Point<T> & ans)
{
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	if (sgn(pv1 - pv2) == 0)
	{
		if (sgn(pv1) == 0)
		{
			ans = p1;
			return 2;
		}
		else
			return 0;
	}
	else
	{
		ans = q1 * (-pv2 / (pv1 - pv2)) + q2 * (pv1 / (pv1 - pv2));
		return 1;
	}
}

template <class T>
Point<T> line_line_intersection(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2)
{
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	return q1 * (-pv2 / (pv1 - pv2)) + q2 * (pv1 / (pv1 - pv2));
}

