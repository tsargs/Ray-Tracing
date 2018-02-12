#ifndef RECTANGULARMAPPING
#define RECTANGULARMAPPING

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Mapping.h"
#include "Constants.h"

class RectangularMapping:public Mapping
{
	public:
		
		//Constructors
		RectangularMapping(void);										//Default Constructor


		//Destructor

		~RectangularMapping(void);

		//Member Functions

		//Pure virtual function to get the color at particular hit point
		RGBColor MapToImage(const ShadeRecord& sr, Image* imagePtr) const;
};

#endif
