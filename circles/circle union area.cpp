template <class T>
class CircleUnionArea
{
public:
	static const int maxn = 1000;

	class Event
	{
	public:
		T a;
		bool f;

		Event(void) : a(0), f(false)
		{

		}

		Event(const T & a, const int & f) : a(a), f(f)
		{

		}

		bool operator < (const Event & rhs) const
		{
			return a < rhs.a;
		}
	};

	int n;
	Circle<T> c[maxn];
	int mtp[maxn];

	CircleUnionArea(void)
	{
		clear();
	}

	void clear(void)
	{
		n = 0;
	}

	void push_back(const Circle<T> & ccl, const int & deg)
	{
		int x = find(c, c + n, ccl) - c;
		if (x == n)
		{
			c[x] = ccl;
			mtp[x] = 0;
			n++;
		}
		mtp[x] += deg;
	}

	vector<T> union_area(void)
	{
		vector<T> ans(n, 0), a(n, 0);
		for (int i = 0; i < n; i++)
		{
			vector<Event> evt;
			for (int j = 0; j < mtp[i]; j++)
			{
				evt.emplace_back(-pi, false);
				evt.emplace_back(pi, true);
			}
			for (int j = 0; j < n; j++)
			{
				if (i == j)
					continue;
				T d = c[i].o.distance(c[j].o);
				if (sgn(d + c[i].r - c[j].r) <= 0)
				{
					for (int k = 0; k < mtp[j]; k++)
					{
						evt.emplace_back(-pi, false);
						evt.emplace_back(pi, true);
					}
				}
				else if (sgn(d + c[j].r - c[i].r) <= 0)
				{

				}
				else
				{
					T alpha = (c[j].o - c[i].o).angle(), phi = interior_angle(c[j].r, c[i].r, d);
					T a = alpha - phi, b = alpha + phi;
					if (sgn(a + pi) < 0)
						a += pi * 2;
					if (sgn(b - pi) > 0)
						b -= pi * 2;
					if (sgn(a - b) > 0)
					{
						for (int k = 0; k < mtp[j]; k++)
						{
							evt.emplace_back(-pi, false);
							evt.emplace_back(b, true);
							evt.emplace_back(a, false);
							evt.emplace_back(pi, true);
						}
					}
					else
					{
						for (int k = 0; k < mtp[j]; k++)
						{
							evt.emplace_back(a, false);
							evt.emplace_back(b, true);
						}
					}
				}
			}
			sort(evt.begin(), evt.end());
			int deg = -1;
			for (const auto & e : evt)
			{
				if (0 <= deg)
				{
					T alpha = e.a - a[deg];
					if (sgn(alpha))
						ans[deg] += c[i].r * c[i].r * (alpha - sin(alpha)) + c[i].polar(a[deg]) * c[i].polar(e.a);
				}
				deg += e.f ? -1 : 1;
				if (0 <= deg)
					a[deg] = e.a;
			}
		}
		for (auto & x : ans)
			x /= 2;
		return ans;
	}
};

