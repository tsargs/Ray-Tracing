#ifndef POINTLIGHT
#define POINTLIGHT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"
#include "World.h"

class PointLight:public Light
{
	public:

		RGBColor color;
		float intensity;
		Point3D position;

		//Constructors
		PointLight(void);										//Default Constructor
		PointLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const bool& shadowState);

		//Destructor

		~PointLight(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);

		bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;
};

#endif
