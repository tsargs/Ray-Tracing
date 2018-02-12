#ifndef SVTRANSPARENT
#define SVTRANSPARENT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/11/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "PerfectSpecular.h"
#include "World.h"


class SVTransparent:public Material
{
	public:

		SVLambertian* ambientBRDF;
		SVLambertian* diffuseBRDF;
		GlossySpecular* specularBRDF;
		SVPerfectSpecular* perfectSpecularBRDF;

		float kt;
		float eta;
		float invEta;
		float invEtaSquared;
		float etaSquared;

		RGBColor rimColor;

		//Constructors
		SVTransparent(void);										//Default Constructor
		SVTransparent(Sampler* sampler);

		//Destructor

		~SVTransparent(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, Texture* texturePointer);
		void SetDiffuseBRDF(const float& kd, Texture* texturePointer);
		void SetSpecularBRDF(const float& ks, const RGBColor& colorObj, const float& eVal);
		void SetPerfectSpecularBRDF(const float& kr, const RGBColor& colorObj);
		void SetTransparentProperties(const float& ktVal, const float& etaVal);
		void SetNormalMap(Texture* texturePointer);
		RGBColor PhongShade(ShadeRecord &sr);
		RGBColor Shade(ShadeRecord &sr);
		bool CheckForTotalInternalReflection(const Ray& ray, const Vector3D& normal);
		RGBColor CalculateTransmittedColor(const Ray& ray, const Vector3D& normal, Vector3D& wt);
};

#endif
