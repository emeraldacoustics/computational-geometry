template <class T>
Point<T> bary(const Point<T> & A, const T & a, const Point<T> & B, const T & b, const Point<T> & C, const T & c)
{
	return (A * a + B * b + C * c) / (a + b + c);
}

template <class T>
Point<T> center_of_gravity(const Point<T> & A, const Point<T> & B, const Point<T> & C)
{
	return (A + B + C) / 3; // bary(A, 1, B, 1, C, 1);
}

template <class T>
Point<T> incenter(const Point<T> & A, const Point<T> & B, const Point<T> & C)
{
	return bary(A, B.distance(C), B, C.distance(A), C, A.distance(B));
}

template <class T>
Point<T> circumcenter(const Point<T> & A, const Point<T> & B, const Point<T> & C)
{
	T a = B.distance2(C), b = C.distance2(A), c = A.distance2(B);
	return bary(A, a * (b + c - a), B, b * (c + a - b), C, c * (a + b - c));
}

template <class T>
Point<T> orthocenter(const Point<T> & A, const Point<T> & B, const Point<T> & C)
{
	T a = B.distance2(C), b = C.distance2(A), c = A.distance2(B), p = (a + b + c) / 2;
	return bary(A, (p - b) * (p - c), B, (p - c) * (p - a), C, (p - a) * (p - b));
}

template <class T>
Point<T> excenter(const Point<T> & A, const Point<T> & B, const Point<T> & C)
{
	return bary(A, -B.distance2(C), B, C.distance2(A), C, A.distance2(B)); // excenter of A
}

