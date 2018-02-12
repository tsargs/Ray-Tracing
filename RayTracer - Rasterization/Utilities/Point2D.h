#ifndef POINT_2D
#define POINT_2D

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/19/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <iostream>

class Point2D
{
	public:
		double x, y, z;

	//Constructors
		Point2D(void);										//Default Constructor
		Point2D(double xVal, double yVal);
		Point2D(const Point2D& point);						//Copy constructor

		~Point2D(void);										//Destructor

	//Member Functions
		Point2D& operator=(const Point2D& point);					//Assignment operator
		Point2D operator*(const float& floatVal) const;

		void PrintValues(void);
};

#endif