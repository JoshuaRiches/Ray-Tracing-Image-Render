#include "libMath.h"
#include <math.h>

//\-----------------------------------------------------------------------------
// Default Constructor
//\-----------------------------------------------------------------------------
Vector4::Vector4()
{
	x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;
}
//\-----------------------------------------------------------------------------
// Constructor with X, Y and Z values
//\-----------------------------------------------------------------------------
Vector4::Vector4(const float a_x, const float a_y, const float a_z, const float a_w)
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}
//\-----------------------------------------------------------------------------
// Copy Constructor
//\-----------------------------------------------------------------------------
Vector4::Vector4(const Vector4& a_v4)
{
	x = a_v4.x;
	y = a_v4.y;
	z = a_v4.z;
	w = a_v4.w;
}
Vector4::Vector4(const Vector3& a_v3, const float a_w)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
	w = a_w;
}
//\-----------------------------------------------------------------------------
// Destructor
//\-----------------------------------------------------------------------------
Vector4::~Vector4()
{
	//nothing
}
//\-----------------------------------------------------------------------------
// Equivalence Operators
//\-----------------------------------------------------------------------------
bool Vector4::operator ==(const Vector4& a_v4) const
{
	return (x == a_v4.x && y == a_v4.y && z == a_v4.z && w == a_v4.w);
}
bool Vector4::operator !=(const Vector4& a_v4) const
{
	return (x != a_v4.x || y != a_v4.y || z != a_v4.z || w != a_v4.w);
}
//\-----------------------------------------------------------------------------
// Neg Operator
//\-----------------------------------------------------------------------------
const Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator-(const Vector4& a_v4) const
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, w - a_v4.w);
}

Vector4 Vector4::operator-(const float a_scalar) const
{
	return Vector4(x - a_scalar, y - a_scalar, z - a_scalar, w - a_scalar);
}
//\-----------------------------------------------------------------------------
// Overload Operator for Vector4 addition
//\-----------------------------------------------------------------------------
Vector4 Vector4::operator+(const Vector4& a_v4) const
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, w + a_v4.w);
}

Vector4 Vector4::operator+(const float a_scalar) const
{
	return Vector4(x + a_scalar, y + a_scalar, z + a_scalar, w + a_scalar);
}
//\-----------------------------------------------------------------------------
// Dot product - projection of one vector along another
//				 or the cosine of the angle between two vectors
//\-----------------------------------------------------------------------------
float Vector4::Dot(const Vector4& a_v4) const
{
	return (x * a_v4.x + y * a_v4.y + z * a_v4.z  + w * a_v4.w);
}
//\-----------------------------------------------------------------------------
// Dot product - Friend function allows use to do the following in code
//				 Vector4 result = Dot(Vec3A, Vec3B);
//				 notice the lack of "Vector4::" prior to the function
//\-----------------------------------------------------------------------------
float Dot(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.Dot(a_v4B);
}
//\-----------------------------------------------------------------------------
// Cross Product
//\-----------------------------------------------------------------------------
Vector4 Vector4::Cross(const Vector4& a_v4) const
{
	return Vector4(y * a_v4.z - a_v4.y * z, z * a_v4.x - x * a_v4.z, x * a_v4.y - y * a_v4.x, 0);
}

Vector4	Cross(const Vector4& a_v4a, const Vector4& a_v4b)
{
	return a_v4a.Cross(a_v4b);
}
//\-----------------------------------------------------------------------------
// Overload Operator for the Vector4 Multiplication
//\-----------------------------------------------------------------------------
Vector4 Vector4::operator*(const float& a_scalar) const
{
	return Vector4(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);
}
//\-----------------------------------------------------------------------------
// Get the length (magnitude) of the vector
//\-----------------------------------------------------------------------------
float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}
//\-----------------------------------------------------------------------------
// Normalise the Vector
//\-----------------------------------------------------------------------------
void Vector4::Normalize()
{
	float length = Length();
	if (length > 0.0f)
	{
		float invLen = 1.0f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;
	}
}
Vector3 Vector4::XYZ()
{
	return Vector3(x, y, z);
}
//\-----------------------------------------------------------------------------
// Linear Interpolate
//\-----------------------------------------------------------------------------
Vector4 Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t)
{
	return (a_v4B - a_v4A) * a_t + a_v4A;
}