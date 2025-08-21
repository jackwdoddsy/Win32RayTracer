#include "Matrix4.h"
#include "Vector3.h"
#include <cassert>
#include <math.h>

Matrix4::Matrix4() : m_11(1.f), m_21(0.f), m_31(0.f), m_41(0.f),
					 m_12(0.f), m_22(1.f), m_32(0.f), m_42(0.f),
					 m_13(0.f), m_23(0.f), m_33(1.f), m_43(0.f),
					 m_14(0.f), m_24(0.f), m_34(0.f), m_44(1.f)
{

}

Matrix4::Matrix4(const float* a_mat) :  m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]), m_41(a_mat[3]),
										m_12(a_mat[4]), m_22(a_mat[5]), m_32(a_mat[6]), m_42(a_mat[7]),
										m_13(a_mat[8]), m_23(a_mat[9]), m_33(a_mat[10]), m_43(a_mat[11]),
										m_14(a_mat[12]), m_24(a_mat[13]), m_34(a_mat[14]), m_44(a_mat[15])
{

}

Matrix4::Matrix4(float a_m11, float a_m21, float a_m31, float a_m41,
				 float a_m12, float a_m22, float a_m32, float a_m42,
				 float a_m13, float a_m23, float a_m33, float a_m43,
				 float a_m14, float a_m24, float a_m34, float a_m44) : 
				m_11(a_m11), m_21(a_m21), m_31(a_m31), m_41(a_m41),
				m_12(a_m12), m_22(a_m22), m_32(a_m32), m_42(a_m42),
				m_13(a_m13), m_23(a_m23), m_33(a_m33), m_43(a_m43),
				m_14(a_m14), m_24(a_m24), m_34(a_m34), m_44(a_m44)
{

}

Matrix4::Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_wAxis) :
	m_xAxis(a_xAxis), m_yAxis(a_yAxis), m_zAxis(a_zAxis), m_wAxis(a_wAxis)
{

}

Matrix4::Matrix4(const Matrix4& a_m4) :
	m_11(a_m4.m_11), m_21(a_m4.m_21), m_31(a_m4.m_31), m_41(a_m4.m_41),
	m_12(a_m4.m_12), m_22(a_m4.m_22), m_32(a_m4.m_32), m_42(a_m4.m_42),
	m_13(a_m4.m_13), m_23(a_m4.m_23), m_33(a_m4.m_33), m_43(a_m4.m_43),
	m_14(a_m4.m_14), m_24(a_m4.m_24), m_34(a_m4.m_34), m_44(a_m4.m_44)
{

}

Matrix4::~Matrix4()
{

}

float& Matrix4::operator() (int a_row, int a_col)
{
	assert(a_col >= 0 && a_col < 4);
	assert(a_row >= 0 && a_row < 4);
	return m[a_col][a_row];//potential source of errors
}

float Matrix4::operator() (int a_iRow, int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return m[a_iCol][a_iRow];//potential source of errors
}

void Matrix4::SetColumn(int a_iCol, const Vector4& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x;
	m[a_iCol][1] = a_vCol.y;
	m[a_iCol][2] = a_vCol.z;
	m[a_iCol][3] = a_vCol.w;
}

void Matrix4::SetColumn(int a_iCol, const Vector3& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x;
	m[a_iCol][1] = a_vCol.y;
	m[a_iCol][2] = a_vCol.z;
}

Vector4 Matrix4::GetColumn(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	return Vector4(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2], m[a_iCol][3]);
}

bool Matrix4::operator == (const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return false; }
	if (m_21 != a_m4.m_21) { return false; }
	if (m_31 != a_m4.m_31) { return false; }
	if (m_41 != a_m4.m_41) { return false; }
	if (m_12 != a_m4.m_12) { return false; }
	if (m_22 != a_m4.m_22) { return false; }
	if (m_32 != a_m4.m_32) { return false; }
	if (m_42 != a_m4.m_42) { return false; }
	if (m_13 != a_m4.m_13) { return false; }
	if (m_23 != a_m4.m_23) { return false; }
	if (m_33 != a_m4.m_33) { return false; }
	if (m_43 != a_m4.m_43) { return false; }
	if (m_14 != a_m4.m_14) { return false; }
	if (m_24 != a_m4.m_24) { return false; }
	if (m_34 != a_m4.m_34) { return false; }
	if (m_44 != a_m4.m_44) { return false; }
	return true;
}

