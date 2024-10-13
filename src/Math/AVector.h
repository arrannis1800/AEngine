#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <string>

struct AVector2
{
	AVector2() : x(0.0f), y(0.0f) {}

	AVector2(float x, float y) : x(x), y(y) {}

	float x;
	float y;
};

struct AVector3
{
	AVector3() : x(0.0f), y(0.0f), z(0.0f) {}

	AVector3(float x, float y, float z) : x(x), y(y), z(z) {}

	AVector3& operator*=(float t)
	{
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	float x;
	float y;
	float z;
};

struct AVector4
{
	AVector4() : x(0.0f), y(0.0f), z(0.0f), a(0.0f) {}

	AVector4(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}

	AVector4& operator*=(float t)
	{
		x *= t;
		y *= t;
		z *= t;
		a *= t;
		return *this;
	}

	float x;
	float y;
	float z;
	float a;
};

inline AVector4 operator+(const AVector4& u, const AVector4& v) {
	return AVector4(u.x + v.x, u.y + v.y, u.z + v.z, u.a + v.a);
}

inline AVector4 operator*(float t, const AVector4& v) {
	return AVector4(t * v.x, t * v.y, t * v.z, t * v.a);
}

inline AVector4 operator*(const AVector4& v, float t) {
	return t * v;
}

#endif