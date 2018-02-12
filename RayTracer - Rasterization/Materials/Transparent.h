#ifndef TRANSPARENT
#define TRANSPARENT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/10/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "PerfectSpecular.h"
#include "World.h"


class Transparent:public Material
{
	public:

		Lambertian* ambientBRDF;
		Lambertian* diffuseBRDF;
		GlossySpecular* specularBRDF;
		PerfectSpecular* perfectSpecularBRDF;

		float kt;
		float eta;
		float invEta;
		float invEtaSquared;
		float etaSquared;

		//Constructors
		Transparent(void);										//Default Constructor
		Transparent(Sampler* sampler);

		//Destructor

		~Transparent(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, const RGBColor& colorObj);
		void SetDiffuseBRDF(const float& kd, const RGBColor& colorObj);
		void SetSpecularBRDF(const float& ks, const RGBColor& colorObj, const float& eVal);
		void SetPerfectSpecularBRDF(const float& kr, const RGBColor& colorObj);
		void SetTransparentProperties(const float& ktVal, const float& etaVal);
		RGBColor PhongShade(ShadeRecord &sr);
		RGBColor Shade(ShadeRecord &sr);
		bool CheckForTotalInternalReflection(const Ray& ray, const Vector3D& normal);
		RGBColor CalculateTransmittedColor(const Ray& ray, const Vector3D& normal, Vector3D& wt);
};

#endif
