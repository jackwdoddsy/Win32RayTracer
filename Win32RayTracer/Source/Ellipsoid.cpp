#include "Ellipsoid.h"
#include <corecrt_math.h>

Ellipsoid::Ellipsoid() : m_radius(1.f)
{

}

Ellipsoid::Ellipsoid(const Vector3& a_position, const float& a_radius) : m_radius(a_radius)
{
	SetPosition(a_position);
	SetScale(Vector3(m_radius, m_radius, m_radius));
}

Ellipsoid::~Ellipsoid()
{

}

bool Ellipsoid::IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const
{
    const float EPSILON = 1e-6f; // tweak depending on your scene scale

    Matrix4 normalMatrix = m_Transform.GetTranspose().Inverse();
    Matrix4 invTx = m_Transform.Inverse();

    // Transform ray into object space
    Vector4 rayOrigin = invTx * Vector4(a_ray.Origin().x, a_ray.Origin().y, a_ray.Origin().z, 1.f);
    Vector4 rayDir = invTx * Vector4(a_ray.Direction().x, a_ray.Direction().y, a_ray.Direction().z, 0.f);
    rayDir.Normalize();

    Vector3 OC(rayOrigin.x, rayOrigin.y, rayOrigin.z);
    Vector3 d(rayDir.x, rayDir.y, rayDir.z);

    // Quadratic coefficients
    float b = Dot(OC, d);
    float c = Dot(OC, OC) - 1.f;
    float discriminant = b * b - c;

    if (discriminant < 0.f)
        return false;

    // Find roots
    float sqrtDisc = sqrt(discriminant);
    float i0 = -b - sqrtDisc;
    float i1 = -b + sqrtDisc;

    float dist = -1.f;
    if (i0 > EPSILON)      dist = i0;
    else if (i1 > EPSILON) dist = i1;
    else                   return false; // both behind ray start or too close

    // Hit point in object space
    Vector4 hpObj = rayOrigin + rayDir * dist;
    Vector3 nObj(hpObj.x, hpObj.y, hpObj.z);
    nObj.Normalize();

    // Transform hit point back to world space
    Vector4 hpWorld = m_Transform * hpObj;
    a_ir.hitPos = Vector3(hpWorld.x, hpWorld.y, hpWorld.z);

    // Transform normal back to world space
    Vector4 n4 = normalMatrix * Vector4(nObj.x, nObj.y, nObj.z, 0.f);
    a_ir.surfaceNormal = Vector3(n4.x, n4.y, n4.z);
    a_ir.surfaceNormal.Normalize();
    a_ir.distance = (a_ray.Origin() - Vector3(hpWorld.x, hpWorld.y, hpWorld.z)).Length();
    a_ir.colour = m_colour;

    return true;
}