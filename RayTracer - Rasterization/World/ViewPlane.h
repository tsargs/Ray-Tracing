#ifndef VIEW_PLANE
#define VIEW_PLANE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Sampler.h"
#include "RegularSampler.h"
#include "JitteredSampler.h"

class ViewPlane
{
	public:
		
		int width;				//Number of pixel columns
		int height;				//Number of pixel rows
		float pixelSize;		//Size of a pixel square
		int samplesPerPixel;

		Sampler *samplerPtr;
		

		//Constructors

		ViewPlane(void);												//Default Constructor
		ViewPlane(const int& widthVal, const int& heightVal, const float& sizeVal);
		
		//Destructor

		~ViewPlane(void);

		//Member Functions

		void SetResolution(const int& widthVal, const int& heightVal, const float& sizeVal);
		void SetSampler(int type, int noOfSamples);
};

inline void ViewPlane::SetResolution(const int& widthVal, const int& heightVal, const float& sizeVal)
{
	width = widthVal;
	height = heightVal;
	pixelSize = sizeVal;
}

#endif
