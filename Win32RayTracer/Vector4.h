#pragma once

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
#pragma region Constructors/Destructors
	Vector4();
	Vector4(const float a_x, const float a_y, const float a_z, const float a_w);
	Vector4(const Vector4& a_v4);
	~Vector4();
#pragma endregion
#pragma region Operator Overloads
	bool operator == (const Vector4& a_v4) const;
	bool operator != (const Vector4& a_v4) const;
	const Vector4 operator - () const;
	Vector4 operator - (const Vector4& a_v4) const;
	Vector4 operator + (const Vector4& a_v4) const;
	Vector4 operator + (const float a_scalar) const;
	Vector4 operator * (const float& a_scalar) const;
	float Dot(const Vector4& a_v4) const;
	friend float Dot(const Vector4& a_v4A, const Vector4& a_v4B);
	float Length() const;
	void Normalize();
#pragma endregion
};