bool Matrix4::operator != (const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return true; }
	if (m_21 != a_m4.m_21) { return true; }
	if (m_31 != a_m4.m_31) { return true; }
	if (m_41 != a_m4.m_41) { return true; }
	if (m_12 != a_m4.m_12) { return true; }
	if (m_22 != a_m4.m_22) { return true; }
	if (m_32 != a_m4.m_32) { return true; }
	if (m_42 != a_m4.m_42) { return true; }
	if (m_13 != a_m4.m_13) { return true; }
	if (m_23 != a_m4.m_23) { return true; }
	if (m_33 != a_m4.m_33) { return true; }
	if (m_43 != a_m4.m_43) { return true; }
	if (m_14 != a_m4.m_14) { return true; }
	if (m_24 != a_m4.m_24) { return true; }
	if (m_34 != a_m4.m_34) { return true; }
	if (m_44 != a_m4.m_44) { return true; }
	return false;
}

Matrix4 Matrix4::operator+(const Matrix4& a_m4) const
{
	return Matrix4( m_11 + a_m4.m_11, m_21 + a_m4.m_21, m_31 + a_m4.m_31, m_41 + a_m4.m_41,
					m_12 + a_m4.m_12, m_22 + a_m4.m_22, m_32 + a_m4.m_32, m_42 + a_m4.m_42,
					m_13 + a_m4.m_13, m_23 + a_m4.m_23, m_33 + a_m4.m_33, m_43 + a_m4.m_43,
					m_14 + a_m4.m_14, m_24 + a_m4.m_24, m_34 + a_m4.m_34, m_44 + a_m4.m_44 );
}

const Matrix4& Matrix4::operator+=(const Matrix4& a_m4)
{
	m_11 += a_m4.m_11;
	m_21 += a_m4.m_21;
	m_31 += a_m4.m_31;
	m_41 += a_m4.m_41;
	m_12 += a_m4.m_12;
	m_22 += a_m4.m_22;
	m_32 += a_m4.m_32;
	m_42 += a_m4.m_42;
	m_13 += a_m4.m_13;
	m_23 += a_m4.m_23;
	m_33 += a_m4.m_33;
	m_43 += a_m4.m_43;
	m_14 += a_m4.m_14;
	m_24 += a_m4.m_24;
	m_34 += a_m4.m_34;
	m_44 += a_m4.m_44;
	return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& a_m4) const
{
	return Matrix4( m_11 - a_m4.m_11, m_21 - a_m4.m_21, m_31 - a_m4.m_31, m_41 - a_m4.m_41,
					m_12 - a_m4.m_12, m_22 - a_m4.m_22, m_32 - a_m4.m_32, m_42 - a_m4.m_42,
					m_13 - a_m4.m_13, m_23 - a_m4.m_23, m_33 - a_m4.m_33, m_43 - a_m4.m_43,
					m_14 - a_m4.m_14, m_24 - a_m4.m_24, m_34 - a_m4.m_34, m_44 - a_m4.m_44);
}

const Matrix4& Matrix4::operator-=(const Matrix4& a_m4)
{
	m_11 -= a_m4.m_11;
	m_21 -= a_m4.m_21;
	m_31 -= a_m4.m_31;
	m_41 -= a_m4.m_41;
	m_12 -= a_m4.m_12;
	m_22 -= a_m4.m_22;
	m_32 -= a_m4.m_32;
	m_42 -= a_m4.m_42;
	m_13 -= a_m4.m_13;
	m_23 -= a_m4.m_23;
	m_33 -= a_m4.m_33;
	m_43 -= a_m4.m_43;
	m_14 -= a_m4.m_14;
	m_24 -= a_m4.m_24;
	m_34 -= a_m4.m_34;
	m_44 -= a_m4.m_44;
	return *this;
}

Matrix4 Matrix4::operator*(const float a_fScalar) const
{
	return Matrix4( m_11 * a_fScalar, m_21 * a_fScalar, m_31 * a_fScalar, m_41 * a_fScalar,
					m_12 * a_fScalar, m_22 * a_fScalar, m_32 * a_fScalar, m_42 * a_fScalar,
					m_13 * a_fScalar, m_23 * a_fScalar, m_33 * a_fScalar, m_43 * a_fScalar,
					m_14 * a_fScalar, m_24 * a_fScalar, m_34 * a_fScalar, m_44 * a_fScalar);
}

