#ifndef MATERIAL
#define MATERIAL

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ShadeRecord.h"

class Material
{
	public:

		//Constructors
		Material(void);										//Default Constructor

		//Destructor

		~Material(void);

		//Member Functions

		virtual RGBColor Shade(ShadeRecord &sr);
		virtual RGBColor PathShade(ShadeRecord &sr);
		virtual RGBColor GetEmittedRadiance(ShadeRecord &sr);
};

#endif
