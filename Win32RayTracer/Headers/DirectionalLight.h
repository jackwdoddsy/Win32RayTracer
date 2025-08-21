#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing);
	virtual ~DirectionalLight();
	Vector3 CalculateLighting(const Vector3& a_hitPos, const Vector3& a_eyePos, const Vector3& a_normal) const override;
	void SetDirection(const Vector3& a_direction, const Vector3& a_up = Vector3(0.f, 1.f, 0.f));
	Vector3 GetDirection() const;
};