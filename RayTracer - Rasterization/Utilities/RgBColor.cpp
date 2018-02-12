// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "RGBColor.h"

//Default Constructor
RGBColor::RGBColor(void) : r(0.0), g(0.0), b(0.0)
{

}


RGBColor::RGBColor(float rVal, float gVal, float bVal) : r(rVal), g(gVal), b(bVal)
{

}


//Copy constructor
RGBColor::RGBColor(const RGBColor& color): r(color.r), g(color.g), b(color.b)
{
	
}


//Destructor
RGBColor::~RGBColor(void)
{

}


//Assignment Operator
RGBColor& RGBColor::operator=(const RGBColor& color)
{
	r = color.r;
	g = color.g;
	b = color.b;

	return (*this);
}

//Addition & assignment Operator
RGBColor& RGBColor::operator+=(const RGBColor& color)
{
	r = r + color.r;
	g = g + color.g;
	b = b + color.b;

	return (*this);
}

//Multiplication with a float value
RGBColor RGBColor::operator*(const float constant) const
{
	return (RGBColor(r*constant, g*constant, b*constant));
}

//Division by a float value
RGBColor RGBColor::operator/(const float constant) const
{
	return (RGBColor(r/constant, g/constant, b/constant));
}

//Multiplication with a color object
RGBColor RGBColor::operator* (const RGBColor& colorObj) const
{
	return (RGBColor(r*colorObj.r, g*colorObj.g, b*colorObj.b));
}

RGBColor RGBColor::operator+ (const RGBColor& colorObj) const
{
	return (RGBColor(r+colorObj.r, g+colorObj.g, b+colorObj.b));
}

RGBColor RGBColor::ClampBasedOnMaxValue(void)
{
	float maxValue = FindMax(r, g, b);

	if (maxValue > 1)
	{
		r = r / maxValue;
		g = g / maxValue;
		b = b / maxValue;
	}

	return *this;
}

float RGBColor::FindMax(const float& a, const float& b, const float& c)
{
	if (a >= b)
	{
		if (a >= c)
			return a;
		else
			return c;
	}
	else
	{
		if (b >= c)
			return b;
		else
			return c;
	}
}

void RGBColor::PrintValues(void)
{
	std::cout << "r: " << r << ", g: " << g << ", b: " << b << "\n";
}
