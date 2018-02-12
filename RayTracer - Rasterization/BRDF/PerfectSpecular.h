#ifndef PERFECTSPECULAR
#define PERFECTSPECULAR

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/03/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BRDF.h"
#include <iostream>

class PerfectSpecular:public BRDF
{
	public:
		
		float kr; // Diffuse reflection coefficient
		RGBColor reflectiveColor;

		//Constructors
		PerfectSpecular(void);										//Default Constructor
		PerfectSpecular(Sampler* samplerPointer);
		PerfectSpecular(const float& krVal, const RGBColor colorObj);
		PerfectSpecular(const PerfectSpecular& lambertian);
		
		//Destructor

		~PerfectSpecular(void);

		//Member Functions

		PerfectSpecular& operator=(const PerfectSpecular& perfectSpecular);		//Assignment Operator

		RGBColor GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const;
		RGBColor SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const;
		RGBColor Rho(const ShadeRecord& sr, const Vector3D& wo) const;
};

#endif
