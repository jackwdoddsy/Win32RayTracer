#include "Light.h"

Light::Light() : m_Transform(Matrix4()), m_colourRGB(1.f, 1.f, 1.f)
{

}

Light::Light(const Matrix4& a_transform, const Vector3& a_colour) : m_Transform(a_transform), m_colourRGB(a_colour)
{

}

Light::~Light()
{

}

Matrix4 Light::GetTransform() const
{
	return m_Transform;
}

void Light::SetTransform(const Matrix4& a_m4)
{
	m_Transform = a_m4;
}

Vector3 Light::GetPosition() const
{
	Vector4 col = m_Transform.GetColumn(3);
	return Vector3(col.x, col.y, col.z);
}

void Light::SetPosition(const Vector3& a_v3)
{
	m_Transform.SetColumn(3, a_v3);
}