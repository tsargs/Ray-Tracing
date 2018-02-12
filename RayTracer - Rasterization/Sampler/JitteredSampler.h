#ifndef JITTEREDSAMPLER
#define JITTEREDSAMPLER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/27/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Sampler.h"

class JitteredSampler:public Sampler
{
	public:
		
		//Constructors

		JitteredSampler(void);												//Default Constructor
		JitteredSampler(int noOfSamples);
				
		//Destructor

		~JitteredSampler(void);

		//Member Functions

		void GenerateSamples (void);
};

#endif
