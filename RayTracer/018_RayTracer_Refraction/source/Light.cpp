#include <Light.h>

Light::Light() : m_Transform(Matrix4::IDENTITY), m_colorRGB(1.0f, 1.0f, 1.0f)
{
}

Light::Light(const Matrix4& a_transform, const ColorRGB& a_color)
	: m_Transform(a_transform), m_colorRGB(a_color)
{

}

Light::~Light()
{
}

// Get and set lights matrix
Matrix4 Light::GetTransform() const
{
	return m_Transform;
}

void Light::SetTransform(const Matrix4& a_m4)
{
	m_Transform = a_m4;
}

// Get and set the position of the light
Vector3 Light::GetPosition() const
{
	return m_Transform.GetColumn(3).XYZ();
}

void Light::SetPosition(const Vector3& a_v3)
{
	m_Transform.SetColumn(3, a_v3);
}

Vector3 Light::GetDirectionToLight(const Vector3& a_point) const
{
	Vector3 returnVec3 = GetPosition() - a_point;
	returnVec3.Normalize();
	return returnVec3;
}