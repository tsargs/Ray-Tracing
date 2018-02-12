// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/05/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Camera.h"
#include <math.h>

//Default Constructor
Camera::Camera(void)
{
	
}


//Destructor
Camera::~Camera(void)
{

}

void Camera::RenderScene()
{

}

//Rotation of point about arbitrary line
// --based on method presented in "http://math.kennesaw.edu/~plaval/math4490/rotgen.pdf" and "http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/"
Point3D Camera::Rotate(const Point3D& point, const Point3D& pointOnAxis, const float& rollAngle, const Vector3D& axisVector)
{
	//Degrees to radians conversion
	float theta = rollAngle * toRadiansMultiplier;

	float C = cos(theta);
	float S = sin(theta);
	float t = 1 - C;

	float u = axisVector.x;
	float v = axisVector.y;
	float w = axisVector.z;

	float x = point.x;
	float y = point.y;
	float z = point.z;

	float a = pointOnAxis.x;
	float b = pointOnAxis.y;
	float c = pointOnAxis.z;

	Point3D newPoint;

	
	newPoint.x = (a*(v*v + w*w) - u*(b*v + c*w - u*x - v*y - w*z)) * t + x*C + ((-c)*v + b*w - w*y + v*z)*S;
	newPoint.y = (b*(u*u + w*w) - v*(a*u + c*w - u*x - v*y - w*z)) * t + y*C + (c*u - a*w + w*x - u*z)*S;
	newPoint.z = (c*(u*u + v*v) - w*(a*u + b*v - u*x - v*y - w*z)) * t + z*C + ((-b)*u + a*v - v*x + u*y)*S;

	return newPoint;
}

