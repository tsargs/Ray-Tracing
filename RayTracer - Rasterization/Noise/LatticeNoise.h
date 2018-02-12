#ifndef LATTICENOISE
#define LATTICENOISE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Constants.h"
#include "Point3D.h"

#define PERMUTATION(x)		permTable[x & (tableSize-1)]
#define INDEX(iX, iY, iZ)	PERMUTATION(iX + PERMUTATION(iY + PERMUTATION(iZ)))

class LatticeNoise
{
	public:
		
		const int tableSize = 256;
		float *valueTable;
		float octaves;
		float fractalSumMin;
		float fractalSumMax;
		int *permTable;
		float gain;
		float lacunarity;

		//Constructors
		LatticeNoise(void);										//Default Constructor

		//Destructor

		~LatticeNoise(void);

		//Member Functions
		void InitializeValueTable(void);
		void SetNumberOfOctaves(const int& n);
		void SetGainLacunarity(const float& gainVal, const float& lacunarityVal);
		float GetFractalSumValue(const Vector3D& point);
		float GetTurbulence(const Vector3D& point);
		float GetFBMValue(const Vector3D& point);

		//Pure virtual function to get the noise value for particular hit point
		virtual float GetNoiseValue(const Vector3D& point) const = 0;
};

inline void LatticeNoise::SetNumberOfOctaves(const int& n)
{
	octaves = n;
	if (gain == 1.0)
		fractalSumMax = octaves;
	else
		fractalSumMax = (1.0 - pow(gain, octaves)) / (1.0 - gain);

	fractalSumMin = -fractalSumMax;

	std::cout << "Max: " << fractalSumMax << "\n";
	std::cout << "Min: " << fractalSumMin << "\n";
}

inline void LatticeNoise::SetGainLacunarity(const float& gainVal, const float& lacunarityVal)
{
	gain = gainVal;
	lacunarity = lacunarityVal;
}

#endif
