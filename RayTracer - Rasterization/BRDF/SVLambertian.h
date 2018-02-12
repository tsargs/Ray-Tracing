#ifndef SVLAMBERTIAN
#define SVLAMBERTIAN

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BRDF.h"
#include "Texture.h"
#include <iostream>
//#include "World.h"

class world;

class SVLambertian:public BRDF
{
	public:
		
		float kd; // Diffuse reflection coefficient
		Texture *texturePtr;
		Texture *normalTexPtr;

		//Constructors
		SVLambertian(void);										//Default Constructor
		SVLambertian(Sampler* samplerPointer);
		SVLambertian(const float& kdVal, Texture* texturePointer);
		SVLambertian(const SVLambertian& svLambertian);
		
		//Destructor

		~SVLambertian(void);

		//Member Functions

		SVLambertian& operator=(const SVLambertian& svlambertian);		//Assignment Operator

		RGBColor GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const;
		RGBColor SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const;
		RGBColor Rho(const ShadeRecord& sr, const Vector3D& wo) const;
		
		Vector3D GetNormal(const ShadeRecord& sr) const;
		float GetEta(const ShadeRecord& sr, const float& normalizedVal) const;
};

#endif
