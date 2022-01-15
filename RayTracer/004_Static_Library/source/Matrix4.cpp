#include "Matrix4.h"

const Matrix4 Matrix4::IDENTITY = Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

//Default constructor defaults to identity matrix
Matrix4::Matrix4() : m_11(1.f), m_21(0.f), m_31(0.f), m_41(0.f),
m_12(0.f), m_22(1.f), m_32(0.f), m_42(0.f),
m_13(0.f), m_23(0.f), m_33(1.f), m_43(0.f),
m_14(0.f), m_24(0.f), m_34(0.f), m_44(1.f)
{
}

Matrix4::Matrix4(const float* matrix) : m_11(matrix[0]), m_21(matrix[1]), m_31(matrix[2]), m_41(matrix[3]),
m_12(matrix[4]), m_22(matrix[5]), m_32(matrix[6]), m_42(matrix[7]),
m_13(matrix[8]), m_23(matrix[9]), m_33(matrix[10]), m_43(matrix[11]),
m_14(matrix[12]), m_24(matrix[13]), m_34(matrix[14]), m_44(matrix[15])
{
}

Matrix4::Matrix4(float in_m11, float in_m21, float in_m31, float in_m41,
	float in_m12, float in_m22, float in_m32, float in_m42,
	float in_m13, float in_m23, float in_m33, float in_m43,
	float in_m14, float in_m24, float in_m34, float in_m44) :
	m_11(in_m11), m_21(in_m21), m_31(in_m31), m_41(in_m41),
	m_12(in_m12), m_22(in_m22), m_32(in_m32), m_42(in_m42),
	m_13(in_m13), m_23(in_m23), m_33(in_m33), m_43(in_m43),
	m_14(in_m14), m_24(in_m24), m_34(in_m34), m_44(in_m44)
{
}

//Angle axis constructor
Matrix4::Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w) :
	xAxis(x), yAxis(y), zAxis(z), wAxis(w)
{
}

//Copy constructor
Matrix4::Matrix4(const Matrix4& matrix) :
	m_11(matrix.m_11), m_21(matrix.m_21), m_31(matrix.m_31), m_41(matrix.m_41),
	m_12(matrix.m_12), m_22(matrix.m_22), m_32(matrix.m_32), m_42(matrix.m_42),
	m_13(matrix.m_13), m_23(matrix.m_23), m_33(matrix.m_33), m_43(matrix.m_43),
	m_14(matrix.m_14), m_24(matrix.m_24), m_34(matrix.m_34), m_44(matrix.m_44)
{
}

//Destructor
Matrix4::~Matrix4() {}

//Operator overloads
#include <cassert>
float& Matrix4::operator()(int row, int column)
{
	//Makes sure the column and row are in range
	assert(column >= 0 && column < 4);
	assert(row >= 0 && row < 4);
	return m[row - 1][column - 1];
}

float Matrix4::operator()(int row, int column) const
{
	//Makes sure the column and row are in range
	assert(column >= 0 && column < 4);
	assert(row >= 0 && row < 4);
	return m[row - 1][column - 1];
}

void Matrix4::SetColumn(int column, const Vector4& inputColumn)
{
	assert(column >= 0 && column < 4);
	m[0][column] = inputColumn.x;
	m[1][column] = inputColumn.y;
	m[2][column] = inputColumn.z;
	m[3][column] = inputColumn.w;
}

void Matrix4::SetColumn(int column, const Vector3& inputColumn)
{
	assert(column >= 0 && column < 4);
	m[0][column] = inputColumn.x;
	m[1][column] = inputColumn.y;
	m[2][column] = inputColumn.z;
}

Vector4 Matrix4::GetColumn(int column) const
{
	assert(column >= 0 && column < 4);
	Vector4 tempVec4 = Vector4(m[0][column], m[1][column], m[2][column], m[3][column]);
	return tempVec4;
}

