#pragma once

#include "Vector3.h"

class Matrix3
{
private:
	union
	{
		float m[3][3];
		struct
		{
			float m_11, m_12, m_13;
			float m_21, m_22, m_23;
			float m_31, m_32, m_33;
		};
		struct
		{
			Vector3 m_xAxis;
			Vector3 m_yAxis;
			Vector3 m_zAxis;
		};
	};
public:
	static const Matrix3 IDENTITY;
	Matrix3();
	Matrix3(const float* a_mat);
	Matrix3(float a_m11, float a_m21, float a_m31,
		float a_m12, float a_m22, float a_m32,
		float a_m13, float a_m23, float a_m33);
	Matrix3(const Vector3& a_xAxis, const Vector3& a_yAxis, const Vector3& a_zAxis);
	Matrix3(const Matrix3& a_m3);
	~Matrix3();

	float& operator() (int a_iColumn, int a_iRow);
	float operator() (int a_iColumn, int a_iRow) const;

	void SetColumn(int a_iCol, const Vector3& a_vCol);
	Vector3 GetColumn(int a_iCol) const;

	bool operator == (const Matrix3& a_m3) const;
	bool operator != (const Matrix3& a_m3) const;

	Matrix3 operator + (const Matrix3& a_m3) const;
	const Matrix3& operator += (const Matrix3& a_m3);

	Matrix3 operator - (const Matrix3& a_m3) const;
	const Matrix3& operator -= (const Matrix3& a_m3);

	Matrix3 operator * (const float a_scalar) const;
	const Matrix3& operator *= (const float a_scalar);

	Vector3 operator * (const Vector3& a_v3) const;

	Matrix3 operator * (const Matrix3& a_m3) const;
	const Matrix3& operator *= (const Matrix3& a_m3);

	void Transpose();
	Matrix3 GetTranspose() const;
	void Scale(const float a_scalar);
	void Scale(const Vector3& a_v3);

	void Identity();

	float Determinant()const;

	Matrix3 Inverse() const;
};