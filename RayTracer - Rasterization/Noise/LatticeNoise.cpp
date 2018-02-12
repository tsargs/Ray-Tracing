// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "LatticeNoise.h"

//Default Constructor
LatticeNoise::LatticeNoise(void)
{
	InitializeValueTable();
}

//Destructor
LatticeNoise::~LatticeNoise(void)
{

}

void LatticeNoise::InitializeValueTable(void)
{
	valueTable = new float[tableSize];
	//Values taken from the website of book "Ray tracing from ground up"
	permTable = new int[tableSize] {225, 155,210,108,175,199,221,144,
		203, 116, 70, 213, 69, 158, 33, 252, 5, 82, 173, 133, 222, 139, 174, 27,
		9, 71, 90, 246, 75,130, 91,191, 169,138, 2, 151, 194, 235, 81, 7,
		25, 113, 228, 159, 205, 253, 134, 142,
		248, 65,224,217, 22,121,229, 63, 89,103, 96,104,156, 17,201,129,
		36,  8,165,110,237,117,231, 56,132,211,152, 20,181,111,239,218,
		170,163, 51,172,157, 47, 80,212,176,250, 87, 49, 99,242,136,189,
		162,115, 44, 43,124, 94,150, 16,141,247, 32, 10,198,223,255, 72,
		53,131, 84, 57,220,197, 58, 50,208, 11,241, 28,  3,192, 62,202,
		18,215,153, 24, 76, 41, 15,179, 39, 46, 55,  6,128,167, 23,188,
		106, 34,187,140,164, 73,112,182,244,195,227, 13, 35, 77,196,185,
		26,200,226,119, 31,123,168,125,249, 68,183,230,177,135,160,180,
		12,  1,243,148,102,166, 38,238,251, 37,240,126, 64, 74,161, 40,
		184,149,171,178,101, 66, 29, 59,146, 61,254,107, 42, 86,154,  4,
		236,232,120, 21,233,209, 45, 98,193,114, 78, 19,206, 14,118,127,
		48, 79,147, 85, 30,207,219, 54, 88,234,190,122, 95, 67,143,109,
		137,214,145, 93, 92,100,245,  0,216,186, 60, 83,105, 97,204, 52
	};

	srand(253); // Setting seed value for random numbers so that the order is same for every run

	for (int i = 0; i < tableSize; i++)
	{
		valueTable[i] = 1 - (2 * (rand()*inverseRandMax)); //rand()*inverseRandMax -> returns value in 0 to 1 range. We need values in -1 to +1 range
		//std::cout << "val: " << valueTable[i] << "\n";
	}
}

float LatticeNoise::GetFractalSumValue(const Vector3D& point)
{
	float amplitude = 1;
	float frequency = 1;
	float fractalSum = 0;

	for (int i = 0; i < octaves; i++)
	{
		fractalSum += amplitude * GetNoiseValue(point*frequency);
		amplitude *= 0.5;
		frequency *= 2;
	}

	fractalSum = (fractalSum - fractalSumMin) / (fractalSumMax - fractalSumMin);
	
	return fractalSum;
}

float LatticeNoise::GetTurbulence(const Vector3D& point)
{
	float amplitude = 1;
	float frequency = 1;
	float turbulence = 0;

	for (int i = 0; i < octaves; i++)
	{
		turbulence += amplitude * fabs(GetNoiseValue(point*frequency));
		amplitude *= 0.5;
		frequency *= 2;
	}

	turbulence /= fractalSumMax;

	return turbulence;
}

float LatticeNoise::GetFBMValue(const Vector3D& point)
{
	float amplitude = 1;
	float frequency = 1;
	float fbm = 0;

	for (int i = 0; i < octaves; i++)
	{
		fbm += amplitude * GetNoiseValue(point*frequency);
		amplitude *= gain;
		frequency *= lacunarity;
	}

	fbm = (fbm - fractalSumMin) / (fractalSumMax - fractalSumMin);

	return fbm;
}
