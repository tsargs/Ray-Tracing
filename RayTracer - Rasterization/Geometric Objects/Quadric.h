#ifndef QUADRIC
#define QUADRIC

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/14/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"

class Quadric:public GeometricObject
{
	public:
		
		int ai2[3], a21, a00;
		int s[3];

		Point3D Pe, Pc;

		Vector3D n[3];
		Vector3D PCE;
		

		//Constructors

		Quadric(void);												//Default Constructor
		Quadric(const int& a02, const int& a12, const int& a22, const int& a21Param, const int& a00Param);
		Quadric(const Quadric& quadric);								//Copy constructor
		
		//Destructor

		~Quadric(void);

		//Member Functions

		Quadric& operator=(const Quadric& quadric);										//Assignment Operator
		bool hit(const Ray& ray, double& tMin) const;									//Hit function which checks for ray intersections
		void SetCenter(const Point3D& centerPoint);										//Function to set the center of sphere
		void SetCenter(const double& xVal, const double& yVal, const double& zVal);		//Function to set the center of sphere
		void SetEyePosAndPCE(const Point3D& eyePosition);
		void SetSParameter(const int& s0, const int& s1, const int& s2);
		void SetNormalVectors(const Vector3D& n0, const Vector3D& n1, const Vector3D& n2);
		void SetColor(const float& rVal, const float& gVal, const float& bVal);								//Function to set the color of sphere
		void SetColor(const RGBColor& colorObj);
};

inline void Quadric::SetCenter(const Point3D& centerPoint)
{
	Pc = centerPoint;
}

inline void Quadric::SetCenter(const double& xVal, const double& yVal, const double& zVal)
{
	Pc.x = xVal;
	Pc.y = yVal;
	Pc.z = zVal;
}

inline void Quadric::SetEyePosAndPCE(const Point3D& eyePosition)
{
	Pe.x = eyePosition.x;
	Pe.y = eyePosition.y;
	Pe.z = eyePosition.z;

	PCE = Pe - Pc;
}

inline void Quadric::SetSParameter(const int& s0, const int& s1, const int& s2)
{
	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
}

inline void Quadric::SetNormalVectors(const Vector3D& n0, const Vector3D& n1, const Vector3D& n2)
{
	n[0] = n0;
	n[1] = n1;
	n[2] = n2;
}

inline void Quadric::SetColor(const float& rVal, const float& gVal, const float& bVal)
{
	color.r = rVal;
	color.g = gVal;
	color.b = bVal;
}

inline void Quadric::SetColor(const RGBColor& colorObj)
{
	color = colorObj;
}

#endif
