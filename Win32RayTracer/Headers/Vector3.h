#pragma once

class Vector3
{
public:
	float x;
	float y;
	float z;
#pragma region Constructors/Destructors
	Vector3();
	Vector3(const float a_x, const float a_y, const float a_z);
	Vector3(const Vector3& a_v3);
	~Vector3();
#pragma endregion
#pragma region Operator Overloads
	bool operator == (const Vector3& a_v3) const;
	bool operator != (const Vector3& a_v3) const;
	const Vector3 operator - () const;
	Vector3 operator - (const Vector3& a_v3) const;
	Vector3 operator + (const Vector3& a_v3) const;
	Vector3 operator + (const float a_scalar) const;
	Vector3 operator * (const float& a_scalar) const;
	float Dot(const Vector3& a_v3) const;
	friend float Dot(const Vector3& a_v3A, const Vector3& a_v3B);
	Vector3 Cross(const Vector3& a_v3A, const Vector3& a_v3B) const;
	float Length() const;
	void Normalize();
	friend Vector3 Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t);
#pragma endregion
};

using ColourRGB = Vector3;