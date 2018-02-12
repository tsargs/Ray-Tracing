#ifndef GLOSSYREFLECTIVE
#define GLOSSYREFLECTIVE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/03/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "PerfectSpecular.h"
#include "World.h"


class GlossyReflective:public Material
{
	public:

		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;
		GlossySpecular* specularBRDF;
		PerfectSpecular* perfectSpecularBRDF;

		Sampler *localSampler;

		Vector3D u, v, w;
		Vector3D up = Vector3D(0.0072, 1, 0.0034);

		//Constructors
		GlossyReflective(void);										//Default Constructor
		GlossyReflective(Sampler* sampler);

		//Destructor

		~GlossyReflective(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, const RGBColor& colorObj);
		void SetDiffuseBRDF(const float& kd, const RGBColor& colorObj);
		void SetSpecularBRDF(const float& ks, const RGBColor& colorObj, const float& eVal);
		void SetPerfectSpecularBRDF(const float& kr, const RGBColor& colorObj);
		RGBColor PhongShade(ShadeRecord &sr);
		RGBColor Shade(ShadeRecord &sr);
};

#endif
