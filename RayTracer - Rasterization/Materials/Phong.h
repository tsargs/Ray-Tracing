#ifndef PHONG
#define PHONG

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "World.h"

class Phong:public Material
{
	public:

		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;
		GlossySpecular* specularBRDF;

		RGBColor rimColor;

		//Constructors
		Phong(void);										//Default Constructor
		Phong(Sampler* sampler);

		//Destructor

		~Phong(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, const RGBColor& colorObj);
		void SetDiffuseBRDF(const float& kd, const RGBColor& colorObj);
		void SetSpecularBRDF(const float& ks, const RGBColor& colorObj, const float& eVal);
		void SetRimColor(const RGBColor& colorObj);
		RGBColor Shade(ShadeRecord &sr);
};

#endif
