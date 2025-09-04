#include "DirectionalLight.h"
#include <cmath>

DirectionalLight::DirectionalLight()
{
	SetDirection(Vector3(0.f, 0.f, 0.f));
}

DirectionalLight::DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing) : Light(a_transform, a_colour)
{
	SetDirection(a_facing);
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::SetDirection(const Vector3& a_direction, const Vector3& a_up)
{
	m_Transform.SetColumn(2, a_direction);
	m_Transform.SetColumn(1, a_up);
	m_Transform.Orthonormalise();
}

Vector3 DirectionalLight::GetDirection() const
{
	Vector4 dir = m_Transform.GetColumn(2);
	return Vector3(dir.x, dir.y, dir.z);
}

float Max(float a, float b)
{
	return (a > b) ? a : b;
}

Vector3 Reflect(const Vector3& a_v3A, const Vector3& a_v3B)
{
	Vector3 reflect = a_v3A - a_v3B * 2.f * Dot(a_v3A, a_v3B);
	return reflect;
}

Vector3 DirectionalLight::CalculateLighting(const IntersectResponse& a_ir, const Vector3& a_eyePos) const
{
    // Ambient term
    Vector3 ambient = m_colourRGB * 0.1f;

    // Light direction (towards surface)
    Vector3 lightDir = -GetDirection();
    lightDir.Normalize();

    // Diffuse term
    float lightDiffuse = Max(0.f, Dot(lightDir, a_ir.surfaceNormal));
    Vector3 diffuse = a_ir.colour * 0.9f * lightDiffuse;

    // View direction
    Vector3 eyeDir = a_ir.hitPos - a_eyePos;
    eyeDir.Normalize();

    // Reflection of light direction around the normal
    Vector3 reflectionVec = Reflect(-lightDir, a_ir.surfaceNormal);
    reflectionVec.Normalize();

    // Specular term (Phong)
    float specularFactor = std::powf(Max(0.f, Dot(reflectionVec, lightDir)), 64.f);
    Vector3 specular = m_colourRGB * 0.9f * specularFactor;

    return ambient + diffuse + specular;
}