bool Matrix4::operator == (const Matrix4& matrix) const
{
	if (m_11 != matrix.m_11) { return false; }
	if (m_21 != matrix.m_21) { return false; }
	if (m_31 != matrix.m_31) { return false; }
	if (m_41 != matrix.m_41) { return false; }
	if (m_12 != matrix.m_12) { return false; }
	if (m_22 != matrix.m_22) { return false; }
	if (m_32 != matrix.m_32) { return false; }
	if (m_42 != matrix.m_42) { return false; }
	if (m_13 != matrix.m_13) { return false; }
	if (m_23 != matrix.m_23) { return false; }
	if (m_33 != matrix.m_33) { return false; }
	if (m_43 != matrix.m_43) { return false; }
	if (m_14 != matrix.m_14) { return false; }
	if (m_24 != matrix.m_24) { return false; }
	if (m_34 != matrix.m_34) { return false; }
	if (m_44 != matrix.m_44) { return false; }
	return true;
}

bool Matrix4::operator != (const Matrix4& matrix) const
{
	if (m_11 != matrix.m_11) { return true; }
	if (m_21 != matrix.m_21) { return true; }
	if (m_31 != matrix.m_31) { return true; }
	if (m_41 != matrix.m_41) { return true; }
	if (m_12 != matrix.m_12) { return true; }
	if (m_22 != matrix.m_22) { return true; }
	if (m_32 != matrix.m_32) { return true; }
	if (m_42 != matrix.m_42) { return true; }
	if (m_13 != matrix.m_13) { return true; }
	if (m_23 != matrix.m_23) { return true; }
	if (m_33 != matrix.m_33) { return true; }
	if (m_43 != matrix.m_43) { return true; }
	if (m_14 != matrix.m_14) { return true; }
	if (m_24 != matrix.m_24) { return true; }
	if (m_34 != matrix.m_34) { return true; }
	if (m_44 != matrix.m_44) { return true; }
	return false;
}

Matrix4 Matrix4::operator + (const Matrix4& matrix) const
{
	return Matrix4(m_11 + matrix.m_11, m_21 + matrix.m_21, m_31 + matrix.m_31, m_41 + matrix.m_41,
		m_12 + matrix.m_12, m_22 + matrix.m_22, m_32 + matrix.m_23, m_42 + matrix.m_42,
		m_13 + matrix.m_13, m_23 + matrix.m_23, m_33 + matrix.m_33, m_43 + matrix.m_43,
		m_14 + matrix.m_14, m_24 + matrix.m_24, m_34 + matrix.m_34, m_44 + matrix.m_44);
}

const Matrix4& Matrix4::operator += (const Matrix4& matrix)
{
	m_11 += matrix.m_11; m_21 += matrix.m_21; m_31 += matrix.m_31; m_41 += matrix.m_41;
	m_12 += matrix.m_12; m_22 += matrix.m_22; m_32 += matrix.m_23; m_42 += matrix.m_42;
	m_13 += matrix.m_13; m_23 += matrix.m_23; m_33 += matrix.m_33; m_43 += matrix.m_43;
	m_14 += matrix.m_14; m_24 += matrix.m_24; m_34 += matrix.m_34; m_44 += matrix.m_44;
	return *this;
}

Matrix4 Matrix4::operator - (const Matrix4& matrix) const
{
	return Matrix4(m_11 - matrix.m_11, m_21 - matrix.m_21, m_31 - matrix.m_31, m_41 - matrix.m_41,
		m_12 - matrix.m_12, m_22 - matrix.m_22, m_32 - matrix.m_23, m_42 - matrix.m_42,
		m_13 - matrix.m_13, m_23 - matrix.m_23, m_33 - matrix.m_33, m_43 - matrix.m_43,
		m_14 - matrix.m_14, m_24 - matrix.m_24, m_34 - matrix.m_34, m_44 - matrix.m_44);
}

const Matrix4& Matrix4::operator -= (const Matrix4& matrix)
{
	m_11 -= matrix.m_11; m_21 -= matrix.m_21; m_31 -= matrix.m_31; m_41 -= matrix.m_41;
	m_12 -= matrix.m_12; m_22 -= matrix.m_22; m_32 -= matrix.m_23; m_42 -= matrix.m_42;
	m_13 -= matrix.m_13; m_23 -= matrix.m_23; m_33 -= matrix.m_33; m_43 -= matrix.m_43;
	m_14 -= matrix.m_14; m_24 -= matrix.m_24; m_34 -= matrix.m_34; m_44 -= matrix.m_44;
	return *this;
}

