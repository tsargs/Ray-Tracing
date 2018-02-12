#ifndef SVREFLECTIVE
#define SVREFLECTIVE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/04/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Texture.h"
#include "SVLambertian.h"
#include "GlossySpecular.h"
#include "SVPerfectSpecular.h"
#include "World.h"

class SVReflective:public Material
{
	public:

		SVLambertian* ambientBRDF;
		SVLambertian* diffuseBRDF;
		GlossySpecular* specularBRDF;
		SVPerfectSpecular* svPerfectSpecularBRDF;

		RGBColor reflectiveColor;

		//Constructors
		SVReflective(void);										//Default Constructor
		SVReflective(Sampler* sampler);

		//Destructor

		~SVReflective(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, Texture* texturePointer);
		void SetDiffuseBRDF(const float& kd, Texture* texturePointer);
		void SetSpecularBRDF(const float& ks, const RGBColor& colorObj, const float& eVal);
		void SetPerfectSpecularBRDF(const float& kr, const RGBColor& colorObj);
		void SetNormalMap(Texture* texturePointer);
		RGBColor PhongShade(ShadeRecord &sr);
		RGBColor Shade(ShadeRecord &sr);
};

#endif
