#ifndef FUNCTIONMAPPING
#define FUNCTIONMAPPING

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Mapping.h"
#include "Math.h"
#include "Constants.h"

class FunctionMapping:public Mapping
{
	public:
		
		//Constructors
		FunctionMapping(void);										//Default Constructor


		//Destructor

		~FunctionMapping(void);

		//Member Functions

		//Pure virtual function to get the color at particular hit point
		RGBColor MapToImage(const ShadeRecord& sr, Image* imagePtr) const;
};

#endif
