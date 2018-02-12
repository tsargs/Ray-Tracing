#ifndef CONSTANTS
#define CONSTANTS

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "RGBColor.h"
//#include "GeometricObject.h"
//#include "Quadric.h"
#include <iostream>

const RGBColor black = RGBColor(0, 0, 0);
const RGBColor white = RGBColor(1, 1, 1);
const RGBColor red	 = RGBColor(1, 0, 0);
const RGBColor green = RGBColor(0, 1, 0);
const RGBColor blue	 = RGBColor(0, 0, 1);
const RGBColor yellow = RGBColor(1, 1, 0);

//const Quadric ellipsoid = Quadric(1, 1, 1, 0, -1);

const double kEpsilon = 0.0001;			//This value denotes the smallest possible value of t during ray intersections
const double kMaxValue = 1.0E10;		//This value denotes the largest possible value of t during ray intersections

const float inverseRandMax = 1.0 / (float)RAND_MAX;

const float toRadiansMultiplier = 3.14159265359 / 180;

const float pi = 3.14159;
const float piBy4 = pi/4;
const float invPi = 0.31831;
const float inv2Pi = 0.15915;


#endif