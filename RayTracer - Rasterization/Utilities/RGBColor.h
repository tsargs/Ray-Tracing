#ifndef RGBCOLOR
#define RGBCOLOR

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <iostream>

class RGBColor
{
	public:
		float r, g, b;

	//Constructors
		RGBColor(void);										//Default Constructor
		RGBColor(float rVal, float gVal, float bVal);
		RGBColor(const RGBColor& color);					//Copy constructor

		~RGBColor(void);									//Destructor

	//Member Functions
		RGBColor& operator=(const RGBColor& color);				//Assignment operator
		RGBColor& operator+=(const RGBColor& color);			//Addition & Assignment operator
		RGBColor operator* (const float constant) const;		//Multiplication with a float value
		RGBColor operator* (const RGBColor& colorObj) const;	//Multiplication with a color object
		RGBColor operator/ (const float constant) const;		//Division by a float value
		RGBColor operator+ (const RGBColor& colorObj) const;	//Addition with another color

		RGBColor ClampBasedOnMaxValue(void);					//Multiplication with a color object
		float FindMax(const float& a, const float& b, const float& c);
		void PrintValues(void);
};

#endif