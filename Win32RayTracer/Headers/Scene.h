#pragma once

#include <vector>
#include "IntersectionResponse.h"
#include "Ray.h"

class Primitive;

class Scene
{
public: 
	Scene();
	~Scene();
	
	void AddObject(const Primitive* a_object);
	void RemoveObject(const Primitive* a_object);

	bool IntersectTest(const Ray& a_ray, IntersectResponse& a_ir);
private:
	std::vector<const Primitive*> m_objects;
};