#ifndef FBMTEXTURE
#define FBMTEXTURE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Texture.h"
#include "LatticeNoise.h"

class FBMTexture:public Texture
{
	public:

		LatticeNoise *noisePtr;
		RGBColor color;
		float minValue, maxValue;
		
		//Constructors
		FBMTexture(void);										//Default Constructor
		FBMTexture(LatticeNoise* noisePointer);

		//Destructor

		~FBMTexture(void);

		//Member Functions
		void SetColor(const RGBColor& colorVal);
		void SetMinMaxValues(const float& minVal, const float& maxVal);

		//Pure virtual function to get the color at particular hit point
		RGBColor GetColor(const ShadeRecord& sr) const;
};

#endif