const Matrix4& Matrix4::operator*=(float a_fScalar)
{
	m_11 *= a_fScalar;
	m_21 *= a_fScalar;
	m_31 *= a_fScalar;
	m_41 *= a_fScalar;
	m_12 *= a_fScalar;
	m_22 *= a_fScalar;
	m_32 *= a_fScalar;
	m_42 *= a_fScalar;
	m_13 *= a_fScalar;
	m_23 *= a_fScalar;
	m_33 *= a_fScalar;
	m_43 *= a_fScalar;
	m_14 *= a_fScalar;
	m_24 *= a_fScalar;
	m_34 *= a_fScalar;
	m_44 *= a_fScalar;
	return *this;
}

Vector4 Matrix4::operator*(const Vector4& a_v4) const
{
	float x = m_11 * a_v4.x + m_21 * a_v4.y + m_31 * a_v4.z + m_41 * a_v4.w;
	float y = m_12 * a_v4.x + m_22 * a_v4.y + m_32 * a_v4.z + m_42 * a_v4.w;
	float z = m_13 * a_v4.x + m_23 * a_v4.y + m_33 * a_v4.z + m_43 * a_v4.w;
	float w = m_14 * a_v4.x + m_24 * a_v4.y + m_34 * a_v4.z + m_44 * a_v4.w;

	return Vector4(x, y, z, w);
}

Matrix4 Matrix4::operator*(const Matrix4& a_m4) const
{
	return Matrix4( m_11 * a_m4.m_11 + m_21 * a_m4.m_12 + m_31 * a_m4.m_13 + m_41 * a_m4.m_14,
					m_11 * a_m4.m_21 + m_21 * a_m4.m_22 + m_31 * a_m4.m_23 + m_41 * a_m4.m_24,
					m_11 * a_m4.m_31 + m_21 * a_m4.m_32 + m_31 * a_m4.m_33 + m_41 * a_m4.m_34,
					m_11 * a_m4.m_41 + m_21 * a_m4.m_42 + m_31 * a_m4.m_43 + m_41 * a_m4.m_44,

					m_12 * a_m4.m_11 + m_22 * a_m4.m_12 + m_32 * a_m4.m_13 + m_42 * a_m4.m_14,
					m_12 * a_m4.m_21 + m_22 * a_m4.m_22 + m_32 * a_m4.m_23 + m_42 * a_m4.m_24,
					m_12 * a_m4.m_31 + m_22 * a_m4.m_32 + m_32 * a_m4.m_33 + m_42 * a_m4.m_34,
					m_12 * a_m4.m_41 + m_22 * a_m4.m_42 + m_32 * a_m4.m_43 + m_42 * a_m4.m_44,

					m_13 * a_m4.m_11 + m_23 * a_m4.m_12 + m_33 * a_m4.m_13 + m_43 * a_m4.m_14,
					m_13 * a_m4.m_21 + m_23 * a_m4.m_22 + m_33 * a_m4.m_23 + m_43 * a_m4.m_24,
					m_13 * a_m4.m_31 + m_23 * a_m4.m_32 + m_33 * a_m4.m_33 + m_43 * a_m4.m_34,
					m_13 * a_m4.m_41 + m_23 * a_m4.m_42 + m_33 * a_m4.m_43 + m_43 * a_m4.m_44,

					m_14 * a_m4.m_11 + m_24 * a_m4.m_12 + m_34 * a_m4.m_13 + m_44 * a_m4.m_14,
					m_14 * a_m4.m_21 + m_24 * a_m4.m_22 + m_34 * a_m4.m_23 + m_44 * a_m4.m_24,
					m_14 * a_m4.m_31 + m_24 * a_m4.m_32 + m_34 * a_m4.m_33 + m_44 * a_m4.m_34,
					m_14 * a_m4.m_41 + m_24 * a_m4.m_42 + m_34 * a_m4.m_43 + m_44 * a_m4.m_44);
}

const Matrix4& Matrix4::operator*=(const Matrix4& a_m4)
{
	*this = (*this) * a_m4;
	return *this;
}

void Matrix4::Transpose()
{
	float k;
	k = m_12;
	m_12 = m_21;
	m_21 = k;
	k = m_13;
	m_13 = m_31;
	m_31 = k;
	k = m_14;
	m_14 = m_41;
	m_41 = k;
	k = m_23;
	m_23 = m_32;
	m_32 = k;
	k = m_24;
	m_24 = m_42;
	m_42 = k;
	k = m_34;
	m_34 = m_43;
	m_43 = k;
}

