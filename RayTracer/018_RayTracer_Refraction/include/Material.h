#pragma once

#include <libMath.h>
#include "IntersectionResponse.h"

class Material
{
public:
	Material() : albedo(1.f, 1.f, 1.f), ambient(0.f), diffuse(0.f), specular(0.f), roughness(0.f), reflective(0.f), transparency(0.0f), refractiveIndex(0.0f) {};
	Material(const Vector3& albedoIn, float ambientIn, float diffuseIn, float specularIn, float roughnessIn, float reflectiveIn, float transparencyIn, float refractiveIndexIn) :
		albedo(albedoIn), ambient(ambientIn), diffuse(diffuseIn), specular(specularIn), roughness(roughnessIn), reflective(reflectiveIn), transparency(transparencyIn), refractiveIndex(refractiveIndexIn)
	{
	};
	~Material() {};

	const Vector3& GetAlbedo() { return albedo; }
	void SetAlbedo(const Vector3& albedoIn) { albedo = albedoIn; }

	const float& GetAmbient() const { return ambient; }
	void SetAmbient(const float& ambientIn) { ambient = ambientIn; }

	const float& GetDiffuse() const { return diffuse; }
	void SetDiffuse(const float& diffuseIn) { diffuse = diffuseIn; }

	const float& GetSpecular() const { return specular; }
	void SetSpecular(const float& specularIn) { specular = specularIn; }

	const float& GetRoughness() const { return roughness; }
	void SetRoughness(const float& roughnessIn) { roughness = roughnessIn; }

	const float& GetReflective() const { return reflective; }
	void SetReflective(const float& reflectiveIn) { reflective = reflectiveIn; }

	bool CalcReflection(const Ray& rayIn, const IntersectResponse& ir, Ray& rayOut) const;

	const float& GetRefractiveIndex() const { return refractiveIndex; }
	void SetRefractiveIndex(const float& a_refractiveIndex) { refractiveIndex = a_refractiveIndex; }

	const float& GetTransparency() const { return transparency; }
	void SetTransparency(const float& a_transparency) { transparency = a_transparency; }

	bool CalcRefraction(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const;

	float Schlick(const Ray& a_in, const IntersectResponse& a_ir) const;

protected:
	Vector3 albedo;
	float ambient;
	float diffuse;
	float specular;
	float roughness;
	float reflective;
	float transparency;
	float refractiveIndex;
};