Matrix4 Matrix4::operator * (const float scalar) const
{
	return Matrix4(m_11 * scalar, m_21 * scalar, m_31 * scalar, m_41 * scalar,
		m_12 * scalar, m_22 * scalar, m_32 * scalar, m_42 * scalar,
		m_13 * scalar, m_23 * scalar, m_33 * scalar, m_43 * scalar,
		m_14 * scalar, m_24 * scalar, m_34 * scalar, m_44 * scalar);
}

const Matrix4& Matrix4::operator *= (const float scalar)
{
	m_11 *= scalar; m_21 *= scalar; m_31 *= scalar; m_41 *= scalar;
	m_12 *= scalar; m_22 *= scalar; m_32 *= scalar; m_42 *= scalar;
	m_13 *= scalar; m_23 *= scalar; m_33 *= scalar; m_43 *= scalar;
	m_14 *= scalar; m_24 *= scalar; m_34 *= scalar; m_44 *= scalar;
	return *this;
}

Vector4 Matrix4::operator * (const Vector4& vec4) const
{
	return Vector4(m_11 * vec4.x + m_12 * vec4.y + m_13 * vec4.z + m_14 * vec4.w,
		m_21 * vec4.x + m_22 * vec4.y + m_23 * vec4.z + m_24 * vec4.w,
		m_31 * vec4.x + m_32 * vec4.y + m_33 * vec4.z + m_34 * vec4.w,
		m_41 * vec4.x + m_42 * vec4.y + m_43 * vec4.z + m_44 * vec4.w);
}

Vector3 Matrix4::operator * (const Vector3& vec3) const
{
	Vector4 tempVec4 = Vector4(vec3.x, vec3.y, vec3.z, 1.f);
	return((*this * tempVec4).XYZ());
}

Matrix4 Matrix4::operator * (const Matrix4& matrix) const
{
	return Matrix4(m_11 * matrix.m_11 + m_12 * matrix.m_21 + m_13 * matrix.m_31 + m_14 * matrix.m_41,
		m_21 * matrix.m_11 + m_22 * matrix.m_21 + m_23 * matrix.m_31 + m_24 * matrix.m_41,
		m_31 * matrix.m_11 + m_32 * matrix.m_21 + m_33 * matrix.m_31 + m_34 * matrix.m_41,
		m_41 * matrix.m_11 + m_42 * matrix.m_21 + m_43 * matrix.m_31 + m_44 * matrix.m_41,

		m_11 * matrix.m_12 + m_12 * matrix.m_22 + m_13 * matrix.m_32 + m_14 * matrix.m_42,
		m_21 * matrix.m_12 + m_22 * matrix.m_22 + m_23 * matrix.m_32 + m_24 * matrix.m_42,
		m_31 * matrix.m_12 + m_32 * matrix.m_22 + m_33 * matrix.m_32 + m_34 * matrix.m_42,
		m_41 * matrix.m_12 + m_42 * matrix.m_22 + m_43 * matrix.m_32 + m_44 * matrix.m_42,

		m_11 * matrix.m_13 + m_12 * matrix.m_23 + m_13 * matrix.m_33 + m_14 * matrix.m_43,
		m_21 * matrix.m_13 + m_22 * matrix.m_23 + m_23 * matrix.m_33 + m_24 * matrix.m_43,
		m_31 * matrix.m_13 + m_32 * matrix.m_23 + m_33 * matrix.m_33 + m_34 * matrix.m_43,
		m_41 * matrix.m_13 + m_42 * matrix.m_23 + m_43 * matrix.m_33 + m_44 * matrix.m_43,

		m_11 * matrix.m_14 + m_12 * matrix.m_24 + m_13 * matrix.m_34 + m_14 * matrix.m_44,
		m_21 * matrix.m_14 + m_22 * matrix.m_24 + m_23 * matrix.m_34 + m_24 * matrix.m_44,
		m_31 * matrix.m_14 + m_32 * matrix.m_24 + m_33 * matrix.m_34 + m_34 * matrix.m_44,
		m_41 * matrix.m_14 + m_42 * matrix.m_24 + m_43 * matrix.m_34 + m_44 * matrix.m_44);
}

