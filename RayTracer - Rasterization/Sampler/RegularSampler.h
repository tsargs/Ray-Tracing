#ifndef REGULARSAMPLER
#define REGULARSAMPLER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/19/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Sampler.h"

class RegularSampler:public Sampler
{
	public:
		
		//Constructors

		RegularSampler(void);												//Default Constructor
		RegularSampler(int noOfSamples);
				
		//Destructor

		~RegularSampler(void);

		//Member Functions

		void GenerateSamples (void);
};

#endif
