#ifndef GLOSSYSPECULAR
#define GLOSSYSPECULAR

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "BRDF.h"
#include <iostream>

class GlossySpecular:public BRDF
{
	public:
		
		float ks; // Specular reflection coefficient
		RGBColor specularColor;
		float e; //Exponent to control the reflection lobe

		//Constructors
		GlossySpecular(void);										//Default Constructor
		GlossySpecular(Sampler* samplerPointer);
		GlossySpecular(const float& kdVal, const RGBColor colorObj, const float& eVal);
		GlossySpecular(const GlossySpecular& glossySpecular);
		
		//Destructor

		~GlossySpecular(void);

		//Member Functions

		GlossySpecular& operator=(const GlossySpecular& glossySpecular);		//Assignment Operator

		RGBColor GetBRDF(const ShadeRecord& sr, const Vector3D& wi, const Vector3D& wo) const;
		RGBColor SampleBRDF(const ShadeRecord& sr, Vector3D& wi, const Vector3D& wo) const;
		RGBColor Rho(const ShadeRecord& sr, const Vector3D& wo) const;
};

#endif