const Matrix4& Matrix4::operator *= (const Matrix4& matrix)
{
	*this = (*this) * matrix;
	return *this;
}

//Functions
void Matrix4::Transpose()
{
	float x;
	x = m_12; m_12 = m_21; m_21 = x;
	x = m_13; m_13 = m_31; m_31 = x;
	x = m_23; m_23 = m_32; m_32 = x;
	x = m_14; m_14 = m_41; m_41 = x;
	x = m_24; m_24 = m_42; m_42 = x;
	x = m_34; m_34 = m_43; m_43 = x;
}

Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(m_11, m_12, m_13, m_14,
		m_21, m_22, m_23, m_24,
		m_31, m_32, m_33, m_34,
		m_41, m_42, m_43, m_44);
}

void Matrix4::Scale(const Vector4& vec4)
{
	m_11 = vec4.x; m_21 = 0.f; m_31 = 0.f; m_41 = 0.f;
	m_12 = 0.f; m_22 = vec4.y; m_32 = 0.f; m_42 = 0.f;
	m_13 = 0.f; m_23 = 0.f; m_33 = vec4.z; m_43 = 0.f;
	m_14 = 0.f; m_24 = 0.f; m_34 = 0.f; m_44 = vec4.w;
}

void Matrix4::Scale(const Vector3& vec3)
{
	m_11 = vec3.x; m_21 = 0.f; m_31 = 0.f;
	m_12 = 0.f; m_22 = vec3.y; m_32 = 0.f;
	m_13 = 0.f; m_23 = 0.f; m_33 = vec3.z;
}

void Matrix4::Scale(float scalar)
{
	Scale(Vector4(scalar, scalar, scalar, scalar));
}

void Matrix4::Shear(float xy, float xz, float yx, float yz, float zx, float zy)
{
	m_11 = 1.f; m_21 = yx; m_31 = zx; m_41 = 0.f;
	m_12 = xy; m_22 = 1.f; m_32 = zy; m_42 = 0.f;
	m_13 = xz; m_23 = yz; m_33 = 1.f; m_43 = 0.f;
	m_14 = 0.f; m_24 = 0.f; m_34 = 0.f; m_44 = 1.f;
}

void Matrix4::Identity()
{
	m_11 = 1.f; m_21 = 0.f; m_31 = 0.f; m_41 = 0.f;
	m_12 = 0.f; m_22 = 1.f; m_32 = 0.f; m_42 = 0.f;
	m_13 = 0.f; m_23 = 0.f; m_33 = 1.f; m_43 = 0.f;
	m_14 = 0.f; m_24 = 0.f; m_34 = 0.f; m_44 = 1.f;
}

float Matrix4::Determinant() const
{
	float a = m_11 * (m_22 * (m_33 * m_44 - m_34 * m_43) +
		m_23 * (m_34 * m_42 - m_32 * m_44) +
		m_24 * (m_32 * m_43 - m_33 * m_42));

	float b = m_12 * (m_21 * (m_33 * m_44 - m_34 * m_43) +
		m_23 * (m_34 * m_41 - m_31 * m_44) +
		m_24 * (m_31 * m_43 - m_33 * m_41));

	float c = m_13 * (m_21 * (m_32 * m_44 - m_34 * m_42) +
		m_22 * (m_34 * m_41 - m_31 * m_44) +
		m_24 * (m_31 * m_42 - m_32 * m_41));

	float d = m_14 * (m_21 * (m_32 * m_43 - m_33 * m_42) +
		m_22 * (m_33 * m_41 - m_31 * m_43) +
		m_23 * (m_31 * m_42 - m_32 * m_41));

	return a - b + c - d;
}

