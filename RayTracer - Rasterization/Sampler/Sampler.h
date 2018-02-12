#ifndef SAMPLER
#define SAMPLER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/19/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Point2D.h"
#include "Point3D.h"
#include "Constants.h"
#include <vector>
#include <iostream>
#include <math.h>

class Sampler
{
	public:
		
		int numberOfSamples;
		int numberOfSets;
		int currentSample;
		int jump;
		std::vector<Point2D> samples;
		std::vector<Point3D> hemiSphericalSamples;
		std::vector<Point2D> circularSamples;  //Disk
		
		//Constructors

		Sampler(void);												//Default Constructor
		Sampler(int noOfSamples);												
				
		//Destructor

		~Sampler(void);

		//Member Functions

		virtual void GenerateSamples (void);
		void MapSamplesToHemiSphere(const float& e);
		void MapSamplesToCircle(void);
		Point2D FetchSample(void);
		Point3D FetchHemisPhericalSample(void);
		Point2D FetchCircularSample(void);
};

#endif
