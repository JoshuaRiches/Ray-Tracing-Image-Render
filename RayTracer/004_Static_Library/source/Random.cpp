#include "Random.h"
static int rand_seed = 0xC7171CA1;		// Default value for seed
// Values set to glibc (used by gcc)
static const int rand_mod = 0x80000000;	// Set Rand Mod value 2^31
static const int rand_a = 1103515245;	// Set LCG A value
static const int rand_c = 12345;		// Set LCG C value
static const int rand_l = 0x3FFFFFFF;	// Set LCG L value

int Random::GetSeed()
{
	return rand_seed;
}

// Set the seed of the RNG
void Random::SetSeed(const int& a_seed)
{
	rand_seed = a_seed;
}

//Return the maximum value the RNG can produce
int Random::RandMax()
{
	return rand_l;
}

// Generate a random integer based on the seed
int Random::RandInt()
{
	rand_seed = (rand_seed * rand_a + rand_c) % rand_mod;	// Calc seed value
	return rand_seed & rand_l;
}

// Return the range of the RNG (min -> max)
int Random::RandRange(const int& min, const int& max)
{
	return RandInt() % max + min;
}

// Generate a random float
float Random::RandFloat()
{
	return static_cast<float>(RandInt()) / static_cast<float>(RandMax());
}

// return the rnage of the RNG
float Random::RandRange(const float& min, const float& max)
{
	return min + ((max - min) * RandFloat());
}