#pragma once

#include "Vector3.h"
#include <limits>

class Ray
{
private:
	Vector3 m_v3Origin;
	Vector3 m_v3Direction;
	float m_MaxLength;
public:
#pragma region Constructors/Destructors
	Ray();
	Ray(const Ray& a_Ray);
	//Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction);
	Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_maxLength = std::numeric_limits<float>::max());
	~Ray();
#pragma endregion
#pragma region Getters
	Vector3 Origin() const { return m_v3Origin; }
	Vector3 Direction() const { return m_v3Direction; }
#pragma endregion
	Vector3 PointAt(float a_distance);
	float IntersectSphere(const Vector3& a_center, const float a_radius);
};