Matrix4 Matrix4::GetTranspose() const
{
	Matrix4 tmp = *this;
	tmp.Transpose();
	return tmp;
}

void Matrix4::Scale(const Vector4& a_v4)
{
	m_11 = a_v4.x;
	m_21 = 0.f;
	m_31 = 0.f;
	m_41 = 0.f;
	m_12 = 0.f;
	m_22 = a_v4.y;
	m_32 = 0.f;
	m_42 = 0.f;
	m_13 = 0.f;
	m_23 = 0.f;
	m_33 = a_v4.z;
	m_43 = 0.f;
	m_14 = 0.f;
	m_24 = 0.f;
	m_34 = 0.f;
	m_44 = a_v4.w;
}

void Matrix4::Scale(const Vector3& a_v3)
{
	m_11 = a_v3.x;
	m_21 = 0.f;
	m_31 = 0.f;
	m_41 = 0.f;
	m_12 = 0.f;
	m_22 = a_v3.y;
	m_32 = 0.f;
	m_42 = 0.f;
	m_13 = 0.f;
	m_23 = 0.f;
	m_33 = a_v3.z;
	m_43 = 0.f;
	m_14 = 0.f;
	m_24 = 0.f;
	m_34 = 0.f;
	m_44 = 0.f;
}

void Matrix4::Scale(float a_fScalar)
{
	Scale(Vector4(a_fScalar, a_fScalar, a_fScalar, a_fScalar));
}

void Matrix4::Shear(float xy, float xz, float yx, float yz, float zx, float zy)
{
	m_11 = 1.f; m_12 = xy;  m_13 = xz;  m_14 = 0.f;
	m_21 = yx;  m_22 = 1.f; m_23 = yz;  m_24 = 0.f;
	m_31 = zx;  m_32 = zy;  m_33 = 1.f; m_34 = 0.f;
	m_41 = 0.f; m_42 = 0.f; m_43 = 0.f; m_44 = 1.f;
}

void Matrix4::Identity()
{
	m_11 = 1.f;
	m_21 = 0.f;
	m_31 = 0.f;
	m_41 = 0.f;
	m_12 = 0.f;
	m_22 = 1.f;
	m_32 = 0.f;
	m_42 = 0.f;
	m_13 = 0.f;
	m_23 = 0.f;
	m_33 = 1.f;
	m_43 = 0.f;
	m_14 = 0.f;
	m_24 = 0.f;
	m_34 = 0.f;
	m_44 = 1.f;
}

float Matrix4::Determinant() const
{
	float fA = m_11 * (m_22 * (m_33 * m_44 - m_34 * m_43) +
					   m_23 * (m_34 * m_42 - m_32 * m_44) +
					   m_24 * (m_32 * m_43 - m_33 * m_42));

	float fB = m_12 * (m_21 * (m_33 * m_44 - m_34 * m_43) +
					   m_23 * (m_34 * m_41 - m_31 * m_44) +
					   m_24 * (m_31 * m_43 - m_33 * m_41));

	float fC = m_13 * (m_21 * (m_32 * m_44 - m_34 * m_42) +
					   m_22 * (m_34 * m_41 - m_31 * m_44) +
					   m_24 * (m_31 * m_42 - m_32 * m_41));

	float fD = m_14 * (m_21 * (m_32 * m_43 - m_33 * m_42) +
					   m_22 * (m_33 * m_41 - m_31 * m_43) +
					   m_23 * (m_31 * m_42 - m_32 * m_41));

	return fA - fB + fC - fD;
}

