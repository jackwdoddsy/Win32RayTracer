#include "Ray.h"
#include <math.h>

Ray::Ray() : m_v3Origin(0.f, 0.f, 0.f),
			 m_v3Direction(0.f, 0.f, 1.f),
			 m_MaxLength(std::numeric_limits<float>::max())
{

}

//Ray::Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction) : m_v3Origin(a_v3Origin),
//																	m_v3Direction(a_v3Direction),
//																	m_MaxLength(1000000.f)
//{
//	if (m_v3Direction.Length() > 1.f)
//	{
//		m_v3Direction.Normalize();
//	}
//}

Ray::Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_maxLength) : m_v3Origin(a_v3Origin),
																					   m_v3Direction(a_v3Direction),
																					   m_MaxLength(a_maxLength)
{
	if (m_v3Direction.Length() > 1.f)
	{
		m_v3Direction.Normalize();
	}
}

Ray::Ray(const Ray& a_Ray) : m_v3Origin(a_Ray.m_v3Origin),
							 m_v3Direction(a_Ray.m_v3Direction),
							 m_MaxLength(a_Ray.m_MaxLength)
{

}

Ray::~Ray()
{

}

Vector3 Ray::PointAt(float a_distance)
{
	if (a_distance > m_MaxLength)
	{
		a_distance = m_MaxLength;
	}
	return m_v3Origin + (m_v3Direction * a_distance);
}

float Ray::IntersectSphere(const Vector3& a_center, const float a_radius)
{
	Vector3 OC = m_v3Origin - a_center;
	float b = Dot(OC, m_v3Direction);
	float c = Dot(OC, OC) - a_radius * a_radius;
	float discriminant = b * b - c;
	if (discriminant < 0.f)
	{
		return -1.f;
	}
	else
	{
		return (-b - sqrtf(discriminant));
	}
}