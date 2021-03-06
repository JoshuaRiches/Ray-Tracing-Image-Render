#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const Matrix4& a_transform, const Vector3& a_color, const Vector3& a_facing);
	virtual ~DirectionalLight();
	// Override the base light class' calculate lighting function
	ColorRGB CalculateLighting(const IntersectResponse& a_ir, const Vector3& a_eyePos, float a_shadowFactor = 1.0f) const override;
	// Functionality to set and get the direction of the light
	void SetDirection(const Vector3& a_direction, const Vector3& a_up = Vector3(0.0f, 1.0f, 0.0f));
	Vector3 GetDirection() const;
	Vector3 GetDirectionToLight(const Vector3& a_point = Vector3(0.0f, 0.0f, 0.0f)) const override;
protected:
	// Directional light no additional variables use fwd direction from m_Transform  for direction
};