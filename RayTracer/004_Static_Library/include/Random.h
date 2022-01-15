#pragma once
//\-----------------------------------------------------------
//\ Class that implements a random number generator (LCG)
//\ use folowing rule:
//\						seed = (a*seed + c) & m;
//\						randomint = seed & L;
//\-----------------------------------------------------------
namespace Random
{
	// gets current seed
	int					GetSeed();
	// sets current seed
	void				SetSeed(const int& iSeed);
	// gets maximum allowed int
	int					RandMax();

	// Random integer number generator
	int					RandInt();
	int					RandRange(const int& iMin, const int& iMax);
	// Random float number generator from 0.0f to 1.0f
	float				RandFloat();
	// Random float number generator from interval [x0, x1]
	float				RandRange(const float& fX0, const float& fX1);
};