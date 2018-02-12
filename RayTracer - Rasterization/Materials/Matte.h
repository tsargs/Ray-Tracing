#ifndef MATTE
#define MATTE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Lambertian.h"
#include "World.h"

class Matte:public Material
{
	public:

		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;

		//Constructors
		Matte(void);										//Default Constructor
		Matte(Sampler* sampler);

		//Destructor

		~Matte(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, const RGBColor& colorObj);
		void SetDiffuseBRDF(const float& kd, const RGBColor& colorObj);
		RGBColor Shade(ShadeRecord &sr);
		RGBColor PathShade(ShadeRecord &sr);
};

#endif
