#pragma once

namespace Random
{
	int GetSeed();
	void SetSeed(const int& iSeed);
	int RandMax();
	int RandInt();
	int RandRange(const int& iMin, const int& iMax);
	float RandFloat();
	float RandRange(const float& fX0, const float& fX1);
}