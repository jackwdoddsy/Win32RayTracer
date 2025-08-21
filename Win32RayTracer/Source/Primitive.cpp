#include "Primitive.h"

Primitive::Primitive() : m_Transform(Matrix4()), m_Scale()
{

}

Primitive::~Primitive()
{

}

Matrix4 Primitive::GetTransform() const
{
	return m_Transform;
}

void Primitive::SetTransform(const Matrix4& a_m4)
{
	m_Transform = a_m4;
}

Vector3 Primitive::GetPosition() const
{
	Vector4 pos = m_Transform.GetColumn(3);
	return Vector3(pos.x, pos.y, pos.z);
}

void Primitive::SetPosition(const Vector3& a_v3)
{
	m_Transform.SetColumn(3, a_v3);
}

Vector3 Primitive::GetScale() const
{
	return m_Scale;
}

void Primitive::SetScale(const Vector3& a_v3)
{
    m_Scale = a_v3;
    Vector3 position = GetPosition();
    Matrix4 rotationMatrix = m_Transform;
    rotationMatrix.SetColumn(3, Vector3(0, 0, 0));
    Matrix4 scaleMat;
    scaleMat.Scale(a_v3);
    m_Transform = rotationMatrix * scaleMat;
    m_Transform.SetColumn(3, Vector4(position.x, position.y, position.z, 1.f));
}

void Primitive::SetShear(float xy, float xz, float yx, float yz, float zx, float zy)
{
    Vector3 position = GetPosition();
    Matrix4 rotationScaleMatrix = m_Transform;
    rotationScaleMatrix.SetColumn(3, Vector3(0, 0, 0));
    Matrix4 shearMat;
    shearMat.Shear(xy, xz, yx, yz, zx, zy);
    m_Transform = rotationScaleMatrix * shearMat;
    m_Transform.SetColumn(3, Vector4(position.x, position.y, position.z, 1.f));
}