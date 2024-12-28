const int maxn = 100000;

int n;
long long x[maxn], y[maxn], r[maxn];

class Query
{
public:
	int i;
	bool f;

	Query(void) : i(0), f(false)
	{

	}

	Query(const int & i, const bool & f) : i(i), f(f)
	{

	}

	long long get_x(void) const
	{
		return x[i] + r[i] * (f ? -1 : 1);
	}

	bool operator < (const Query & rhs) const
	{
		return get_x() < rhs.get_x();
	}
};

class HalfCircle
{
public:
	static long long X;

	int i;
	bool f;

	HalfCircle(void) : i(0), f(false)
	{

	}

	HalfCircle(const int & i, const bool & f) : i(i), f(f)
	{

	}

	long double get_y() const
	{
		return y[i] + sqrtl(r[i] * r[i] - (X - x[i]) * (X - x[i])) * (f ? 1 : -1);
	}

	bool operator < (const HalfCircle & rhs) const
	{
		int s = sgn(get_y() - rhs.get_y());
		return s != 0 ? s < 0 : (i != rhs.i ? i < rhs.i : f < rhs.f);
	}
};

int p[maxn];
Query qry[maxn * 2];
vector<int> E[maxn];
set<HalfCircle> HC;
long long HalfCircle::X = 0;

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T;
	fin >> T;
	for (int TN = 0; TN < T; TN++)
	{
		fin >> n;
		for (int i = 0; i < n; i++)
			fin >> x[i] >> y[i] >> r[i];

		memset(p, -1, sizeof p[0] * n);

		int sz = 0;
		for (int i = 0; i < n; i++)
		{
			qry[sz++] = Query(i, true);
			qry[sz++] = Query(i, false);
		}
		sort(qry, qry + sz);
		for (int k = 0; k < sz; k++)
		{
			HalfCircle::X = qry[k].get_x();
			if (qry[k].f)
			{
				auto itr = HC.lower_bound(HalfCircle(qry[k].i, false));
				if (itr != HC.end())
					p[qry[k].i] = itr->f ? itr->i : p[itr->i];
				HC.emplace(qry[k].i, false);
				HC.emplace(qry[k].i, true);
			}
			else
			{
				HC.erase(HalfCircle(qry[k].i, false));
				HC.erase(HalfCircle(qry[k].i, true));
			}
		}

		queue<int> que;
		for (int i = 0; i < n; i++)
		{
			if (p[i] == -1)
				que.push(i);
			else
				E[p[i]].push_back(i);
		}
		for (; !que.empty(); )
		{
			sz = que.size();
			fout << sz << fendl;
			for (; sz > 0; que.pop(), sz--)
			{
				int u = que.front();
				for (const auto &v : E[u])
					que.push(v);
			}
		}

		HC.clear();
		for (int i = 0; i < n; i++)
			E[i].clear();
	}

	return 0;
}
