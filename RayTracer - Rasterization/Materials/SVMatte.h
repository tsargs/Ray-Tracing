#ifndef SVMATTE
#define SVMATTE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "Texture.h"
#include "SVLambertian.h"
#include "World.h"

//class World;

class SVMatte:public Material
{
	public:

		SVLambertian* ambientBRDF;
		SVLambertian* diffuseBRDF;

		//Constructors
		SVMatte(void);										//Default Constructor
		SVMatte(Sampler* sampler);

		//Destructor

		~SVMatte(void);

		//Member Functions

		void SetAmbientBRDF(const float& ka, Texture* texturePointer);
		void SetDiffuseBRDF(const float& kd, Texture* texturePointer);
		void SetNormalMap(Texture* texturePointer);
		RGBColor Shade(ShadeRecord &sr);
};

#endif
