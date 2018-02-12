// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BRDF.h"

//Default Constructor
BRDF::BRDF(void) : samplerPtr(nullptr)
{
	
}

BRDF::BRDF(Sampler* samplerPointer)
{
	samplerPtr = samplerPointer;
}

//Destructor
BRDF::~BRDF(void)
{

}


