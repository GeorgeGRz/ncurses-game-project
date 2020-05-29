#ifndef __Vector2D_H__
#define __Vector2D_H__

#include <cmath>

template <class T>
class Vector2D
{
public:
	T x, y;

	Vector2D() : x(0), y(0) {}
	Vector2D(T x, T y) : x(x), y(y) {}
	Vector2D(const Vector2D &v) : x(v.x), y(v.y) {}

	Vector2D &operator=(const Vector2D &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2D operator+(Vector2D &v)
	{
		return Vector2D(x + v.x, y + v.y);
	}
	Vector2D operator-(Vector2D &v)
	{
		return Vector2D(x - v.x, y - v.y);
	}

	Vector2D &operator+=(Vector2D &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2D &operator-=(Vector2D &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2D operator+(double s)
	{
		return Vector2D(x + s, y + s);
	}
	Vector2D operator-(double s)
	{
		return Vector2D(x - s, y - s);
	}
	Vector2D operator*(double s)
	{
		return Vector2D(x * s, y * s);
	}
	Vector2D operator/(double s)
	{
		return Vector2D(x / s, y / s);
	}

	Vector2D &operator+=(double s)
	{
		x += s;
		y += s;
		return *this;
	}
	Vector2D &operator-=(double s)
	{
		x -= s;
		y -= s;
		return *this;
	}
	Vector2D &operator*=(double s)
	{
		x *= s;
		y *= s;
		return *this;
	}
	Vector2D &operator/=(double s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	void set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	void rotate(double deg)
	{
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}

	Vector2D &normalize()
	{
		if (length() == 0)
			return *this;
		*this *= (1.0 / length());
		return *this;
	}

	float dist(Vector2D v) const
	{
		Vector2D d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const
	{
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length)
	{
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	Vector2D ortho() const
	{
		return Vector2D(y, -x);
	}

	static float dot(Vector2D v1, Vector2D v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(Vector2D v1, Vector2D v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
};

typedef Vector2D<int> Vector2Di;
typedef Vector2D<double> Vector2Dd;

#endif