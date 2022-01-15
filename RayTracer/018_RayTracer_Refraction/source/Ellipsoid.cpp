#include "Ellipsoid.h"

Ellipsoid::Ellipsoid() : m_radius(1.0f)
{
}

Ellipsoid::Ellipsoid(const Vector3& a_position, const float& a_radius) : m_radius(a_radius)
{
	SetPosition(a_position);
	SetScale(Vector3(m_radius, m_radius, m_radius));
}

Ellipsoid::~Ellipsoid()
{
}

// Function to calculate the point of intersection with an ellipsoid and a ray
// returns true is intersection occurs, tests for intersections in front of the ray (not behind)
bool Ellipsoid::IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const
{
	// The normal matrix is the inverse transpose of the transform
	Matrix4 normalMatrix = m_Transform.GetTranspose().Inverse();

	Matrix4 invTx = m_Transform.Inverse();								// Get the inverse of the transform matrix
	Vector4 rayOrigin = invTx * Vector4(a_ray.Origin(), 1.0f);			// Multiply ray origin by inverse to get in local space
	Vector4 rayDir = (invTx * Vector4(a_ray.Direction(), 0.0f));		// Get ray direction in local space
	rayDir.Normalize();

	Vector3 OC = rayOrigin.XYZ();			// Vector from Ray Origin to center of sphere
	float b = Dot(OC, rayDir.XYZ());		// Dot product of direction with vector to center of sphere
	float c = Dot(OC, OC) - 1.0f;			// Dot product of OC subtract radius squared (radius of 1 for unit sphere)
	float discriminant = b * b - c;			// Discriminant part under sqrt of quadratic (b - c)
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		// Test for both intersection points to see if intersection occurs behind ray origin
		// Discard negative intersection distances as intersection is behind ray
		float dist = -1.0f;						// Start with distance initialised as negative
		float i0 = -b - sqrt(discriminant);		// Complete negative part of quadratic equation
		float i1 = -b + sqrt(discriminant);		// Complete positive part of quadratic equation
		if (i0 > 0.0f)							// Is first intersection point in front of ray origin
		{
			dist = i0;
		}
		else if (i1 > 0.0f)						// If first point not in front of origin is second intersection point
		{
			dist = i1;
		}
		else
		{
			return false;						// Both intersection points behind ray origin
		}
		// Now that we have closest positive intersection point
		Vector4 hp = rayOrigin + rayDir * dist;			// Calculate hit point in local space to ellipsoid
		Vector3 sn = hp.XYZ();		// Normalize this point provides direction of surface normal
		sn.Normalize();
		hp = m_Transform * hp;								// Multiply point by transform matrix to get in world space
		a_ir.HitPos = hp.XYZ();			// Nearest hit point on surface of ellipsoid to ray

		a_ir.SurfaceNormal = normalMatrix * sn;						// Convert normal into world space normal by multiplying with normal matrix
		a_ir.SurfaceNormal.Normalize();

		a_ir.frontFace = Dot(a_ir.SurfaceNormal, a_ray.Direction()) < 0.0f;	// If normal and incoming ray in same direction then not front

		a_ir.distance = (a_ray.Origin() - hp.XYZ()).Length();

		a_ir.material = m_material;
		return true;									// Return true as ray intersected ellipsoid
	}
	return false;										// No intersection has occurred
}