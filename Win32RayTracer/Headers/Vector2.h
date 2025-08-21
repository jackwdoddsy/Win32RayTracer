#pragma once

class Vector2
{
public:
	float x;
	float y;
#pragma region Constructors/Destructors
	Vector2();
	Vector2(const float a_x, const float a_y);
	Vector2(const Vector2& a_v2);
	~Vector2();
#pragma endregion
#pragma region Operator Overloads
	bool operator == (const Vector2& a_v2) const;
	bool operator != (const Vector2& a_v2) const;
	const Vector2 operator - () const;
	Vector2 operator + (const Vector2& a_v2) const;
	float Dot(const Vector2& a_v2) const;
	friend float Dot(const Vector2& a_v2A, const Vector2& a_v2B);
#pragma endregion
};