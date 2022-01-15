#pragma once
#include <libMath.h>
#include "IntersectionResponse.h"
class Material;

class Primitive
{
public:
	Primitive();
	virtual ~Primitive();
	// FUnction to text for intersection with primitive and ray - pure virtual only implemented in derived classes
	virtual bool IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const = 0;
	// Get and set primitive matrix
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);
	// Get and set the position of the primitive
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);
	// Get and set the scale of the primitive
	Vector3 GetScale() const;
	void SetScale(const Vector3& a_v3);
	void SetShear(float xy, float xz, float yx, float yz, float zx, float zy);

	void SetMaterial(Material* a_material);
	const Material* GetMaterial() { return m_material; }

protected:
	Matrix4 m_Transform;	// Position scale and rotation
	Vector3 m_Scale;		// Scale Vector
	Material* m_material;	// Surface material for the primitive
};