#pragma once

#include <iostream>
#include <Vector3.h>
#include <Ray.h>

//\--------------------------------------------------------------------------
// Set Up ColorRgb to be an alias for Vector3
//\--------------------------------------------------------------------------
using ColorRGB = Vector3;

void WriteColorRGB(std::ostream& a_ostream, ColorRGB a_color);

//\--------------------------------------------------------------------------
// Function to transform ray from world space direction to color value
// Direction is in space -1 -> 1, color data in space 0 -> 1
//\--------------------------------------------------------------------------
ColorRGB RayToColor(const Ray& a_ray);