// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/19/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "RegularSampler.h"

//Default Constructor
RegularSampler::RegularSampler(void)
{
	numberOfSamples = 1;
	numberOfSets = 83;
	currentSample = 0;
	jump = 0;
	samples.reserve(numberOfSamples*numberOfSets);
}

RegularSampler::RegularSampler(int noOfSamples) 
{
	std::cout << "Inside Constructor\n";
	numberOfSamples = noOfSamples;
	numberOfSets = 83;
	currentSample = 0;
	jump = 0;
	samples.reserve(numberOfSamples*numberOfSets);
	GenerateSamples();
	MapSamplesToHemiSphere(1);
}


//Destructor
RegularSampler::~RegularSampler(void)
{

}

//Generate Samples Function
void RegularSampler::GenerateSamples(void)
{
	std::cout << "\nRegularSampler: GenerateSamples\n";
	int n = sqrt(numberOfSamples);
	std::cout << "n: " << n << "\n";
	int index = 0;
	for (int i = 0; i < numberOfSets; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				samples.push_back(Point2D((j+0.5)/n, (k+0.5)/n));
				//std::cout << "Point2D: " << (j + 0.5) / n << ", " << (k + 0.5) / n << "\n";
			}
		}
	}
}
