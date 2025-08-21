#include "Matrix3.h"
#include <cassert>

//const mat3 mat3::IDENTITY = mat3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);

Matrix3::Matrix3() : m_11(1.f), m_21(0.f), m_31(0.f),
m_12(0.f), m_22(1.f), m_32(0.f),
m_13(0.f), m_23(0.f), m_33(1.f)
{

}

Matrix3::Matrix3(const float* a_mat) : m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]),
m_12(a_mat[3]), m_22(a_mat[4]), m_32(a_mat[5]),
m_13(a_mat[6]), m_23(a_mat[7]), m_33(a_mat[8])
{

}

Matrix3::Matrix3(float a_m11, float a_m21, float a_m31,
	float a_m12, float a_m22, float a_m32,
	float a_m13, float a_m23, float a_m33) :
	m_11(a_m11), m_21(a_m21), m_31(a_m31),
	m_12(a_m12), m_22(a_m22), m_32(a_m32),
	m_13(a_m13), m_23(a_m23), m_33(a_m33)
{

}

Matrix3::Matrix3(const Vector3& a_xAxis, const Vector3& a_yAxis, const Vector3& a_zAxis) :
	m_xAxis(a_xAxis), m_yAxis(a_yAxis), m_zAxis(a_zAxis)
{

}

Matrix3::Matrix3(const Matrix3& a_m3) :
	m_11(a_m3.m_11), m_21(a_m3.m_21), m_31(a_m3.m_31),
	m_12(a_m3.m_12), m_22(a_m3.m_22), m_32(a_m3.m_32),
	m_13(a_m3.m_13), m_23(a_m3.m_23), m_33(a_m3.m_33)
{

}

Matrix3::~Matrix3()
{

}

float& Matrix3::operator() (int a_row, int a_col)
{
	assert(a_col >= 0 && a_col < 3);
	assert(a_row >= 0 && a_row < 3);
	return m[a_col - 1][a_row - 1];//potential source of errors
}

float Matrix3::operator() (int a_iRow, int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 3);
	assert(a_iRow >= 0 && a_iRow < 3);
	return m[a_iCol - 1][a_iRow - 1];//potential source of errors
}

void Matrix3::SetColumn(int a_iCol, const Vector3& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 3);
	m[a_iCol][0] = a_vCol.x;
	m[a_iCol][1] = a_vCol.y;
	m[a_iCol][2] = a_vCol.z;
}

Vector3 Matrix3::GetColumn(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 3);
	return Vector3(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2]);
}

bool Matrix3::operator == (const Matrix3& a_m3) const
{
	if (m_11 != a_m3.m_11) { return false; }
	if (m_21 != a_m3.m_21) { return false; }
	if (m_31 != a_m3.m_31) { return false; }
	if (m_12 != a_m3.m_12) { return false; }
	if (m_22 != a_m3.m_22) { return false; }
	if (m_32 != a_m3.m_32) { return false; }
	if (m_13 != a_m3.m_13) { return false; }
	if (m_23 != a_m3.m_23) { return false; }
	if (m_33 != a_m3.m_33) { return false; }
	return true;
}

bool Matrix3::operator != (const Matrix3& a_m3) const
{
	if (m_11 != a_m3.m_11) { return true; }
	if (m_21 != a_m3.m_21) { return true; }
	if (m_31 != a_m3.m_31) { return true; }
	if (m_12 != a_m3.m_12) { return true; }
	if (m_22 != a_m3.m_22) { return true; }
	if (m_32 != a_m3.m_32) { return true; }
	if (m_13 != a_m3.m_13) { return true; }
	if (m_23 != a_m3.m_23) { return true; }
	if (m_33 != a_m3.m_33) { return true; }
	return false;
}

Matrix3 Matrix3::operator+(const Matrix3& a_m3) const
{
	return Matrix3(m_11 + a_m3.m_11, m_21 + a_m3.m_21, m_31 + a_m3.m_31,
		m_12 + a_m3.m_12, m_22 + a_m3.m_22, m_32 + a_m3.m_32,
		m_13 + a_m3.m_13, m_23 + a_m3.m_23, m_33 + a_m3.m_33);
}

const Matrix3& Matrix3::operator+=(const Matrix3& a_m3)
{
	m_11 += a_m3.m_11;
	m_21 += a_m3.m_21;
	m_31 += a_m3.m_31;
	m_12 += a_m3.m_12;
	m_22 += a_m3.m_22;
	m_32 += a_m3.m_32;
	m_13 += a_m3.m_13;
	m_23 += a_m3.m_23;
	m_33 += a_m3.m_33;
	return *this;
}

Matrix3 Matrix3::operator-(const Matrix3& a_m3) const
{
	return Matrix3(m_11 - a_m3.m_11, m_21 - a_m3.m_21, m_31 - a_m3.m_31,
		m_12 - a_m3.m_12, m_22 - a_m3.m_22, m_32 - a_m3.m_32,
		m_13 - a_m3.m_13, m_23 - a_m3.m_23, m_33 - a_m3.m_33);
}

