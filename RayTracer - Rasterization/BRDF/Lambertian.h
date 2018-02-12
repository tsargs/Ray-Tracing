#ifndef LAMBERTIAN
#define LAMBERTIAN

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BRDF.h"
#include <iostream>

class Lambertian:public BRDF
{
	public:
		
		float kd; // Diffuse reflection coefficient
		RGBColor diffuseColor;

		//Constructors
		Lambertian(void);										//Default Constructor
		Lambertian(Sampler* samplerPointer);
		Lambertian(const float& kdVal, const RGBColor colorObj);
		Lambertian(const Lambertian& lambertian);
		
		//Destructor

		~Lambertian(void);

		//Member Functions

		Lambertian& operator=(const Lambertian& lambertian);		//Assignment Operator

		RGBColor GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const;
		RGBColor SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const;
		RGBColor Rho(const ShadeRecord& sr, const Vector3D& wo) const;
};

#endif
