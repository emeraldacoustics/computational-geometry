template <class T>
class Circle
{
public:
	Point<T> o;
	T r;

	Circle(void) : r(0)
	{

	}

	Circle(const Point<T> & o, const T & r) : o(o), r(r)
	{

	}

	Circle(const T & x, const T & y, const T & r) : o(x, y), r(r)
	{

	}

	Point<T> polar(const T & t) const
	{
		return Point<T>(o.x + r * cos(t), o.y + r * sin(t));
	}

	bool operator < (const Circle & rhs) const
	{
		if (o != rhs.o)
			return xycmp<T>(o, rhs.o);
		else
			return sgn(r - rhs.r) < 0;
	}

	bool operator == (const Circle & rhs) const
	{
		return o == rhs.o && sgn(r - rhs.r) == 0;
	}

	bool operator != (const Circle & rhs) const
	{
		return o != rhs.o || sgn(r - rhs.r) != 0;
	}
};

