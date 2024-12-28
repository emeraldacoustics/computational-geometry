long long x;

template <class T>
class Segment
{
public:
	Point<T> u, v;

	Segment(void)
	{

	}

	Segment(const Point<T> & u, const Point<T> & v) : u(u), v(v)
	{

	}

	Segment(const T & ux, const T & uy, const T & vx, const T & vy) : u(ux, uy), v(vx, vy)
	{

	}

	void update()
	{
		if (u.x > v.x || u.x == v.x && u.y > v.y)
			swap(u, v);
	}

	Fraction<T> get() const
	{
		return u.x == v.x ? Fraction<T>(u.y) : Fraction<T>(u.y * (v.x - x) + v.y * (x - u.x), v.x - u.x);
	}

	bool intersect(const Segment & rhs) const
	{
		return seg_seg_intersect(u, v, rhs.u, rhs.v, true);
	}

	bool operator < (const Fraction<T> & rhs) const
	{
		return get() < rhs;
	}

	bool operator < (const Segment & rhs) const
	{
		return get() < rhs.get();
	}

	bool operator == (const Segment & rhs) const
	{
		return u == rhs.u && v == rhs.v;
	}

	bool operator != (const Segment & rhs) const
	{
		return u != rhs.u || v != rhs.v;
	}
};

template <class T>
class Event
{
public:
	T x, y;
	int i;
	bool f;

	Event(void) : x(0), y(0), i(0), f(false)
	{

	}

	Event(const T & x, const T & y, const int & i, const bool & f) : x(x), y(y), i(i), f(f)
	{

	}

	bool operator < (const Event & rhs) const
	{
		if (x != rhs.x)
			return x < rhs.x;
		else if (y != rhs.y)
			return y < rhs.y;
		else
			return f > rhs.f;
	}
};

const int maxn = 100000;

int n;
Segment<long long> smt[maxn];

bool answer(void)
{
	vector<Event<long long> > evt;
	for (int i = 0; i < n; i++)
	{
		evt.emplace_back(smt[i].u.x, smt[i].u.y, i, true);
		evt.emplace_back(smt[i].v.x, smt[i].v.y, i, false);
	}
	sort(evt.begin(), evt.end());
	set<Segment<long long> > s;
	for (const auto & q : evt)
	{
		if (q.f)
		{
			auto itr = s.lower_bound(smt[q.i]);
			if (itr != s.end() && itr->intersect(smt[q.i]))
				return false;
			if (itr != s.begin() && (--itr)->intersect(smt[q.i]))
				return false;
			s.insert(smt[q.i]);
		}
		else
		{
			auto itr = s.find(smt[q.i]);
			if (itr != s.begin() && itr != s.end())
			{
				auto dtr = itr, utr = itr;
				dtr--, utr++;
				if (dtr->intersect(*utr))
					return false;
			}
			s.erase(itr);
		}
	}

	return true;
}
