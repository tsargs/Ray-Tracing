#ifndef BRDFCLASS
#define BRDFCLASS

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ShadeRecord.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "Sampler.h"

#include <math.h>

class BRDF
{
	public:
		
		Sampler *samplerPtr;

		//Constructors
		BRDF(void);										//Default Constructor
		BRDF(Sampler* samplerPointer);

		//Destructor

		~BRDF(void);

		//Member Functions

		//Pure virtual function to compute the BRDF based on wi - opposite direction of incoming light and wo - direction of reflection
		virtual RGBColor GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
		virtual RGBColor SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const = 0;
		virtual RGBColor Rho(const ShadeRecord &sr, const Vector3D& wo) const = 0;
};

#endif
