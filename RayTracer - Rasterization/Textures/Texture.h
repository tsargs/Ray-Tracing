#ifndef TEXTURE
#define TEXTURE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ShadeRecord.h"


class Texture
{
	public:
		
		//Constructors
		Texture(void);										//Default Constructor


		//Destructor

		~Texture(void);

		//Member Functions

		//Pure virtual function to get the color at particular hit point
		virtual RGBColor GetColor(const ShadeRecord& sr) const = 0;
};

#endif
