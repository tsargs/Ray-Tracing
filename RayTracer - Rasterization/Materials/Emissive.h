#ifndef EMISSIVE
#define EMISSIVE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Material.h"
#include "World.h"

class Emissive:public Material
{
	public:

		float radianceFactor;
		RGBColor emissiveColor;
		RGBColor colorProduct;

		//Constructors
		Emissive(void);										//Default Constructor
		Emissive(const float& rVal, const RGBColor& colorObj);

		//Destructor

		~Emissive(void);

		//Member Functions

		RGBColor Shade(ShadeRecord &sr);
		RGBColor PathShade(ShadeRecord &sr);
		RGBColor GetEmittedRadiance(ShadeRecord &sr);
};

#endif
