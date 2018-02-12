#ifndef PLAINTEXTURE
#define PLAINTEXTURE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Texture.h"


class PlainTexture:public Texture
{
	public:

		RGBColor constantColor;
		
		//Constructors
		PlainTexture(void);										//Default Constructor
		PlainTexture(const RGBColor& colorObj);

		//Destructor

		~PlainTexture(void);

		//Member Functions

		//Pure virtual function to get the color at particular hit point
		RGBColor GetColor(const ShadeRecord& sr) const;
};

#endif