Matrix4 Matrix4::Inverse() const
{
	const float det = Determinant();
	if (det != 0.0f)
	{
		const float invDet = 1.f / det;
		Matrix4 inverted;

		inverted.m_11 = (m_22 * (m_33 * m_44 - m_34 * m_43) +
			m_23 * (m_34 * m_42 - m_32 * m_44) +
			m_24 * (m_32 * m_43 - m_33 * m_42)) * invDet;

		inverted.m_21 = (m_21 * (m_33 * m_44 - m_34 * m_43) +
			m_23 * (m_34 * m_41 - m_31 * m_44) +
			m_24 * (m_31 * m_43 - m_33 * m_41)) * -invDet;

		inverted.m_31 = (m_21 * (m_32 * m_44 - m_34 * m_42) +
			m_22 * (m_34 * m_41 - m_31 * m_44) +
			m_24 * (m_31 * m_42 - m_32 * m_41)) * invDet;

		inverted.m_41 = (m_21 * (m_32 * m_43 - m_33 * m_42) +
			m_22 * (m_33 * m_41 - m_31 * m_43) +
			m_23 * (m_31 * m_42 - m_32 * m_41)) * -invDet;

		inverted.m_12 = (m_12 * (m_33 * m_44 - m_34 * m_43) +
			m_13 * (m_34 * m_42 - m_32 * m_44) +
			m_14 * (m_32 * m_43 - m_33 * m_42)) * -invDet;

		inverted.m_22 = (m_11 * (m_33 * m_44 - m_34 * m_43) +
			m_13 * (m_34 * m_41 - m_31 * m_44) +
			m_14 * (m_31 * m_43 - m_33 * m_41)) * invDet;

		inverted.m_32 = (m_11 * (m_32 * m_44 - m_34 * m_42) +
			m_12 * (m_34 * m_41 - m_31 * m_44) +
			m_14 * (m_31 * m_42 - m_32 * m_41)) * -invDet;

		inverted.m_42 = (m_11 * (m_32 * m_43 - m_33 * m_42) +
			m_12 * (m_33 * m_41 - m_31 * m_43) +
			m_13 * (m_31 * m_42 - m_32 * m_41)) * invDet;

		inverted.m_13 = (m_12 * (m_23 * m_44 - m_24 * m_43) +
			m_13 * (m_24 * m_42 - m_22 * m_44) +
			m_14 * (m_22 * m_43 - m_23 * m_42)) * invDet;

		inverted.m_23 = (m_11 * (m_23 * m_44 - m_24 * m_43) +
			m_13 * (m_24 * m_41 - m_21 * m_44) +
			m_14 * (m_21 * m_43 - m_23 * m_41)) * -invDet;

		inverted.m_33 = (m_11 * (m_22 * m_44 - m_24 * m_42) +
			m_12 * (m_24 * m_41 - m_21 * m_44) +
			m_14 * (m_21 * m_42 - m_22 * m_41)) * invDet;

		inverted.m_43 = (m_11 * (m_22 * m_43 - m_23 * m_42) +
			m_12 * (m_23 * m_41 - m_21 * m_43) +
			m_13 * (m_21 * m_42 - m_22 * m_41)) * -invDet;

		inverted.m_14 = (m_12 * (m_23 * m_34 - m_24 * m_33) +
			m_13 * (m_24 * m_32 - m_22 * m_34) +
			m_14 * (m_22 * m_33 - m_23 * m_32)) * -invDet;

		inverted.m_24 = (m_11 * (m_23 * m_34 - m_24 * m_33) +
			m_13 * (m_24 * m_31 - m_21 * m_34) +
			m_14 * (m_21 * m_33 - m_23 * m_31)) * invDet;

		inverted.m_34 = (m_11 * (m_22 * m_34 - m_24 * m_32) +
			m_12 * (m_24 * m_31 - m_21 * m_34) +
			m_14 * (m_21 * m_32 - m_22 * m_31)) * -invDet;

		inverted.m_44 = (m_11 * (m_22 * m_33 - m_23 * m_32) +
			m_12 * (m_23 * m_31 - m_21 * m_33) +
			m_13 * (m_21 * m_32 - m_22 * m_31)) * invDet;

		return inverted;
	}
	else
	{
		return Matrix4::IDENTITY;
	}
}