Matrix4 Matrix4::Inverse() const
{
	const float fDet = Determinant();
	if (fDet != 0.0f)
	{
		const float fInvDet = 1.f / fDet;
		Matrix4 mat;
		mat.m_11 = (m_22 * (m_33 * m_44 - m_34 * m_43) +
					m_23 * (m_34 * m_42 - m_32 * m_44) +
					m_24 * (m_32 * m_43 - m_33 * m_42)) * fInvDet;

		mat.m_21 = (m_21 * (m_33 * m_44 - m_34 * m_43) +
					m_23 * (m_34 * m_41 - m_31 * m_44) +
					m_24 * (m_31 * m_43 - m_33 * m_41)) * -fInvDet;

		mat.m_31 = (m_21 * (m_32 * m_44 - m_34 * m_42) +
					m_22 * (m_34 * m_41 - m_31 * m_44) +
					m_24 * (m_31 * m_42 - m_32 * m_41)) * fInvDet;

		mat.m_41 = (m_21 * (m_32 * m_43 - m_33 * m_42) +
					m_22 * (m_33 * m_41 - m_31 * m_43) +
					m_23 * (m_31 * m_42 - m_32 * m_41)) * -fInvDet;

		mat.m_12 = (m_12 * (m_33 * m_44 - m_34 * m_43) +
					m_13 * (m_34 * m_42 - m_32 * m_44) +
					m_14 * (m_32 * m_43 - m_33 * m_42)) * -fInvDet;

		mat.m_22 = (m_11 * (m_33 * m_44 - m_34 * m_43) +
					m_13 * (m_34 * m_41 - m_31 * m_44) +
					m_14 * (m_31 * m_43 - m_33 * m_41)) * fInvDet;

		mat.m_32 = (m_11 * (m_32 * m_44 - m_34 * m_42) +
					m_12 * (m_34 * m_41 - m_31 * m_44) +
					m_14 * (m_31 * m_42 - m_32 * m_41)) * -fInvDet;

		mat.m_42 = (m_11 * (m_32 * m_43 - m_33 * m_42) +
					m_12 * (m_33 * m_41 - m_31 * m_43) +
					m_13 * (m_31 * m_42 - m_32 * m_41)) * fInvDet;

		mat.m_13 = (m_12 * (m_23 * m_44 - m_24 * m_43) +
					m_13 * (m_24 * m_42 - m_22 * m_44) +
					m_14 * (m_22 * m_43 - m_23 * m_42)) * fInvDet;

		mat.m_23 = (m_11 * (m_23 * m_44 - m_24 * m_43) +
					m_13 * (m_24 * m_41 - m_21 * m_44) +
					m_14 * (m_21 * m_43 - m_23 * m_41)) * -fInvDet;

		mat.m_33 = (m_11 * (m_22 * m_44 - m_24 * m_42) +
					m_12 * (m_24 * m_41 - m_21 * m_44) +
					m_14 * (m_21 * m_42 - m_22 * m_41)) * fInvDet;

		mat.m_43 = (m_11 * (m_22 * m_43 - m_23 * m_42) +
					m_12 * (m_23 * m_41 - m_21 * m_43) +
					m_13 * (m_21 * m_42 - m_22 * m_41)) * -fInvDet;

		mat.m_14 = (m_12 * (m_23 * m_34 - m_24 * m_33) +
					m_13 * (m_24 * m_32 - m_22 * m_34) +
					m_14 * (m_22 * m_33 - m_23 * m_32)) * -fInvDet;

		mat.m_24 = (m_11 * (m_23 * m_34 - m_24 * m_33) +
					m_13 * (m_24 * m_31 - m_21 * m_34) +
					m_14 * (m_21 * m_33 - m_23 * m_31)) * fInvDet;

		mat.m_34 = (m_11 * (m_22 * m_34 - m_24 * m_32) +
					m_12 * (m_24 * m_31 - m_21 * m_34) +
					m_14 * (m_21 * m_32 - m_22 * m_31)) * -fInvDet;

		mat.m_44 = (m_11 * (m_22 * m_33 - m_23 * m_32) +
					m_12 * (m_23 * m_31 - m_21 * m_33) +
					m_13 * (m_21 * m_32 - m_22 * m_31)) * fInvDet;
		return mat;
	}
	else
	{
		return Matrix4();
	}
}

bool Matrix4::Perspective(float fRadFovY, float fAspectRatio, float fZNear, float fZFar)
{
	float tanHalfFov = tanf(fRadFovY * 0.5f);
	if (fabsf(fZFar - fZNear) < 0.01f)
	{
		return false;
	}
	const float w = 1.f / (fAspectRatio * tanHalfFov);
	const float h = 1.f / tanHalfFov;

	const float r = 1.f / (fZFar - fZNear);

	m_11 = w;    m_21 = 0.f;    m_31 = 0.f;                         m_41 = 0.f;
	m_12 = 0.f;  m_22 = h;      m_32 = 0.f;                         m_42 = 0.f;
	m_13 = 0.f;  m_23 = 0.f;    m_33 = -(fZFar + fZNear) * r;       m_43 = -1.f;
	m_14 = 0.f;  m_24 = 0.f;    m_34 = -(2.f * fZFar * fZNear) * r; m_44 = 0.f;

	return true;
}

