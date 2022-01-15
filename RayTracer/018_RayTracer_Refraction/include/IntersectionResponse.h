#pragma once
#include <libMath.h>
class Material;

struct IntersectResponse
{
	Vector3 HitPos;			// The location in worldspace of the intersection
	Vector3 SurfaceNormal;	// The surface normal at the intersection location
	float distance;			// The distance to the hit location
	Material* material;		// The material property of the intersected object
	bool frontFace;			// This is the front face or internal face of the object (in case of refraction)
};