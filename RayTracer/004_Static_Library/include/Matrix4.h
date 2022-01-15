#ifndef _MATRIX_4_H_
#define _MATRIX_4_H_
#include "LibMath.h"

/// <summary>
/// 4 by 4 Matrix Class
/// </summary>
class Matrix4
{
private:
	// These member variables are held in a union for better accessibility, sharing the same memory.
	union
	{
		float m[4][4];
		struct
		{
			float m_11, m_12, m_13, m_14; //Column 1: X axis
			float m_21, m_22, m_23, m_24; //Column 2: Y axis
			float m_31, m_32, m_33, m_34; //Column 3: Z axis
			float m_41, m_42, m_43, m_44; //Column 4: W axis
		};
		struct
		{
			Vector4 xAxis;
			Vector4 yAxis;
			Vector4 zAxis;
			Vector4 wAxis;
		};
	};

public:
	//Constants
	static const Matrix4 IDENTITY;
	//Constructors
	Matrix4();
	Matrix4(const float* matrix); //This is a float pointer to an array of floats
	Matrix4(float in_m11, float in_m21, float in_m31, float in_m41,
		float in_m12, float in_m22, float in_m32, float in_m42,
		float in_m13, float in_m23, float in_m33, float in_m43,
		float in_m14, float in_m24, float in_m34, float in_m44);
	Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w);
	Matrix4(const Matrix4& matrix); //Copy constructor
	~Matrix4(); //Destructor

	//Operator overloads
	float& operator() (int column, int row);
	float operator() (int column, int row) const;

	void SetColumn(int column, const Vector4& inputColumn);
	void SetColumn(int column, const Vector3& inputColumn);
	Vector4 GetColumn(int column) const;

	bool operator == (const Matrix4& matrix) const;
	bool operator != (const Matrix4& matrix) const;

	Matrix4 operator + (const Matrix4& matrix) const;
	const Matrix4& operator += (const Matrix4& matrix);

	Matrix4 operator - (const Matrix4& matrix) const;
	const Matrix4& operator -= (const Matrix4& matrix);

	Matrix4 operator * (const Matrix4& matrix) const;
	const Matrix4& operator *= (const Matrix4& matrix);

	Matrix4 operator * (const float scalar) const;
	const Matrix4& operator *= (const float scalar);

	Vector4 operator * (const Vector4& vec4) const;
	Vector3 operator * (const Vector3& vec3) const;

	//Transpose functions
	void Transpose();
	Matrix4 GetTranspose() const;

	void Scale(const float scalar);
	void Scale(const Vector4& vec4);
	void Scale(const Vector3& vec3);

	void Shear(float xy, float xz, float yx, float yz, float zx, float zy);

	void Identity();

	float Determinant() const;
	Matrix4 Inverse() const;

	//Camera projection functions
	bool Perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
	bool Orthographic(float left, float right, float top, float bottom, float near, float far);
	static Matrix4 LookAt(const Vector3& eyePos, const Vector3& target, const Vector3& up);

	void Orthonormalise();
};

#endif //_MATRIX_4_H_