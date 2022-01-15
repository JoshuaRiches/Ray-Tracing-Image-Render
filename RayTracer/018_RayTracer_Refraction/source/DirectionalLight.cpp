#include "DirectionalLight.h"
#include <MathUtil.h>
#include <cmath>

DirectionalLight::DirectionalLight()
{
	SetDirection(Vector3(0.0f, 0.0f, 0.0f));
}

DirectionalLight::DirectionalLight(const Matrix4& a_transform, const Vector3& a_color, const Vector3& a_facing) : Light(a_transform, a_color)
{
	SetDirection(a_facing);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(const Vector3& a_direction, const Vector3& a_up)
{
	m_Transform.SetColumn(2, a_direction);
	m_Transform.SetColumn(1, a_up);
	m_Transform.Orthonormalise();
}

Vector3 DirectionalLight::GetDirection() const
{
	return m_Transform.GetColumn(2).XYZ();
}

Vector3 DirectionalLight::GetDirectionToLight(const Vector3& a_point) const
{
	return GetDirection();
}

ColorRGB DirectionalLight::CalculateLighting(const IntersectResponse& a_ir, const Vector3& a_eyePos, float a_shadowFactor) const
{
	// calculate effective light color for diffuse channel (and metallic specular)
	Vector3 effectiveColor = m_colorRGB * a_ir.material->GetAlbedo();

	// We will look at materials next tutorial
	ColorRGB ambient = effectiveColor * a_ir.material->GetAmbient();	// Get ambient color for surface
	// Light Direction is forward axis of light matrix
	Vector3 lightDirection = -GetDirection();							// Get directio to light from surface
	float lightDiffuse = MathUtil::Max(0.0f, Dot(lightDirection, a_ir.SurfaceNormal)); // Positive values indicate vectors in same dir
	ColorRGB diffuse = effectiveColor * a_ir.material->GetDiffuse() * lightDiffuse;	// Blend light diffuse value and color
	// Calculate light specular value
	// for non-metals material color plays no part in specular highlight
	Vector3 eyeDir = a_ir.HitPos - a_eyePos;			// Get the dir from view to surface
	eyeDir.Normalize();
	Vector3 reflectionVec = Reflect(eyeDir, a_ir.SurfaceNormal);	// Get the reflection vector of the eye around normal
	// Specular power indicates roughness of the surface material use roughness to control specular power as range between 0 ->255
	float specularPower = (1.0f - a_ir.material->GetRoughness()) * 254.0f + 1.0f;
	float specularFactor = std::powf(MathUtil::Max(0.0f, Dot(reflectionVec, lightDirection)), specularPower);	// Get the specular value
	ColorRGB specular = m_colorRGB * a_ir.material->GetSpecular() * specularFactor;

	return ambient + (diffuse + specular) * a_shadowFactor;
}