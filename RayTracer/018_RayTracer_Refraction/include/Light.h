#include <libMath.h>
#include "ColorRGB.h"
#include "IntersectionResponse.h"
#include "Material.h"

class Light
{
public:
	Light();
	Light(const Matrix4& a_transform, const ColorRGB& a_color);
	virtual ~Light();
	// Each type of light will need to calculate its own lighting outcome based off the type of light it is
	virtual ColorRGB CalculateLighting(const IntersectResponse& a_ir, const Vector3& a_eyePos, float a_shadowFactor = 1.0f) const = 0;
	// we will need to ahve a funtion to get the direction to the light from a given point
	virtual Vector3 GetDirectionToLight(const Vector3& a_point = Vector3(0.0f, 0.0f, 0.0f)) const;
	// Get and Set light matrix
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);
	// Get and set the position of the light
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);
	// Set and Get the color of the light
	const ColorRGB& GetColor() const { return m_colorRGB; }
	void SetColor(const ColorRGB& a_color) { m_colorRGB = a_color; }

protected:
	Matrix4 m_Transform;		// Transform of the light
	ColorRGB m_colorRGB;		// Color of the light
};
