#ifndef CUBICNOISE
#define CUBICNOISE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "LatticeNoise.h"

class CubicNoise:public LatticeNoise
{
	public:
		
		//Constructors
		CubicNoise(void);										//Default Constructor

		//Destructor

		~CubicNoise(void);

		//Member Functions

		//Pure virtual function to get the noise value for particular hit point
		float GetNoiseValue(const Vector3D& point) const;
};

//Code to find value of cubic function - taken from the website of book "Ray tracing from ground up"
template <class T> T
FourKnotSpline(const float& x, const T* knots)
{
	T c3 = -0.5 * knots[0] + 1.5 * knots[1] - 1.5 * knots[2] + 0.5 * knots[3];
	T c2 = knots[0] - 2.5 * knots[1] + 2.0 * knots[2] - 0.5 * knots[3];
	T c1 = 0.5 * (-knots[0] + knots[2]);
	T c0 = knots[1];

	return (T((c3*x + c2)*x + c1)*x + c0);
}


#endif
