#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <string>

struct AVector
{
	AVector() : x(0.0f), y(0.0f) {}

	AVector(float x, float y) : x(x), y(y) {}

	float x;
	float y;
};

#endif