#ifndef CUBE
#define CUBE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Cube:public GeometricObject
{
	public:
		
		Point3D minPoint;
		Point3D maxPoint;     

		Vector3D normals[6];

		BBox bBox;

		//Constructors

		Cube(void);												//Default Constructor
		Cube(const Point3D& minPointObj, const Point3D& maxPointObj);
		Cube(const Cube& cube);								//Copy constructor
		
		//Destructor

		~Cube(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;

		void SetColor(float rVal, float gVal, float bVal);								//Function to set the color of sphere
		void SetNormals(void);
		void SetBoundingBox(void);
};


inline void Cube::SetColor(float rVal, float gVal, float bVal)
{
	color.r = rVal;
	color.g = gVal;
	color.b = bVal;
}

inline void Cube::SetNormals(void)
{
	normals[0] = Vector3D(-1, 0, 0);
	normals[1] = Vector3D(0 ,-1, 0);
	normals[2] = Vector3D(0, 0, -1);
	normals[3] = Vector3D(1, 0, 0);
	normals[4] = Vector3D(0, 1, 0);
	normals[5] = Vector3D(0, 0, 1);
}

#endif
