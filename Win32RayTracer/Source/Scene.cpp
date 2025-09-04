#include "Scene.h"
#include "Primitive.h"

Scene::Scene()
{
	m_objects.clear();
}

Scene::~Scene()
{
	m_objects.clear();
}

void Scene::AddObject(const Primitive* a_object)
{
	m_objects.push_back(a_object);
}

void Scene::RemoveObject(const Primitive* a_object)
{
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if (*iter == a_object)
		{
			iter = m_objects.erase(iter);
		}
	}
}

bool Scene::IntersectTest(const Ray& a_ray, IntersectResponse& a_ir)
{
	float intersectDist = FLT_MAX;
	bool intersectionOccured = false;
	IntersectResponse objectIntersection;
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		const Primitive* object = (*iter);
		if (object->IntersectTest(a_ray, objectIntersection))
		{
			intersectionOccured = true;
			if (objectIntersection.distance < intersectDist)
			{
				intersectDist = objectIntersection.distance;
				a_ir = objectIntersection;
			}
		}
	}
	return intersectionOccured;
}