#include "libMath.h"
#include <math.h>

//\-----------------------------------------------------------------------------
// Default Constructor
//\-----------------------------------------------------------------------------
Vector3::Vector3()
{
	x = 0.0f; y = 0.0f; z = 0.0f;
}
//\-----------------------------------------------------------------------------
// Constructor with X, Y and Z values
//\-----------------------------------------------------------------------------
Vector3::Vector3(const float a_x, const float a_y, const float a_z)
{
	x = a_x;
	y = a_y;
	z = a_z;
}
//\-----------------------------------------------------------------------------
// Copy Constructor
//\-----------------------------------------------------------------------------
Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}
//\-----------------------------------------------------------------------------
// Destructor
//\-----------------------------------------------------------------------------
Vector3::~Vector3()
{
	//nothing
}
//\-----------------------------------------------------------------------------
// Equivalence Operators
//\-----------------------------------------------------------------------------
bool Vector3::operator ==(const Vector3& a_v3) const
{
	return (x == a_v3.x && y == a_v3.y && z == a_v3.z);
}
bool Vector3::operator !=(const Vector3& a_v3) const
{
	return (x != a_v3.x || y != a_v3.y || z != a_v3.z);
}
//\-----------------------------------------------------------------------------
// Neg Operator
//\-----------------------------------------------------------------------------
const Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(const Vector3& a_v3) const
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}

Vector3 Vector3::operator-(const float a_scalar) const
{
	return Vector3(x - a_scalar, y - a_scalar, z - a_scalar);
}
//\-----------------------------------------------------------------------------
// Overload Operator for Vector3 addition
//\-----------------------------------------------------------------------------
Vector3 Vector3::operator+(const Vector3& a_v3) const
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}

Vector3 Vector3::operator+(const float a_scalar) const
{
	return Vector3(x + a_scalar, y + a_scalar, z + a_scalar);
}
//\-----------------------------------------------------------------------------
// Dot product - projection of one vector along another
//				 or the cosine of the angle between two vectors
//\-----------------------------------------------------------------------------
float Vector3::Dot(const Vector3& a_v3) const
{
	return (x * a_v3.x + y * a_v3.y + z * a_v3.z);
}
//\-----------------------------------------------------------------------------
// Dot product - Friend function allows use to do the following in code
//				 Vector3 result = Dot(Vec3A, Vec3B);
//				 notice the lack of "Vector3::" prior to the function
//\-----------------------------------------------------------------------------
float Dot(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return a_v3A.Dot(a_v3B);
}
//\-----------------------------------------------------------------------------
// Cross Product
//\-----------------------------------------------------------------------------
Vector3 Vector3::Cross(const Vector3& a_v3) const
{
	return Vector3(y * a_v3.z - a_v3.y * z, z * a_v3.x - x * a_v3.z, x * a_v3.y - y * a_v3.x);
}

Vector3	Cross(const Vector3& a_v3a, const Vector3& a_v3b)
{
	return a_v3a.Cross(a_v3b);
}
//\-----------------------------------------------------------------------------
// Overload Operator for the Vector3 Multiplication
//\-----------------------------------------------------------------------------
Vector3 Vector3::operator*(const float& a_scalar) const
{
	return Vector3(x * a_scalar, y * a_scalar, z * a_scalar);
}
Vector3 Vector3::operator*(const Vector3& a_v3a) const
{
	return Vector3(x * a_v3a.x, y * a_v3a.y, z * a_v3a.z);
}
//\-----------------------------------------------------------------------------
// Get the length (magnitude) of the vector
//\-----------------------------------------------------------------------------
float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}
//\-----------------------------------------------------------------------------
// Normalise the Vector
//\-----------------------------------------------------------------------------
void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.0f)
	{
		float invLen = 1.0f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}
Vector3 Vector3::Normalize(Vector3 a_v3)
{
	float length = a_v3.Length();
	if (length > 0.0f)
	{
		float invLen = 1.0f / length;
		a_v3.x *= invLen;
		a_v3.y *= invLen;
		a_v3.z *= invLen;
		return a_v3;
	}
}
Vector3 Vector3::operator+=(const Vector3& a_v3)
{
	this->x += a_v3.x;
	this->y += a_v3.y;
	this->z += a_v3.z;
	return *this;
}
//\-----------------------------------------------------------------------------
// Linear Interpolate
//\-----------------------------------------------------------------------------
Vector3 Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t)
{
	return (a_v3B - a_v3A) * a_t + a_v3A;
}
//\-----------------------------------------------------------------------------
// Reflect one vector around another
//\-----------------------------------------------------------------------------
Vector3 Reflect(const Vector3& a_v3A, const Vector3& a_v3B)
{
	Vector3 reflect = a_v3A - (a_v3B * 2.0f * Dot(a_v3A, a_v3B));
	return reflect;
}