const Matrix3& Matrix3::operator-=(const Matrix3& a_m3)
{
	m_11 -= a_m3.m_11;
	m_21 -= a_m3.m_21;
	m_31 -= a_m3.m_31;
	m_12 -= a_m3.m_12;
	m_22 -= a_m3.m_22;
	m_32 -= a_m3.m_32;
	m_13 -= a_m3.m_13;
	m_23 -= a_m3.m_23;
	m_33 -= a_m3.m_33;
	return *this;
}

Matrix3 Matrix3::operator*(const float a_fScalar) const
{
	return Matrix3(m_11 * a_fScalar, m_21 * a_fScalar, m_31 * a_fScalar,
		m_12 * a_fScalar, m_22 * a_fScalar, m_32 * a_fScalar,
		m_13 * a_fScalar, m_23 * a_fScalar, m_33 * a_fScalar);
}

const Matrix3& Matrix3::operator*=(float a_fScalar)
{
	m_11 *= a_fScalar;
	m_21 *= a_fScalar;
	m_31 *= a_fScalar;
	m_12 *= a_fScalar;
	m_22 *= a_fScalar;
	m_32 *= a_fScalar;
	m_13 *= a_fScalar;
	m_23 *= a_fScalar;
	m_33 *= a_fScalar;
	return *this;
}

Vector3 Matrix3::operator*(const Vector3& a_v3) const
{
	return Vector3(m_11 * a_v3.x + m_12 * a_v3.y + m_13 * a_v3.z,
		m_21 * a_v3.x + m_22 * a_v3.y + m_23 * a_v3.z,
		m_31 * a_v3.x + m_32 * a_v3.y + m_33 * a_v3.z);
}

Matrix3 Matrix3::operator*(const Matrix3& a_m3) const
{
	return Matrix3(m_11 * a_m3.m_11 + m_12 * a_m3.m_21 + m_13 * a_m3.m_31,
		m_21 * a_m3.m_11 + m_22 * a_m3.m_21 + m_23 * a_m3.m_31,
		m_32 * a_m3.m_11 + m_32 * a_m3.m_21 + m_33 * a_m3.m_31,

		m_11 * a_m3.m_12 + m_12 * a_m3.m_22 + m_13 * a_m3.m_32,
		m_21 * a_m3.m_12 + m_22 * a_m3.m_22 + m_23 * a_m3.m_32,
		m_31 * a_m3.m_12 + m_32 * a_m3.m_22 + m_33 * a_m3.m_32,

		m_11 * a_m3.m_13 + m_12 * a_m3.m_23 + m_13 * a_m3.m_33,
		m_21 * a_m3.m_13 + m_22 * a_m3.m_23 + m_23 * a_m3.m_33,
		m_31 * a_m3.m_13 + m_32 * a_m3.m_23 + m_33 * a_m3.m_33);
}

const Matrix3& Matrix3::operator*=(const Matrix3& a_m3)
{
	*this = (*this) * a_m3;
	return *this;
}

void Matrix3::Transpose()
{
	float k;
	k = m_12;
	m_12 = m_21;
	m_21 = k;
	k = m_13;
	m_13 = m_31;
	m_31 = k;
	k = m_23;
	m_23 = m_32;
	m_32 = k;
}

Matrix3 Matrix3::GetTranspose() const
{
	return Matrix3(m_11, m_12, m_13,
		m_21, m_22, m_23,
		m_31, m_32, m_33);
}

void Matrix3::Scale(const Vector3& a_v3)
{
	m_11 = a_v3.x;
	m_21 = 0.f;
	m_31 = 0.f;
	m_12 = 0.f;
	m_22 = a_v3.y;
	m_32 = 0.f;
	m_13 = 0.f;
	m_23 = 0.f;
	m_33 = a_v3.z;
}

void Matrix3::Scale(float a_fScalar)
{
	Scale(Vector3(a_fScalar, a_fScalar, a_fScalar));
}

void Matrix3::Identity()
{
	m_11 = 1.f;
	m_21 = 0.f;
	m_31 = 0.f;
	m_12 = 0.f;
	m_22 = 1.f;
	m_32 = 0.f;
	m_13 = 0.f;
	m_23 = 0.f;
	m_33 = 1.f;
}

float Matrix3::Determinant() const
{
	return( m_11 * (m_22 * m_33 - m_23 * m_32) +
			m_12 * (m_23 * m_31 - m_21 * m_33) +
			m_13 * (m_21 * m_32 - m_22 * m_31));
}

Matrix3 Matrix3::Inverse() const
{
	float fDet = Determinant();
	if (fDet != 0.f)
	{
		Matrix3 cofactor = Matrix3(m_22 * m_33 - m_23 * m_32, -(m_21 * m_33 - m_23 * m_31),  m_21 * m_32 - m_22 * m_31,
								 -(m_12 * m_33 - m_13 * m_32),  m_11 * m_33 - m_13 * m_31, -(m_11 * m_32 - m_12 * m_31),
								   m_12 * m_23 - m_13 * m_22, -(m_11 * m_23 - m_13 * m_21),  m_11 * m_22 - m_12 * m_21);
		cofactor *= (1.f / fDet);
		return cofactor;
	}
	return Matrix3();
}