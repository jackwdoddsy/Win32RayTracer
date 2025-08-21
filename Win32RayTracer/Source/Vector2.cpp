#include "Vector2.h"

Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(const float a_x, const float a_y)
{
	x = a_x;
	y = a_y;
}

Vector2::Vector2(const Vector2& a_v2)
{
	x = a_v2.x;
	y = a_v2.y;
}

Vector2::~Vector2()
{

}

bool Vector2::operator==(const Vector2& a_v2) const
{
	return (x == a_v2.x && y == a_v2.y);
}

bool Vector2::operator!=(const Vector2& a_v2) const
{
	return (x != a_v2.x || y != a_v2.y);
}

const Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& a_v2) const
{
	return Vector2(x + a_v2.x, y + a_v2.y);
}

float Vector2::Dot(const Vector2& a_v2) const
{
	return (x * a_v2.x + y * a_v2.y);
}

float Dot(const Vector2& a_v2A, const Vector2& a_v2B)
{
	return a_v2A.Dot(a_v2B);
}