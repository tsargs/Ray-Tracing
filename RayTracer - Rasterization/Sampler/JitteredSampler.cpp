// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/27/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "JitteredSampler.h"

//Default Constructor
JitteredSampler::JitteredSampler(void)
{
	numberOfSamples = 1;
	numberOfSets = 83;
	currentSample = 0;
	jump = 0;
	samples.reserve(numberOfSamples*numberOfSets);
}

JitteredSampler::JitteredSampler(int noOfSamples)
{
	numberOfSamples = noOfSamples;
	numberOfSets = 83;
	currentSample = 0;
	jump = 0;
	samples.reserve(numberOfSamples*numberOfSets);

	GenerateSamples();
	MapSamplesToHemiSphere(1);
}


//Destructor
JitteredSampler::~JitteredSampler(void)
{

}

//Generate Samples Function
void JitteredSampler::GenerateSamples(void)
{
	
	std::cout << "\nJitteredSampler: GenerateSamples"<<numberOfSamples<<"\n";
	int n = sqrt(numberOfSamples);
	std::cout << "n: " << n << "\n";
	int index = 0;
	for (int i = 0; i < numberOfSets; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				samples.push_back(Point2D((k+(float)(rand()*inverseRandMax))/n, (j+(float)(rand()*inverseRandMax))/n));
				//std::cout << "Point2D: " << (j + 0.5) / n << ", " << (k + 0.5) / n << "\n";
			}
		}
	}
}
