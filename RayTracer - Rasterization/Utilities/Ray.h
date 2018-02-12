#ifndef RAY
#define RAY

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Point3D.h"
#include "Vector3D.h"

class Ray
{
	public:
		Point3D origin;
		Vector3D rayDirection;

	//Constructors
		Ray(void);												//Default Constructor
		Ray(const Point3D& point, const Vector3D& vector);
		Ray(const Ray& ray);								//Copy constructor

		~Ray(void);												//Destructor

	//Member Functions
		Ray& operator=(const Ray& ray);							//Assignment operator
};

#endif