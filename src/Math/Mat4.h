#ifndef MAT4_H
#define MAT4_H

#include "Math/AVector.h"

class AMat4x4
{
public:
	AMat4x4() = default;
	AMat4x4(float value) : m_Mat{ AVector4(value, 0, 0, 0), AVector4(0, value, 0, 0), AVector4(0, 0, value, 0), AVector4(0, 0, 0, value) } {}

	AMat4x4 Translate(AVector3 vec3);
	AMat4x4 Rotate(float angle, AVector3 vec3);
	AMat4x4 Scale(AVector3 vec3);

	const float* GetPtr() const;

	static AMat4x4 Ortho(float left, float right, float bottom, float top, float near, float far);

private:
	AVector4 m_Mat[4];
};

#endif // !MAT4_H
