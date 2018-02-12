// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/19/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Sampler.h"
#include <stdlib.h>

//Default Constructor
Sampler::Sampler(void) : numberOfSamples(1), numberOfSets(83), currentSample(0), jump(0)
{
	samples.reserve(numberOfSamples*numberOfSets);
}


Sampler::Sampler(int noOfSamples) : numberOfSamples(noOfSamples), numberOfSets(83), currentSample(0), jump(0)
{
	samples.reserve(numberOfSamples*numberOfSets);
}

//Destructor
Sampler::~Sampler(void)
{

}


void Sampler::GenerateSamples(void)
{

}

void Sampler::MapSamplesToHemiSphere(const float& e)
{
	hemiSphericalSamples.reserve(numberOfSamples*numberOfSets);

	float exponent = 1 / (e + 1);

	int n = samples.size();
	for (int i = 0; i < n; i++)
	{
		float x = samples[i].x;
		float y = samples[i].y;

		float cosPhi = cos(2 * pi * x);
		float sinPhi = sin(2 * pi * x);

		float cosTheta = pow((1 - y), exponent);
		float sinTheta = sqrt(1 - (cosTheta * cosTheta));

		float u = sinTheta * cosPhi;
		float v = sinTheta * sinPhi;
		float w = cosTheta;

		hemiSphericalSamples.push_back(Point3D(u,v,w));
	}
}

void Sampler::MapSamplesToCircle(void)
{
	std::cout << "\nMapSamplesToCircle\n";
	circularSamples.reserve(numberOfSamples*numberOfSets);

	float radius, phi;
	Point2D samplePoint;

	for (int i = 0; i < samples.size(); i++)
	{
		float x = 2 * samples[i].x - 1;
		float y = 2 * samples[i].y - 1;

		if (x > y)
		{
			if (x > -y)
			{
				radius = x;
				phi = piBy4 * (y / x);
			}
			else
			{
				radius = -y;
				phi = piBy4 * (6 - (x / y));
			}
		}
		else
		{
			if (x > -y)
			{
				radius = y;
				phi = piBy4 * (2 - (x / y));
			}
			else
			{
				radius = -x;
				if (x != 0)
					phi = piBy4 * (4 + (y / x));
				else
					phi = 0;
			}
		}

		samplePoint.x = radius * cos(phi);
		samplePoint.y = radius * sin(phi);

		circularSamples.push_back(samplePoint);
	}
}

//Fetch Samples Function - First version
Point2D Sampler::FetchSample(void)
{
	if (currentSample%numberOfSamples == 0)
	{
		jump = rand() % numberOfSets;
	}
	return samples[currentSample++ %numberOfSamples + jump * numberOfSamples];
}

Point3D Sampler::FetchHemisPhericalSample(void)
{
	if (currentSample%numberOfSamples == 0)
	{
		jump = rand() % numberOfSets;
	}
	return hemiSphericalSamples[currentSample++ %numberOfSamples + jump * numberOfSamples];
}

Point2D Sampler::FetchCircularSample(void)
{
	if (currentSample%numberOfSamples == 0)
	{
		jump = rand() % numberOfSets;
	}
	return circularSamples[currentSample++ %numberOfSamples + jump * numberOfSamples];
}