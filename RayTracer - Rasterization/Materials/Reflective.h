#ifndef REFLECTIVE
#define REFLECTIVE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/03/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "PerfectSpecular.h"
#include "World.h"


class Reflective:public Material
{
	public:

		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;
		GlossySpecular* specularBRDF;
		PerfectSpecular* perfectSpecularBRDF;

		RGBColor rimColor;

		//Constructors
		Reflective(void);										//Default Constructor
		Reflective(Sampler* sampler);

		//Destructor

		~Reflective(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, const RGBColor& colorObj);
		void SetDiffuseBRDF(const float& kd, const RGBColor& colorObj);
		void SetSpecularBRDF(const float& ks, const RGBColor& colorObj, const float& eVal);
		void SetPerfectSpecularBRDF(const float& kr, const RGBColor& colorObj);
		void SetRimColor(const RGBColor& colorObj);
		RGBColor PhongShade(ShadeRecord &sr);
		RGBColor Shade(ShadeRecord &sr);
		RGBColor PathShade(ShadeRecord &sr);
};

#endif
