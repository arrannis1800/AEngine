#include "Math/Mat4.h"

AMat4x4 AMat4x4::Translate(AVector3 vec3)
{
    m_Mat[3].x += vec3.x;
    m_Mat[3].y += vec3.y;
    m_Mat[3].z += vec3.z;

    return *this;
}

AMat4x4 AMat4x4::Rotate(float angle, AVector3 vec3)
{
	return AMat4x4();
}

AMat4x4 AMat4x4::Scale(AVector3 vec3)
{
    m_Mat[0].x *= vec3.x;
    m_Mat[1].y *= vec3.y;
    m_Mat[2].z *= vec3.z;
    return *this;
}

const float* AMat4x4::GetPtr() const
{
    return &m_Mat[0].x;
}

AMat4x4 AMat4x4::Ortho(float left, float right, float bottom, float top, float near, float far)
{

    AMat4x4 ortho;

    ortho.m_Mat[0] = { 2.0f / (right - left), 0.0f, 0.0f, 0.0f };
    ortho.m_Mat[1] = { 0.0f, 2.0f / (top - bottom), 0.0f, 0.0f };
    ortho.m_Mat[2] = { 0.0f, 0.0f, -2.0f / (far - near), 0.0f };
    ortho.m_Mat[3] = {
        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        -(far + near) / (far - near),
        1.0f
    };

    return ortho;
}
