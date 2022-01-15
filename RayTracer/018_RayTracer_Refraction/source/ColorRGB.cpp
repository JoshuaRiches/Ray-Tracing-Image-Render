#include "ColorRGB.h"

void WriteColorRGB(std::ostream& a_ostream, ColorRGB a_color)
{
	// Cast float values to int for output to file
	a_ostream <<	static_cast<int>(255.999f * a_color.x) << ' ' <<
					static_cast<int>(255.999f * a_color.y) << ' ' <<
					static_cast<int>(255.999f * a_color.z) << ' ';
}
//\-----------------------------------------------------------------------------
//\ Function to transform ray from world space direction to color value
//\ Direction is in space -1 -> 1, color data in space 0 -> 1
//\-----------------------------------------------------------------------------
ColorRGB RayToColor(const Ray& a_ray)
{
	return (a_ray.Direction() + 1.0f) * 0.5f;
}