bool Matrix4::Orthographic(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar)
{
	float deltaX = fRight - fLeft;
	float deltaY = fTop - fBottom;
	float deltaZ = fFar - fNear;

	m_11 = 2.f / deltaX; m_21 = 0.f; m_31 = 0.f; m_41 = 0.f;
	m_12 = 0.f; m_22 = 2.f / deltaY; m_32 = 0.f; m_42 = 0.f;
	m_13 = 0.f; m_23 = 0.f; m_33 = -2.f / deltaZ; m_43 = 0.f;
	m_14 = -((fRight + fLeft) / deltaX);
	m_24 = -((fTop + fBottom) / deltaY);
	m_34 = -((fFar + fNear) / deltaZ);
	m_44 = 1.f;

	return true;
}

Vector3 Matrix4::Cross(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return Vector3(
		a_v3A.y * a_v3B.z - a_v3A.z * a_v3B.y,
		a_v3A.z * a_v3B.x - a_v3A.x * a_v3B.z,
		a_v3A.x * a_v3B.y - a_v3A.y * a_v3B.x
	);
}

Matrix4 Matrix4::LookAt(const Vector3& a_v3EyePos, const Vector3& a_v3Target, const Vector3& a_v3Up)
{
	Vector3 vRight;
	Vector3 vForward;
	Vector3 vUp;

	vForward = a_v3Target - a_v3EyePos;
	vForward.Normalize();

	vRight = Cross(a_v3Up, vForward);
	vRight.Normalize();
	vUp = Cross(vForward, vRight);
	vUp.Normalize();
	Matrix4 mat = Matrix4();
	//mat.m_11 = vRight.x;	mat.m_21 = vRight.y;	mat.m_31 = vRight.z;	mat.m_41 = 0.f;
	//mat.m_12 = vUp.x;	mat.m_22 = vUp.y;	mat.m_32 = vUp.z;	mat.m_42 = 0.f;
	//mat.m_13 = -vForward.x;	mat.m_23 = -vForward.y;	mat.m_33 = -vForward.z; mat.m_43 = 0.f;
	//mat.Transpose();
	//mat.m_14 = -Dot(vRight, a_v3EyePos);
	//mat.m_24 = -Dot(vUp, a_v3EyePos);
	//mat.m_34 = Dot(vForward, a_v3EyePos);
	//mat.m_44 = 1.f;
	//mat.Transpose();
	mat.m_11 = vRight.x;     mat.m_21 = vRight.y;     mat.m_31 = vRight.z;     mat.m_41 = -Dot(vRight, a_v3EyePos);
	mat.m_12 = vUp.x;		   mat.m_22 = vUp.y;		mat.m_32 = vUp.z;		 mat.m_42 = -Dot(vUp, a_v3EyePos);
	mat.m_13 = -vForward.x;  mat.m_23 = -vForward.y;  mat.m_33 = -vForward.z;  mat.m_43 = Dot(vForward, a_v3EyePos);
	mat.m_14 = 0.f;          mat.m_24 = 0.f;          mat.m_34 = 0.f;          mat.m_44 = 1.f;

	//mat.m_11 = vRight.x;    mat.m_12 = vRight.y;    mat.m_13 = vRight.z;    mat.m_14 = -Dot(vRight, a_v3EyePos);
	//mat.m_21 = vUp.x;       mat.m_22 = vUp.y;       mat.m_23 = vUp.z;       mat.m_24 = -Dot(vUp, a_v3EyePos);
	//mat.m_31 = -vForward.x; mat.m_32 = -vForward.y; mat.m_33 = -vForward.z; mat.m_34 = Dot(vForward, a_v3EyePos);
	//mat.m_41 = 0.f;         mat.m_42 = 0.f;         mat.m_43 = 0.f;         mat.m_44 = 1.f;

	return mat;
}

void Matrix4::Orthonormalise()
{
	Vector3 XBasis(m_11, m_21, m_31);
	Vector3 YBasis(m_12, m_22, m_32);
	Vector3 ZBasis(m_13, m_23, m_33);

	YBasis = YBasis - (ZBasis * Dot(ZBasis, YBasis));
	YBasis.Normalize();
	XBasis = Cross(YBasis, ZBasis);
	XBasis.Normalize();
	m_11 = XBasis.x; m_21 = XBasis.y; m_31 = XBasis.z;
	m_12 = YBasis.x; m_22 = YBasis.y; m_32 = YBasis.z;
	m_13 = ZBasis.x; m_23 = ZBasis.y; m_33 = ZBasis.z;
}