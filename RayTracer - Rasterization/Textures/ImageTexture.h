#ifndef IMAGETEXTURE
#define IMAGETEXTURE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Texture.h"
#include "Image.h"
#include "Mapping.h"


class ImageTexture:public Texture
{
	public:

		Image *imagePtr;
		Mapping *mappingPtr;
		
		//Constructors
		ImageTexture(void);										//Default Constructor
		ImageTexture(Image *imagePtr, Mapping *mappingPointer);

		//Destructor

		~ImageTexture(void);

		//Member Functions

		//Pure virtual function to get the color at particular hit point
		RGBColor GetColor(const ShadeRecord& sr) const;
};

#endif
