#include "Scene.h"
#include "Primitive.h"
#include "Camera.h"
#include "Light.h"

Scene::Scene() : m_pCamera(nullptr)
{
	m_objects.clear();
	m_lights.clear();
}

Scene::~Scene()
{
	m_pCamera = nullptr;
	m_objects.clear();
	m_lights.clear();
}

void Scene::AddObject(const Primitive* a_object)
{
	m_objects.push_back(a_object);
}

void Scene::RemoveObject(const Primitive* a_object)
{
	for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if (*iter == a_object)			// we have located the object
		{
			iter = m_objects.erase(iter);	// delete the object from the vector
		}
	}
}

void Scene::AddLight(const Light* a_light)
{
	m_lights.push_back(a_light);
}

void Scene::RemoveLight(const Light* a_light)
{
	for (auto iter = m_lights.begin(); iter != m_lights.end(); iter++)
	{
		if (*iter == a_light)				// we have located the light
		{
			iter = m_lights.erase(iter);	// remove the light from the vector
		}
	}
}

Ray Scene::GetScreenRay(const Vector2& a_screenSpacePos)const
{
	return m_pCamera->CastRay(a_screenSpacePos);
}


Vector3 Scene::CastRay(const Ray& a_ray, int a_bounces) const
{
	if (a_bounces <= 0)							// number of bounces remaining for ray (prevents recursion to infinity)
	{
		return ColorRGB(0.0f, 0.0f, 0.0f);		// number of bounces exceeded return color of black - no reflection due to attenuation
	}

	IntersectResponse ir;
	if (IntersectTest(a_ray, ir))	// If true an intersection has occured
	{
		// Calculate Lighting
		Vector3 rayColor = Vector3(0.0f, 0.0f, 0.0f);
		// For all lights in the scene sum the effects the lights have on the object
		for (auto lightIter = m_lights.begin(); lightIter != m_lights.end(); lightIter++)
		{
			// Test to see if in shadow -- cast ray from intersection twoard light
			Ray shadowRay = Ray(ir.HitPos, -(*lightIter)->GetDirectionToLight(ir.HitPos), 0.001f);
			IntersectResponse sr;
			float shadowValue = (!IntersectTest(shadowRay, sr));	// Call hit test on the shadow ray to see if we have an occluder
			rayColor += (*lightIter)->CalculateLighting(ir, m_pCamera->GetPosition()) * shadowValue;
			// If material hit is transparent and refractive we need to calculate the refraction vector
			// and create a new ray to project into the scene
			Ray refractRay;
			ColorRGB refractionColor = ColorRGB(0.0f, 0.0f, 0.0f);
			if (ir.material->CalcRefraction(a_ray, ir, refractRay))
			{
				refractionColor = CastRay(refractRay, a_bounces - 1) * ir.material->GetTransparency();
			}
			// if the material hit is reflective, calculate reflection vector and create new ray to project into the scene
			ColorRGB reflectionColor = ColorRGB(0.0f, 0.0f, 0.0f);
			Ray bounceRay;
			if (ir.material->CalcReflection(a_ray, ir, bounceRay))
			{
				reflectionColor = CastRay(bounceRay, a_bounces - 1) * ir.material->GetReflective();
				rayColor += reflectionColor;
			}
			// if the material is relective and transparent we need to calculate the ratio of each reflective and refractive color
			// use schlicks approximation to claculate fresnel term for object
			if (ir.material->GetReflective() > 0.0f && ir.material->GetTransparency() > 0.0f)
			{
				float reflectance = ir.material->Schlick(a_ray, ir);
				rayColor += reflectionColor * reflectance + refractionColor * (1.0f - reflectance);
			}
			else
			{
				rayColor += reflectionColor + refractionColor;
			}
		}
		return rayColor;
	}
	else
	{
		Vector3 rayToColor = RayToColor(a_ray);
		// Use lerp to get a color between white and blue based on the vertical value of the ray color
		rayToColor = Lerp(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.4f, 0.7f, 1.0f), rayToColor.y);
		return rayToColor;
	}
}

bool Scene::IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const
{
	// Set the current hit distance to be very far away
	float intersectDist = a_ray.MaxDistance();			// FLT_MAX is the maximum positive value that a float can store
	bool intersectionOccured = false;
	IntersectResponse objectIntersection;
	// For each object in the world, test to see if the ray intersects with the object
	for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Primitive* object = (*iter);							// Get a pointer to primitive object
		if (object->IntersectTest(a_ray, objectIntersection))		// perform intersection test on each object
		{
			if (objectIntersection.distance > a_ray.MinDistance())
			{
				intersectionOccured = true;
				if (objectIntersection.distance < intersectDist)		// if closer than prior intersection
				{
					intersectDist = objectIntersection.distance;		// overwrite with the new intersection distance
					a_ir = objectIntersection;							// copy the data from the intersection response
				}
			}
		}
	}
	return intersectionOccured;
}