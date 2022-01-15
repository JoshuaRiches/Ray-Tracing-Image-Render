#pragma once

#include <vector>
#include <libMath.h>
#include "IntersectionResponse.h"

class Primitive;
class Camera;
class Light;

class Scene
{
public:
	// Constructor and destructor
	Scene();
	~Scene();

	// Add and remove object to the scene (pass in the primitive object you want to add/remove)
	void AddObject(const Primitive* a_object);
	void RemoveObject(const Primitive* a_object);

	void AddLight(const Light* a_light);
	void RemoveLight(const Light* a_light);

	Ray GetScreenRay(const Vector2& a_screenSpacePos)const;
	Vector3 CastRay(const Ray& a_ray, int a_bounces) const;
	// Test all objects in the world against the ray passed in from the camera, stores intersect info in the passed in intersect response
	bool IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const;

	void SetCamera(Camera* a_pCamera) { m_pCamera = a_pCamera; }

private:
	std::vector<const Primitive*> m_objects;
	std::vector<const Light*> m_lights;
	Camera* m_pCamera;
};