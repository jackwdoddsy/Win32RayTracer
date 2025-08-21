#include "Matrix4.h"
#include "Vector3.h"

class Light
{
public:
	Light();
	Light(const Matrix4& a_transform, const Vector3& a_colour);
	virtual ~Light();
	virtual Vector3 CalculateLighting(const Vector3& a_hitPoint, const Vector3& a_eyePos, const Vector3& a_normal) const = 0;
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);
	const Vector3& GetColour() const { return m_colourRGB; }
	void SetColour(const Vector3& a_Colour) { m_colourRGB = a_Colour; }
protected:
	Matrix4 m_Transform;
	Vector3 m_colourRGB;
};