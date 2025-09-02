#pragma once
#include "Vector3.h"

struct IntersectResponse
{
	Vector3 hitPos;
	Vector3 surfaceNormal;
	float distance;
	Vector3 colour;
};