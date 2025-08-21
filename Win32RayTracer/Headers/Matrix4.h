#pragma once

#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{
private:
	union
	{
		float m[4][4];
		struct
		{
			float m_11, m_12, m_13, m_14;
			float m_21, m_22, m_23, m_24;
			float m_31, m_32, m_33, m_34;
			float m_41, m_42, m_43, m_44;
		};
		struct
		{
			Vector4 m_xAxis;
			Vector4 m_yAxis;
			Vector4 m_zAxis;
			Vector4 m_wAxis;
		};
	};
public:
	Matrix4();
	Matrix4(const float* a_mat);
	Matrix4(float a_m11, float a_m21, float a_m31, float a_m41,
		float a_m12, float a_m22, float a_m32, float a_m42,
		float a_m13, float a_m23, float a_m33, float a_m43,
		float a_m14, float a_m24, float a_m34, float a_m44);
	Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_wAxis);
	Matrix4(const Matrix4& a_m4);
	~Matrix4();

	float& operator() (int a_iCol, int a_iRow);
	float operator() (int a_iColm, int a_iRow) const;

	void SetColumn(int a_iCol, const Vector4& a_vCol);
	void SetColumn(int a_iCol, const Vector3& a_vCol);
	Vector4 GetColumn(int a_iCol) const;

	bool operator == (const Matrix4& a_m4) const;
	bool operator != (const Matrix4& a_m4) const;

	Matrix4 operator + (const Matrix4& a_m4) const;
	const Matrix4& operator += (const Matrix4& a_m4);

	Matrix4 operator - (const Matrix4& a_m4) const;
	const Matrix4& operator -= (const Matrix4& a_m4);

	Matrix4 operator * (const float a_scalar) const;
	const Matrix4& operator *= (const float a_scalar);

	Vector4 operator * (const Vector4& a_v4) const;

	Matrix4 operator * (const Matrix4& a_m4) const;
	const Matrix4& operator *= (const Matrix4& a_m4);

	void Transpose();
	Matrix4 GetTranspose() const;
	void Scale(const float a_scalar);
	void Scale(const Vector4& a_v4);
	void Scale(const Vector3& a_v3);

	void Shear(float xy, float xz, float yx, float yz, float zx, float zy);

	static Vector3 Cross(const Vector3& a_v3A, const Vector3& a_v3B);

	void Identity();

	float Determinant() const;
	Matrix4 Inverse() const;

	bool Perspective(float fRadFovY, float fAspectRatio, float fZNear, float fZFar);
	bool Orthographic(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);
	static Matrix4 LookAt(const Vector3& a_v3EyePos, const Vector3& a_v3Target, const Vector3& a_v3Up);
	void Orthonormalise();
};