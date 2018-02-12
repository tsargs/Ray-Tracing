#ifndef MAPPING
#define MAPPING

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ShadeRecord.h"
#include "Image.h"

class Mapping
{
	public:
		
		//Constructors
		Mapping(void);										//Default Constructor


		//Destructor

		~Mapping(void);

		//Member Functions

		//Pure virtual function to get the color at particular hit point
		virtual RGBColor MapToImage(const ShadeRecord& sr, Image* imagePtr) const = 0;
};

#endif