bool Matrix4::Perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	float tanHalfFov = tanf(fov * 0.5f);
	if (fabsf(farPlane - nearPlane) < 0.01f)
	{
		return false;
	}
	const float w = 1.f / (aspectRatio * tanHalfFov);
	const float h = 1.f / tanHalfFov;
	const float r = 1.f / (farPlane - nearPlane);

	//X Axis
	m_11 = w; m_21 = 0.0f; m_31 = 0.0f; m_41 = 0.0f;
	//Y Axis
	m_12 = 0.0f; m_22 = h; m_32 = 0.0f; m_42 = 0.0f;
	//Z Axis
	m_13 = 0.0f; m_23 = 0.0f; m_33 = -(farPlane + nearPlane) * r; m_43 = -1.0f;
	//Transpose Column
	m_14 = 0.0f; m_24 = 0.0f; m_34 = -(2.0f * farPlane * nearPlane) * r; m_44 = 0.0f;

	return true;
}

bool Matrix4::Orthographic(float left, float right, float top, float bottom, float near, float far)
{
	float deltaX = right - left;
	float deltaY = top - bottom;
	float deltaZ = far - near;

	//X Axis
	m_11 = 2.0f / deltaX; m_21 = 0.0f; m_31 = 0.0f; m_41 = 0.0f;
	//Y Axis
	m_12 = 0.0f; m_22 = 2.0f / deltaY; m_32 = 0.0f; m_42 = 0.0f;
	//Z Axis
	m_13 = 0.0f; m_23 = 0.0f; m_33 = -2.0f / deltaZ; m_43 = 0.0f;
	//Transpose Column
	m_14 = -((right + left) / deltaX);
	m_24 = -((top + bottom) / deltaY);
	m_34 = -((near + far) / deltaZ);
	m_44 = 1.0f;

	return true;
}

Matrix4 Matrix4::LookAt(const Vector3& eyePos, const Vector3& target, const Vector3& up)
{
	Vector3 vecRight;
	Vector3 vecForward;
	Vector3 vecUp;

	vecForward = target - eyePos;
	vecForward.Normalize();
	vecRight = Cross(vecForward, up);
	vecRight.Normalize();
	vecUp = Cross(vecRight, vecForward);
	vecUp.Normalize();
	Matrix4 mat = Matrix4::IDENTITY;

	//X Axis
	mat.m_11 = vecRight.x; mat.m_21 = vecRight.y; mat.m_31 = vecRight.z; mat.m_41 = 0.0f;
	//Y Axis
	mat.m_12 = vecUp.x; mat.m_22 = vecUp.y; mat.m_32 = vecUp.z; mat.m_42 = 0.0f;
	//Z Axis
	mat.m_13 = -vecForward.x; mat.m_23 = -vecForward.y; mat.m_33 = -vecForward.z; mat.m_43 = 0.0f;
	//Transpose Column
	mat.Transpose();
	mat.m_14 = -Dot(vecRight, eyePos);
	mat.m_24 = -Dot(vecUp, eyePos);
	mat.m_34 = Dot(vecForward, eyePos);
	mat.m_44 = 1.0f;

	return mat;
}

void Matrix4::Orthonormalise()
{
	Vector3 xBasis = Vector3(m_11, m_21, m_31);
	Vector3 yBasis = Vector3(m_12, m_22, m_32);
	Vector3 zBasis = Vector3(m_13, m_23, m_33);

	yBasis = yBasis - (zBasis * Dot(zBasis, yBasis));
	yBasis.Normalize();
	xBasis = Cross(yBasis, zBasis);
	xBasis.Normalize();

	m_11 = xBasis.x; m_21 = xBasis.y; m_31 = xBasis.z;
	m_12 = yBasis.x; m_22 = yBasis.y; m_32 = yBasis.z;
	m_13 = zBasis.x; m_23 = zBasis.y; m_33 = zBasis.z;
}