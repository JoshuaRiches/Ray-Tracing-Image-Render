#include "Material.h"
#include <Random.h>

bool Material::CalcReflection(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const
{
	// Generate a random vector in range -1 : 1 for all components
	Vector3 randomUnitVec = Vector3(Random::RandRange(-1.0f, 1.0f), Random::RandRange(-1.0f, 1.0f), Random::RandRange(-1.0f, 1.0f));
	randomUnitVec.Normalize(); // ensure vector normalised to make vector unit vector
	// Reflected ray, from hit location
	Vector3 reflected = Reflect(a_in.Direction(), a_ir.SurfaceNormal);
	reflected.Normalize();
	// add the random unit vector to the reflected ray based on roughness if smooth then no randomness
	a_out = Ray(a_ir.HitPos, reflected + (randomUnitVec * roughness), 0.001f);
	// Return true if we have not reflected into the surface
	return (Dot(a_out.Direction(), a_ir.SurfaceNormal) > 0.0f);
}

bool Material::CalcRefraction(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const
{
	// Generate a random vector in range -1 : 1 for all components
	Vector3 randomUnitVec = Vector3(Random::RandRange(-1.0f, 1.0f), Random::RandRange(-1.0f, 1.0f), Random::RandRange(-1.0f, 1.0f));
	randomUnitVec.Normalize(); // ensure vector normalised to make vector unit vector
	// Refract the ray from the hit location
	// For this we will assume that on leaving the object, the reay enters air's refractive index of 1.0
	float refraction_ratio = a_ir.frontFace ? (1.0f / refractiveIndex) : refractiveIndex;	// Inversion of n/n1 from snells law
	float cos_i = Dot(-a_in.Direction(), a_ir.SurfaceNormal);								// Angle of incidence from dot product

	float sin2_t = refraction_ratio * refraction_ratio * (1.0f - cos_i * cos_i);			// sin(theta_t)^2 outoging angle of refracted ray
	if (sin2_t > 1.0f) return false;
	float cos_t = sqrtf(fabsf(1.0f - sin2_t));												// cosine angle of refracted ray
	// Compute direction of outgoing refracted ray
	Vector3 refracted = a_ir.SurfaceNormal * (refraction_ratio * cos_i - cos_t) + a_in.Direction() * refraction_ratio;
	a_out = Ray(a_ir.HitPos, refracted + (randomUnitVec * roughness), 0.001f);				// Outgoing refracted ray
	return true;																			// return true as everything refracts
}

float Material::Schlick(const Ray& a_in, const IntersectResponse& a_ir) const
{
	float cos_i = Dot(-a_in.Direction(), a_ir.SurfaceNormal);								// Angle of incidence
	float refraction_ratio = a_ir.frontFace ? (1.0f / refractiveIndex) : refractiveIndex;	// Inversion of n/n1 from snells law
	// Calculate schlicks approximation for fresnel value
	// total internal reflection refractive index 1 > refractive index 2
	bool internalReflection = (a_ir.frontFace) ? (1.0f > refractiveIndex) : (refractiveIndex > 1.0f);

	if (internalReflection)
	{
		float sin2_t = refraction_ratio * refraction_ratio * (1.0f - cos_i * cos_i);			// sin(theta_t)^2 outoging angle of refracted ray
		if (sin2_t > 1.0f)
		{
			return 1.0f;
		}
		cos_i = sqrtf(1.0f - sin2_t);
	}

	float r0 = (1.0f - refraction_ratio) / (1.0f + refraction_ratio);							// schlicks approximation
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * powf(1.0f - cos_i, 5);
}