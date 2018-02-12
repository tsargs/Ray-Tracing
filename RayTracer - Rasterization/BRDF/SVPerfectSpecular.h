#ifndef SVPERFECTSPECULAR
#define SVPERFECTSPECULAR

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/04/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BRDF.h"
#include "Texture.h"
#include <iostream>

class SVPerfectSpecular:public BRDF
{
	public:
		
		float kr; // Reflection coefficient
		Texture *texturePtr;
		Texture *normalTexPtr;

		RGBColor reflectiveColor;

		//Constructors
		SVPerfectSpecular(void);										//Default Constructor
		SVPerfectSpecular(Sampler* samplerPointer);
		SVPerfectSpecular(const float& kdVal, const RGBColor& colorObj);
		SVPerfectSpecular(const SVPerfectSpecular& svPerfectSpecular);
		
		//Destructor

		~SVPerfectSpecular(void);

		//Member Functions

		SVPerfectSpecular& operator=(const SVPerfectSpecular& svPerfectSpecular);		//Assignment Operator

		RGBColor GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const;
		RGBColor SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const;
		RGBColor Rho(const ShadeRecord& sr, const Vector3D& wo) const;
		
		Vector3D GetNormal(const ShadeRecord& sr) const;
};

#endif
